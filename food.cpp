#include <random>
#include "food.h"
#include "wall.h"
#include <QLabel>

std::mutex Food::mtx;
Food::rememberfree Food::rember;
Food* Food::m_fooddata=nullptr;

Food::Food(QLabel *plabel):m_pfoodlabel(plabel)
{
}

QLabel *Food::getlabel()
{
    return m_pfoodlabel;
}

void Food::setFood()
{
	for (;;)
	{
		static std::default_random_engine e(6);
        static std::uniform_int_distribution<unsigned> u1(1, COL - 2);
        static std::uniform_int_distribution<unsigned> u2(1, ROW - 2);
        m_Food_x = u1(e);
        m_Food_y = u2(e);
        Wall* m_pWall = Wall::getdata();
        if (m_pWall->getwall(m_Food_x, m_Food_y) == S_ROAD)
		{
            m_pWall->setwall(m_Food_x, m_Food_y, S_FOOD);
            m_pfoodlabel->move(m_Food_x*20,m_Food_y*20);
			break;
		}
	}
}

Food* Food::getdata()
{
	if (m_fooddata == nullptr)
	{
		mtx.lock();
		if (!m_fooddata)
        {
            QLabel *pdata=new QLabel(Wall::getdata());
            m_fooddata = new Food(pdata);
            QPixmap map=QPixmap(QString::fromUtf8(":/Skin/food.png"));
            map=map.scaled(20,20,Qt::KeepAspectRatio);
            m_fooddata->getlabel()->setPixmap(map);
        }
		mtx.unlock();
	}
    return m_fooddata;
}

Food::~Food()
{
}
