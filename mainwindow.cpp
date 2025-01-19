#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QBrush>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QRandomGenerator>
#include <QDebug>
#include <QPen>
#include "propertydialog.h"
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    PropertyDialog* dlg = new PropertyDialog();
    if(dlg->exec() == QDialog::Rejected)
    {
        this->close();//退出不完全
    }

    if(dlg->getLineNum() < 2 || dlg->getLineNum() > 20)
        gridHorizontalNum = 20;
    else
        gridHorizontalNum = dlg->getLineNum();
    if(dlg->getRowNum() < 2 || dlg->getRowNum() > 15)
        gridVerticalNum = 15;
    else
        gridVerticalNum = dlg->getRowNum();
    if(dlg->getSpeedNum() < 100 || dlg->getSpeedNum() > 1000)
        timerInterval = 200;
    else
        timerInterval = dlg->getSpeedNum();
    //窗口设置
    this->setWindowTitle("Snake");
    this->resize(gridHorizontalNum * gridWidth + sideBarWidth, gridVerticalNum * gridWidth);
    this->setFixedSize(this->width(), this->height());
    //初始化蛇头
    snakeHead = new SnakeHead(this);
    //初始化蛇身
    snakeNodes[0].posX = 1;
    snakeNodes[0].posY = 0;
    snakeNodes[1].posX = 0;
    snakeNodes[1].posY = 0;
    //初始化食物
    snakeFood = new Food;
    setFood();
    //计时器
    moveTimer = new QTimer;
    connect(moveTimer, &QTimer::timeout, [=](){//1计时器最好放在最外层
        update();
        //是否吃到食物
        if(snakeFood->posX == snakeHead->posX && snakeFood->posY == snakeHead->posY)
        {
            setFood();
            growBody();
        }
        //尾部移动
        moveBody();
        //头部移动
        moveHead();
        //游戏失败
        if(isGameOver())
        {
            gameOver();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    //背景绘制
    drawBackground();
    //网格绘制
    //drawGrid();
    //边栏绘制
    drawSideBar();
    //蛇头绘制
    drawHead();
    //蛇身绘制
    drawBody();
    //食物绘制
    drawFoods();
}



//类的方法全部在主窗口中实现,多窗口编程
void MainWindow::moveHead()
{
    switch (snakeHead->direction) {
    case SnakeHead::upDir:
        snakeHead->posY -= 1;
        break;
    case SnakeHead::downDir:
        snakeHead->posY += 1;
        break;
    case SnakeHead::leftDir:
        snakeHead->posX -= 1;
        break;
    case SnakeHead::rightDir:
        snakeHead->posX += 1;
        break;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Up && snakeHead->direction != SnakeHead::downDir)//防止往回走
    {
        snakeHead->direction = 1;
    }
    if(event->key() == Qt::Key_Down && snakeHead->direction != SnakeHead::upDir)
    {
        snakeHead->direction = 2;
    }
    if(event->key() == Qt::Key_Left && snakeHead->direction != SnakeHead::rightDir)
    {
        snakeHead->direction = 3;
    }
    if(event->key() == Qt::Key_Right && snakeHead->direction != SnakeHead::leftDir)
    {
        snakeHead->direction = 4;
    }//bug:快速按下↓和←键可以重合
    //暂停
    if(event->key() == Qt::Key_Space || event->key() == Qt::Key_Return)
    {
        if(isSuspended)
        {
            moveTimer->start(timerInterval);
            isSuspended = !isSuspended;
        }
        else
        {
            moveTimer->stop();
            isSuspended = !isSuspended;
        }
    }
}

bool MainWindow::isGameOver()
{
    //碰到边界
    if(snakeHead->posX < 0 || snakeHead->posY < 0 || snakeHead->posX >= gridHorizontalNum || snakeHead->posY >= gridVerticalNum)
    {
        return true;
    }
    //碰到蛇身
    for(int i = 0; i < nodeNum; i++)
    {
        if(snakeNodes[i].posX == snakeHead->posX && snakeNodes[i].posY == snakeHead->posY)
        {
            return true;
        }
    }
    return false;
}

void MainWindow::moveBody(){
    for(int i = nodeNum - 1; i >= 1; i--)
    {
        snakeNodes[i].posX = snakeNodes[i - 1].posX;
        snakeNodes[i].posY = snakeNodes[i - 1].posY;
    }
    snakeNodes[0].posX = snakeHead->posX;
    snakeNodes[0].posY = snakeHead->posY;
}

void MainWindow::gameOver()
{
    moveTimer->stop();
}

void MainWindow::setFood()
{
    do
    {
        snakeFood->posX = QRandomGenerator::global()->bounded(0, gridHorizontalNum);
        snakeFood->posY = QRandomGenerator::global()->bounded(0, gridVerticalNum);
    }
    while(isBody());//身体和头部分不能产生食物
}

void MainWindow::drawFoods(){
    QColor foodColor(QColor(0, 188, 212));
    QPen pen(foodColor);
    QBrush foodPen(foodColor);
    QPainter painter(this);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(foodPen);
    painter.drawRect(snakeFood->posX * gridWidth, snakeFood->posY * gridWidth, gridWidth, gridWidth);
}

void MainWindow::growBody()
{
    snakeNodes[nodeNum].posX = snakeNodes[nodeNum - 1].posX;
    snakeNodes[nodeNum].posY = snakeNodes[nodeNum - 1].posY;
    nodeNum++;
}

bool MainWindow::isBody()
{
    if(snakeHead->posX == snakeFood->posX && snakeHead->posY == snakeFood->posY)
    {
        return true;
    }
    for(int i = 0; i < nodeNum; i++)
    {
        if(snakeNodes[i].posX == snakeFood->posX && snakeNodes[i].posY == snakeFood->posY)
        {
            return true;
        }
    }
    return false;
}



void MainWindow::drawHead()
{
    QColor headColor(QColor(230, 138, 230));
    QPen pen(headColor);
    QPainter painter(this);
    QBrush snakeHeadPen(headColor);
    painter.setPen(pen);
    painter.setBrush(snakeHeadPen);
    painter.drawRect(snakeHead->posX * gridWidth, snakeHead->posY * gridWidth, gridWidth, gridWidth);
}

void MainWindow::drawBody()
{
    QColor bodyColor(QColor(119, 221, 119));
    QPen pen(bodyColor);
    QPainter painter(this);
    QBrush snakeBodyPen(bodyColor);
    painter.setPen(pen);
    painter.setBrush(snakeBodyPen);
    for(int i = 0; i < nodeNum; i++)
    {
        painter.drawRect(snakeNodes[i].posX * gridWidth, snakeNodes[i].posY * gridWidth, gridWidth, gridWidth);
    }
}

void MainWindow::drawGrid()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    for(int i = 0; i < gridHorizontalNum; i++){
        for(int j = 0; j < gridVerticalNum; j++){
            painter.drawRect(i * gridWidth, j * gridWidth, gridWidth, gridWidth);
        }
    }
}

void MainWindow::drawSideBar()
{
    QPainter painter(this);
    painter.drawLine(gridWidth * gridHorizontalNum, 0, gridWidth * gridHorizontalNum, gridWidth * gridVerticalNum);
}

void MainWindow::drawBackground()
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/Images/Bk1.jpg");//加载图片
    painter.drawPixmap(0, 0, this->width(), this->height(), pix);//显示图片
}

