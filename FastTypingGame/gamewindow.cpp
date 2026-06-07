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
}

GameWindow::~GameWindow()
{
    delete ui;
}
