#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QString>
#include <QElapsedTimer>

class GameEngine {
public:
    GameEngine();

    void startSession(const QString& text);
    bool processInput(const QString& currentInput, const QString& expectedWord);

    double calculateWPM() const;
    double calculateAccuracy() const;

    QString getCurrentText() const;
    int getErrors() const;

private:
    QString targetText;
    int correctChars;
    int totalKeystrokes;
    int errors;
    QElapsedTimer timer;
};

#endif
