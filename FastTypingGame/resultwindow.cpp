#include "resultwindow.h"
#include "ui_resultwindow.h"

ResultWindow::ResultWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setWindowTitle("Results");
}

ResultWindow::~ResultWindow()
{
    delete ui;
}

void ResultWindow::setResults(double wpm, double accuracy) {
    ui->lblWPM->setText(QString("WPM: %1").arg(wpm, 0, 'f', 1));
    ui->lblAccuracy->setText(QString("Accuracy: %1%").arg(accuracy, 0, 'f', 1));
}

QPushButton* ResultWindow::getRetryButton() const {
    return ui->btnRetry;
}

QPushButton* ResultWindow::getMenuButton() const {
    return ui->btnMenu;
}
