#include "modewindow.h"
#include "ui_modewindow.h"

ModeWindow::ModeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Select Game Mode");

    connect(ui->btnClassic, &QPushButton::clicked, this, &ModeWindow::openGameWindow);
}

ModeWindow::~ModeWindow()
{
    delete ui;
}

QPushButton* ModeWindow::getBackButton() const {
    return ui->btnBack;
}

void ModeWindow::openGameWindow() {
    gameWindow = new GameWindow();

    connect(gameWindow, &GameWindow::destroyed, this, [this]() {
        this->show();
    });

    gameWindow->show();
    this->hide();
}
