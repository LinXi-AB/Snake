#ifndef SNAKEHEAD_H
#define SNAKEHEAD_H

#include <QObject>
#include <QTimer>
#include <QMessageBox>

class SnakeHead : public QObject
{
    Q_OBJECT
public:
    explicit SnakeHead(QObject *parent = nullptr);
    enum Direction {
        upDir = 1,
        downDir,
        leftDir,
        rightDir
    };
    int direction = 4;
    int posX = 2;
    int posY = 0;

    bool gameStatus();
    enum GameStatus {
        proceeding = 1,
        over,
        win
    };

signals:
};

#endif // SNAKEHEAD_H
