#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fast Typing Game - Classic Mode");

    connect(ui->btnBack, &QPushButton::clicked, this, &GameWindow::close);
    this->setAttribute(Qt::WA_DeleteOnClose);

    timeLeft = 60;
    ui->lblTimer->setText(QString::number(timeLeft));

    QString testText = "This is a simple test string for the typing game. We will add more texts later.";
    engine.startSession(testText);

    wordsList = engine.getCurrentText().split(" ");
    currentWordIndex = 0;

    ui->progressBar->setValue(0);

    gameTimer = new QTimer(this);
    connect(gameTimer, &QTimer::timeout, this, &GameWindow::updateTimer);

    connect(ui->inputField, &QLineEdit::textChanged, this, &GameWindow::handleInput);

    renderText("");
    gameTimer->start(1000);
}

GameWindow::~GameWindow()
{
    delete ui;
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
    if (currentWordIndex >= wordsList.size()) {
        return;
    }

    QString targetWord = wordsList[currentWordIndex];

    if (text.endsWith(" ")) {
        QString typedWord = text.trimmed();

        if (typedWord == targetWord) {
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
    }

    renderText(text);
}

void GameWindow::endGame() {
    gameTimer->stop();
    ui->inputField->setEnabled(false);
    ui->textDisplay->setHtml("<h2 style='color: #4caf50; text-align: center;'>Game Over!</h2>");
}
