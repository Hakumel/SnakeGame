#pragma once
#include <mutex>
class QLabel;
class Food
{
public:
    QLabel* getlabel();
	void setFood();
	static Food* getdata();
    ~Food();

private:
    Food(QLabel* plabel);

    unsigned m_Food_x;
    unsigned m_Food_y;
    QLabel * m_pfoodlabel;
	static Food* m_fooddata;

    class rememberfree
    {
    public:
        ~rememberfree()
        {
            if (Food::m_fooddata)
            {
                delete m_fooddata;
            }
        }
    };
	static rememberfree rember;
	static std::mutex mtx;
};
