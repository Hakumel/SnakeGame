#include "snake.h"
#include "wall.h"
#include "Point.h"
#include "Food.h"
#include <iostream>
#include <QLabel>
Snake::rememberfree Snake::m_free;
Snake* Snake::m_data=nullptr;
std::mutex Snake::mtx;

unsigned Snake::m_count = 0;
unsigned Snake::m_level = 1;


Snake *Snake::getdata()
{
    if(!m_data)
    {
        mtx.lock();
        if(!m_data)
        {
            m_data=new Snake(Wall::getdata());
        }
        mtx.unlock();
    }
    return m_data;
}

Snake::Snake(Wall* w) :m_NodeList(), m_phead(nullptr),m_pWall(w),m_predirct(RIGHT),m_nextdirct(RIGHT) { }

QList<SnakeNode *> Snake::getlistdata()
{
    return m_NodeList;
};

void Snake::initial()
{
	destoryPoint();
    addNode(3, 6);
    addNode(4, 6);
    addNode(5, 6);
}

void Snake::deltailnode()
{
    if(!m_NodeList.empty())
    {
        SnakeNode *pdel=m_NodeList.back();
        m_NodeList.pop_back();
        m_pWall->setwall(pdel->m_nodex,pdel->m_nodey,state::S_ROAD);
        delete pdel;
        pdel=nullptr;
    }
    SnakeNode *ptail=m_NodeList.back();
    m_pWall->setwall(ptail->m_nodex,ptail->m_nodey,state::S_TAIL);
	--m_count;
}
void Snake::addNode(unsigned x, unsigned y)
{
    QLabel* newlabel = new QLabel(Wall::getdata());//是否需要加this
    QPixmap map=QPixmap(QString::fromUtf8(":/Skin/snakehead.png"));
    map=map.scaled(20,20,Qt::KeepAspectRatio);
    newlabel->setPixmap(map);
    newlabel->move(x*20,y*20);
    SnakeNode * newnode=new SnakeNode(x,y,newlabel);
    m_pWall->setwall(x,y,state::S_SNAKE);
    if(m_phead)
    {
        QPixmap newmap=QPixmap(QString::fromUtf8(":/Skin/snakebody.png"));
        newmap=newmap.scaled(20,20,Qt::KeepAspectRatio);
        m_NodeList.front()->m_plabel->setPixmap(newmap);
    }
    m_NodeList.push_front(newnode);
    m_phead=newnode;
    ++m_count;
    changeGameInfo();
}

bool Snake::move(char dir)
{
    m_predirct=dir;
    bool result=true;
    unsigned x = m_phead->m_nodex;
    unsigned y = m_phead->m_nodey;
    switch (dir)
    {
    case UP:
    {
        --y;
        break;
    }
    case DOWN:
    {
        ++y;
        break;
    }
    case LEFT:
    {
        --x;
        break;
    }
    case RIGHT:
    {
        ++x;
        break;
    }
    }
    char state = m_pWall->getwall(x, y);
    if (state == state::S_ROAD|| state == state::S_TAIL)
    {
        deltailnode();
        addNode(x,y);
    }
    else if (state == state::S_FOOD)
    {
        addNode(x, y);
        Food::getdata()->setFood();
    }
    else if(state==state::S_SNAKE)
    {
        result=false;
    }
    else
    {
        deltailnode();
        addNode(x, y);
        result=false;
    }
    return result;
}


void Snake::setdir(char dir)
{
    if(((dir == LEFT&& m_predirct==RIGHT) || (dir == UP && m_predirct == DOWN) || (dir == DOWN && m_predirct == UP) || (dir == RIGHT && m_predirct == LEFT)))
    {
    }
    else
    {
        m_nextdirct=dir;
    }
}

char Snake::getPreDirect()
{
    return m_predirct;
}

char Snake::getNextDirect()
{
    return m_nextdirct;
}


unsigned Snake::getCore()
{
	if (m_count == 0)
		return 0;
	else 
		return (m_count-3)*100;
}
unsigned Snake::getLevel()
{
    return m_level;
}

void Snake::destoryPoint()
{
    while(!m_NodeList.empty())
    {
        SnakeNode *pdel=m_NodeList.front();
        m_pWall->setwall(pdel->m_nodex,pdel->m_nodey,state::S_ROAD);
        m_NodeList.pop_front();
        delete pdel;
    }
    m_phead = nullptr;
    m_level=1;
	m_count = 0;
    m_predirct=RIGHT;
    m_nextdirct=RIGHT;
}

void Snake::changeGameInfo()
{
    if(m_level<10)
        m_level=m_count/6+1;
}

