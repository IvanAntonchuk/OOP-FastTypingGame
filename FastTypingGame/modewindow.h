#ifndef MODEWINDOW_H
#define MODEWINDOW_H

#include <QWidget>
#include <QPushButton>
#include "gamewindow.h"

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

private slots:
    void openGameWindow();

private:
    Ui::ModeWindow *ui;
    GameWindow *gameWindow;
};

#endif
