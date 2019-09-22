#include "food.h"
#include "wall.h"
#include <QLabel>
#include <random>

Food::RememberFree Food::m_free;
Food* Food::m_fooddata=nullptr;
std::once_flag Food::m_flag_food;

Food::Food(QLabel *plabel) : m_pfoodlabel(plabel) {}
Food::~Food() = default;

void Food::initial_data_once() {
    m_fooddata = new Food(new QLabel(Wall::getdata()));
    QPixmap map=QPixmap(QString::fromUtf8(":/Skin/food.png"));
    map=map.scaled(20,20,Qt::KeepAspectRatio);
    m_fooddata->getlabel()->setPixmap(map);
}

QLabel *Food::getlabel() {
    return m_pfoodlabel;
}

void Food::setFood() {
	for (;;){
		static std::default_random_engine e(6);
        static std::uniform_int_distribution<unsigned> u1(1, COL - 2);//0-17 => 1-16
        static std::uniform_int_distribution<unsigned> u2(1, ROW - 2);
        m_Food_x = u1(e);
        m_Food_y = u2(e);
        Wall* m_pWall = Wall::getdata();
        if (m_pWall->getwall(m_Food_x, m_Food_y) == state::S_ROAD){
            m_pWall->setwall(m_Food_x, m_Food_y, state::S_FOOD);
            m_pfoodlabel->move(m_Food_x*20,m_Food_y*20);
			break;
		}
	}
}

Food* Food::getdata() {
    std::call_once(m_flag_food,&Food::initial_data_once);
    return m_fooddata;
}


