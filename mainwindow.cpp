#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <QPushButton>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::MainWindow),m_ptimer(new QTimer(this)),m_gametag(false)
{
    ui->setupUi(this);
    ui->pushButton_pause->setEnabled(false);
    m_ptimer->stop();
    connect(ui->pushButton_start,&QPushButton::clicked,this,&MainWindow::gameStart);
    connect(ui->pushButton_pause,&QPushButton::clicked,this,&MainWindow::gamePause);
    connect(m_ptimer,&QTimer::timeout,this,&MainWindow::autoMoveEvent);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::gameStart()
{
    Wall* pwall=Wall::getdata();
    Snake* psnake=Snake::getdata();
    Food* pfood=Food::getdata();
    pwall->initial();
    psnake->initial();
    pfood->setFood();
    m_ptimer->start(200);
    ui->pushButton_start->setEnabled(false);
    ui->pushButton_pause->setEnabled(true);
    m_gametag=true;
    pfood->getlabel()->show();
    emit flushGameInfo();


}

void MainWindow::gamePause()
{
    if(m_gametag)
    {
        ui->pushButton_pause->setText(" 继续游戏");
        m_gametag=false;
        m_ptimer->stop();
    }
    else
    {
        ui->pushButton_pause->setText(" 暂停游戏");
        m_gametag=true;
        m_ptimer->start();
    }
}
void MainWindow::keyPressEvent(QKeyEvent  *event)
{
    Snake* psnake=Snake::getdata();
    if((event->key()==Qt::Key_Up)||(event->key()==Qt::Key_W) )
    {
        psnake->setdir(UP);
    }
    if((event->key()==Qt::Key_Down)||(event->key()==Qt::Key_S))
    {
        psnake->setdir(DOWN);
    }
    if((event->key()==Qt::Key_Left)||(event->key()==Qt::Key_A))
    {
        psnake->setdir(LEFT);
    }
    if((event->key()==Qt::Key_Right)||(event->key()==Qt::Key_D))
    {
        psnake->setdir(RIGHT);
    }
}

void MainWindow::autoMoveEvent()
{
    Snake* psnake=Snake::getdata();
    bool tag_gamepsnake=psnake->move(psnake->getNextDirect());
    if(!tag_gamepsnake) emit gameEnd();
    else
    {
        emit flushGameInfo();
    }
}

void MainWindow::flushGameInfo()
{
    ui->label_level->setText(QString::number(Snake::getLevel()));
    ui->label_score->setText(QString::number(Snake::getCore()));
    m_ptimer->start(200-(Snake::getLevel()-1)*20);
}

void MainWindow::gameEnd()
{
     m_ptimer->stop();
     ui->pushButton_pause->setEnabled(false);
     QMessageBox::StandardButton temp=QMessageBox::information(this,"Game End",QString("继续游戏?"),QMessageBox::Yes|QMessageBox::Cancel);
     if(temp==QMessageBox::Yes)
     {
         emit gameStart();
     }
     else
     {
         ui->pushButton_start->setEnabled(true);
         ui->pushButton_pause->setEnabled(false);
     }
}
