#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "snakehead.h"
#include "snakebody.h"
#include "food.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    int gridWidth = 50;//网格长宽
    int gridHorizontalNum = 20;
    int gridVerticalNum = 15;
    int sideBarWidth = 200;
    int nodeNum = 2;
    bool isSuspended = 1;
    int timerInterval = 200;
    SnakeHead* snakeHead;
    SnakeBody snakeNodes[100];
    Food* snakeFood;
    QTimer* moveTimer;

    void moveHead();
    void moveBody();
    void keyPressEvent(QKeyEvent *event);
    void gameOver();
    bool isGameOver();
    void setFood();
    void drawFoods();
    void growBody();
    bool isBody();
    void drawHead();
    void drawBody();
    void drawGrid();
    void drawSideBar();
    void drawBackground();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
