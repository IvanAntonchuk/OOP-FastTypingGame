#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "GameEngine.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

    QPushButton* getBackButton() const;

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *topLayout;
    QProgressBar *progressBar;
    QLabel *timerLabel;
    QTextEdit *textDisplay;
    QLineEdit *inputField;
    QPushButton *backButton;

    GameEngine engine;
};

#endif
