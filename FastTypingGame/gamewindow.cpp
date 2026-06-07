#include "GameWindow.h"

GameWindow::GameWindow(QWidget *parent) : QWidget(parent) {
    this->resize(800, 600);
    this->setWindowTitle("Fast Typing Game - Classic Mode");

    mainLayout = new QVBoxLayout(this);
    topLayout = new QHBoxLayout();

    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(false);
    progressBar->setStyleSheet("QProgressBar::chunk { background-color: green; }");

    timerLabel = new QLabel("60", this);
    QFont timerFont = timerLabel->font();
    timerFont.setPointSize(16);
    timerFont.setBold(true);
    timerLabel->setFont(timerFont);

    topLayout->addWidget(progressBar);
    topLayout->addWidget(timerLabel);

    textDisplay = new QTextEdit(this);
    textDisplay->setReadOnly(true);
    textDisplay->setFontPointSize(14);
    textDisplay->setText("This is a simple test string for Kyiv typing game.");

    inputField = new QLineEdit(this);
    QFont inputFont = inputField->font();
    inputFont.setPointSize(14);
    inputField->setFont(inputFont);

    backButton = new QPushButton("Main Menu", this);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(textDisplay);
    mainLayout->addWidget(inputField);
    mainLayout->addWidget(backButton);
}

GameWindow::~GameWindow() {
}

QPushButton* GameWindow::getBackButton() const {
    return backButton;
}
