#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fast Typing Game - Kyiv");

    connect(ui->btnEnglish, &QPushButton::clicked, this, &MainWindow::openModeWindow);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openModeWindow() {
    modeWindow = new ModeWindow();

    connect(modeWindow->getBackButton(), &QPushButton::clicked, this, [this]() {
        modeWindow->close();
        this->show();
    });

    modeWindow->show();
    this->hide();
}
