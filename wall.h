#pragma once

#include <mutex>
#include <array>
#include <QFrame>

class QLabel;
class Snake;

enum :char {UP='w',DOWN='s',LEFT='a',RIGHT='d'};
enum :char{ ROW = 25, COL = 18 };
enum state :char{S_SNAKE,S_TAIL,S_WALL,S_FOOD,S_ROAD};

struct SnakeNode
{
    unsigned m_nodex;
    unsigned m_nodey;
    QLabel *m_plabel;
    SnakeNode(unsigned x,unsigned y,QLabel* p=nullptr):m_nodex(x),m_nodey(y),m_plabel(p){}
    ~SnakeNode();
};

class Wall:public QFrame
{
public:
    static Wall* getdata();
    void initial();
    void setwall(size_t x, size_t y, char c);
    char getwall(size_t x, size_t y);
    Wall(const Wall&) = delete;
    Wall& operator=(const Wall&) = delete;
    Wall(Wall&&) = delete;
    Wall& operator==(Wall&&) = delete;
    ~Wall();
private:
    Wall();

    void paintEvent(QPaintEvent *);
    static Wall* m_Walldata;
    std::array<std::array<char, ROW>, COL> m_array;
    Snake* m_pSnake;

    class rememberfree
    {
    public:
        ~rememberfree()
        {
            if (Wall::m_Walldata)
            {
                delete m_Walldata;
            }
        }
    };
    static std::mutex mtx;
    static rememberfree rember;
}; 



