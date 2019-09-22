#include "wall.h"
#include <iostream>
#include <QLabel>
#include <QPainter>
#include "snake.h"
#include "food.h"

Wall* Wall::m_Walldata = nullptr;
std::once_flag Wall::m_flag_wall;
Wall::RememberFree Wall::m_free;

Wall::Wall() : m_array() {
    initial();
}

Wall::~Wall() {}

inline void Wall::initial_data_once() {
    m_Walldata = new Wall();
}

void Wall::initial(){
    for (size_t i = 0; i < COL; ++i) {
        for (size_t j = 0; j < ROW; ++j) {
            if (i == 0 || i == COL - 1 || j == 0 || j == ROW - 1)
                m_array[i][j] = S_WALL;
			else
                m_array[i][j] = S_ROAD;
		}
    }
}

void Wall::paintEvent(QPaintEvent *) {
    QPainter*  m_qpainter=new QPainter(this);
    m_qpainter->setPen(QPen(Qt::gray,36));
    m_qpainter->drawLine(0,0,0,500);
    m_qpainter->drawLine(0,0,360,0);
    m_qpainter->drawLine(0,500,360,500);
    m_qpainter->drawLine(360,0,360,500);
    m_qpainter->setPen(QPen(Qt::lightGray,3));
    for (size_t i=0;i<=ROW;++i) {
        m_qpainter->drawLine(i*20,0,i*20,500);
        m_qpainter->drawLine(0,i*20,500,i*20);
    }
    Snake* p_snake=Snake::getdata();
    QList<SnakeNode*> p_list=p_snake->getlistdata();
    for(auto beg=p_list.begin();beg!=p_list.end();++beg) {
        SnakeNode* p=*beg;
        QLabel* pQlabel=p->m_plabel;
        pQlabel->show();
    }
    delete m_qpainter;
}

Wall* Wall::getdata() {
    std::call_once(m_flag_wall,&Wall::initial_data_once);
    return m_Walldata;
}

void Wall::setwall(size_t x, size_t y, char c) {
    m_array[x][y] = c;
}

char Wall::getwall(size_t x, size_t y) {
    return m_array[x][y];
}


SnakeNode::~SnakeNode() {
    delete m_plabel;
}
