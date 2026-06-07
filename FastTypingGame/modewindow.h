#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class ModeWindow;
}

class ModeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ModeWindow(QWidget *parent = nullptr);
    ~ModeWindow();

    QPushButton* getBackButton() const;

private:
    Ui::ModeWindow *ui;
};

#endif
