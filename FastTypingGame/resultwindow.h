#ifndef RESULTWINDOW_H
#define RESULTWINDOW_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ResultWindow;
}

class ResultWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWindow(QWidget *parent = nullptr);
    ~ResultWindow();

    void setResults(double wpm, double accuracy);
    QPushButton* getRetryButton() const;
    QPushButton* getMenuButton() const;

private:
    Ui::ResultWindow *ui;
};

#endif
