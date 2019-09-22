#pragma once
#include <mutex>

class QLabel;

class Food {
public:
    ~Food();
    Food(const Food&) = delete;
    Food(Food&&) = delete;
    Food& operator=(const Food&) = delete;
    Food& operator=(Food&&) = delete;
    QLabel* getlabel();
	void setFood();
    static Food* getdata();

private:
    Food(QLabel* plabel);
    static void initial_data_once();

    class RememberFree {   //RAII
    public:
        ~RememberFree() {
            if (Food::m_fooddata) {
                delete m_fooddata;
            }
        }
    };

    unsigned m_Food_x;
    unsigned m_Food_y;
    QLabel * m_pfoodlabel;
    static std::once_flag m_flag_food;
	static Food* m_fooddata;
    static RememberFree m_free;

};
