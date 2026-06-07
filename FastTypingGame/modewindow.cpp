#include "modewindow.h"
#include "ui_modewindow.h"

ModeWindow::ModeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Select Game Mode");
}

ModeWindow::~ModeWindow()
{
    delete ui;
}

QPushButton* ModeWindow::getBackButton() const {
    return ui->btnBack;
}
