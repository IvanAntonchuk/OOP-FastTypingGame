#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QStringList>
#include "GameEngine.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void updateTimer();
    void handleInput(const QString &text);
    void endGame();

private:
    void renderText(const QString &currentInput);

    Ui::GameWindow *ui;
    GameEngine engine;
    QTimer *gameTimer;
    int timeLeft;
    QStringList wordsList;
    int currentWordIndex;
};

#endif
