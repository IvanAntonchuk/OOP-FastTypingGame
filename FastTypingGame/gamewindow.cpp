#include "gamewindow.h"
#include "ui_gamewindow.h"
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Fast Typing Game - Classic Mode");

    connect(ui->btnBack, &QPushButton::clicked, this, &GameWindow::onBackClicked);
    this->setAttribute(Qt::WA_DeleteOnClose);

    timeLeft = 60;
    isPlaying = false;

    ui->lblTimer->setText(QString::number(timeLeft));
    ui->inputField->setEnabled(false);

    QFile file(":/texts_en.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (!line.isEmpty()) {
                textPool << line;
            }
        }
        file.close();
    }

    if (textPool.isEmpty()) {
        textPool << "Error loading texts file. This is a fallback string.";
    }

    loadRandomText();

    ui->progressBar->setValue(0);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameWindow::updateTimer);

    connect(ui->inputField, &QLineEdit::textChanged, this, &GameWindow::handleInput);

    QTimer::singleShot(100, this, &GameWindow::startCountdown);
}

GameWindow::~GameWindow()
{
    delete ui;
}

void GameWindow::loadRandomText() {
    int randomIndex = QRandomGenerator::global()->bounded(textPool.size());
    QString selectedText = textPool[randomIndex];

    engine.startSession(selectedText);
    wordsList = engine.getCurrentText().split(" ");
    currentWordIndex = 0;

    renderText("");
}

void GameWindow::onBackClicked() {
    bool timerWasActive = gameTimer->isActive();

    if (timerWasActive) {
        gameTimer->stop();
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Give Up", "Are you sure you want to give up?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        this->close();
    } else {
        if (timerWasActive && timeLeft > 0) {
            gameTimer->start(1000);
            if (isPlaying) {
                ui->inputField->setFocus();
            }
        }
    }
}

void GameWindow::startCountdown() {
    QDialog *dialog = new QDialog(this);
    dialog->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    dialog->setModal(true);
    dialog->setFixedSize(200, 200);

    dialog->setStyleSheet("QDialog { border: 4px solid white; background-color: #333333; border-radius: 10px; }");

    QVBoxLayout *layout = new QVBoxLayout(dialog);
    QLabel *label = new QLabel("3", dialog);
    QFont font = label->font();
    font.setPointSize(72);
    font.setBold(true);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    label->setStyleSheet("color: white;");
    layout->addWidget(label);

    QTimer *timer = new QTimer(dialog);
    int countdownValue = 3;

    connect(timer, &QTimer::timeout, dialog, [dialog, label, timer, countdownValue]() mutable {
        countdownValue--;
        if (countdownValue > 0) {
            label->setText(QString::number(countdownValue));
        } else {
            timer->stop();
            dialog->accept();
        }
    });

    connect(dialog, &QDialog::accepted, this, [this, dialog]() {
        dialog->deleteLater();
        this->startGame();
    });

    timer->start(1000);
    dialog->exec();
}

void GameWindow::startGame() {
    isPlaying = true;
    ui->inputField->setEnabled(true);
    ui->inputField->setFocus();
    gameTimer->start(1000);
}

void GameWindow::updateTimer() {
    timeLeft--;
    ui->lblTimer->setText(QString::number(timeLeft));

    if (timeLeft <= 0) {
        endGame();
    }
}

void GameWindow::renderText(const QString &currentInput) {
    if (currentWordIndex >= wordsList.size()) {
        return;
    }

    QString html = "<span style='font-size: 16pt;'>";
    QString fullText = engine.getCurrentText();

    int wordStartIndex = 0;
    for (int i = 0; i < currentWordIndex; i++) {
        wordStartIndex += wordsList[i].length() + 1;
    }
    int wordEndIndex = wordStartIndex + wordsList[currentWordIndex].length();

    for (int i = 0; i < fullText.length(); i++) {
        if (i == wordStartIndex) {
            html += "<u>";
        }

        if (i == wordStartIndex + currentInput.length()) {
            html += "<b>|</b>";
        }

        QChar c = fullText[i];
        QString charStr = QString(c).toHtmlEscaped();

        if (c == ' ' && i >= wordStartIndex && i < wordStartIndex + currentInput.length() && currentInput[i - wordStartIndex] != c) {
            charStr = "&nbsp;";
        }

        if (i < wordStartIndex) {
            html += "<span style='color: #4caf50;'>" + charStr + "</span>";
        } else if (i >= wordStartIndex && i < wordStartIndex + currentInput.length()) {
            int inputIndex = i - wordStartIndex;
            if (currentInput[inputIndex] == c) {
                html += "<span style='color: #4caf50;'>" + charStr + "</span>";
            } else {
                html += "<span style='background-color: #e57373; color: black;'>" + charStr + "</span>";
            }
        } else {
            html += charStr;
        }

        if (i == wordEndIndex - 1) {
            html += "</u>";
        }
    }

    if (wordStartIndex + currentInput.length() == fullText.length()) {
        html += "<b>|</b>";
    }

    html += "</span>";
    ui->textDisplay->setHtml(html);
}

void GameWindow::handleInput(const QString &text) {
    if (!isPlaying || currentWordIndex >= wordsList.size()) {
        return;
    }

    QString targetWord = wordsList[currentWordIndex];

    if (text.endsWith(" ")) {
        QString typedWord = text.trimmed();

        if (typedWord == targetWord) {
            engine.processInput(typedWord, targetWord);
            currentWordIndex++;

            int progress = (currentWordIndex * 100) / wordsList.size();
            ui->progressBar->setValue(progress);

            ui->inputField->blockSignals(true);
            ui->inputField->clear();
            ui->inputField->setStyleSheet("");
            ui->inputField->blockSignals(false);

            if (currentWordIndex >= wordsList.size()) {
                endGame();
            } else {
                renderText("");
            }
        } else {
            ui->inputField->setStyleSheet("background-color: #e57373; color: black;");
            renderText(text);
        }
        return;
    }

    bool isCorrect = true;
    for (int i = 0; i < text.length(); i++) {
        if (i >= targetWord.length() || text[i] != targetWord[i]) {
            isCorrect = false;
            break;
        }
    }

    if (isCorrect) {
        ui->inputField->setStyleSheet("");
    } else {
        ui->inputField->setStyleSheet("background-color: #e57373; color: black;");
        engine.processInput(text, targetWord);
    }

    renderText(text);
}

void GameWindow::endGame() {
    gameTimer->stop();
    isPlaying = false;
    ui->inputField->setEnabled(false);
    ui->textDisplay->setHtml("<h2 style='color: #4caf50; text-align: center;'>Game Over!</h2>");

    double wpm = engine.calculateWPM();
    double acc = engine.calculateAccuracy();

    resWindow = new ResultWindow();
    resWindow->setResults(wpm, acc);

    connect(resWindow->getMenuButton(), &QPushButton::clicked, this, [this]() {
        resWindow->close();
        this->close();
    });

    connect(resWindow->getRetryButton(), &QPushButton::clicked, this, [this]() {
        resWindow->close();
        this->resetGame();
    });

    resWindow->show();
}

void GameWindow::resetGame() {
    timeLeft = 60;
    isPlaying = false;

    ui->lblTimer->setText(QString::number(timeLeft));
    ui->progressBar->setValue(0);
    ui->inputField->clear();
    ui->inputField->setEnabled(false);

    loadRandomText();

    QTimer::singleShot(100, this, &GameWindow::startCountdown);
}
