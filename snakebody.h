#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <QObject>

class SnakeBody : public QObject
{
    Q_OBJECT
public:
    explicit SnakeBody(QObject *parent = nullptr);
    SnakeBody* nextSnakeBody;
    int posX = -1;
    int posY = -1;

signals:

};

#endif // SNAKEBODY_H
