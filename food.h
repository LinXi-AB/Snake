#ifndef FOOD_H
#define FOOD_H

#include <QMainWindow>

class Food : public QMainWindow
{
    Q_OBJECT
public:
    explicit Food(QWidget *parent = nullptr);
    int posX = -1;
    int posY = -1;

signals:

};

#endif // FOOD_H
