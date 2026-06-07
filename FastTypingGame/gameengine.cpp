#include "GameEngine.h"

GameEngine::GameEngine() : correctChars(0), totalKeystrokes(0), errors(0) {
}

void GameEngine::startSession(const QString& text) {
    targetText = text;
    correctChars = 0;
    totalKeystrokes = 0;
    errors = 0;
    timer.start();
}

bool GameEngine::processInput(const QString& currentInput, const QString& expectedWord) {
    totalKeystrokes++;

    if (expectedWord.startsWith(currentInput)) {
        if (currentInput == expectedWord) {
            correctChars += currentInput.length() + 1;
        }
        return true;
    } else {
        errors++;
        return false;
    }
}

double GameEngine::calculateWPM() const {
    double minutes = timer.elapsed() / 60000.0;
    if (minutes <= 0.0) {
        return 0.0;
    }
    return (correctChars / 5.0) / minutes;
}

double GameEngine::calculateAccuracy() const {
    if (totalKeystrokes == 0) {
        return 0.0;
    }
    return ((totalKeystrokes - errors) * 100.0) / totalKeystrokes;
}

QString GameEngine::getCurrentText() const {
    return targetText;
}

int GameEngine::getErrors() const {
    return errors;
}
