#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTimer>
#include <QStringList>
#include "GameEngine.h"
#include "resultwindow.h"

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
    void startCountdown();
    void startGame();
    void onBackClicked();
    void resetGame();

private:
    void renderText(const QString &currentInput);
    void loadRandomText();

    Ui::GameWindow *ui;
    GameEngine engine;
    QTimer *gameTimer;
    int timeLeft;
    bool isPlaying;
    QStringList wordsList;
    int currentWordIndex;
    ResultWindow *resWindow;
    QStringList textPool;
};

#endif
