#ifndef SNAKE_H
#define SNAKE_H
#include <QList>
#include <mutex>

class Wall;
struct SnakeNode;


class Snake
{
public:
    static Snake* getdata();
    QList<SnakeNode*> getlistdata();
    void initial();
    bool move(char dir);
    void setdir(char dir);
    char getPreDirect();
    char getNextDirect();
    static unsigned getLevel();
	static unsigned getCore();

private:
    void addNode(unsigned x, unsigned y);
    void deltailnode();
    void destoryPoint();
    void changeGameInfo();
private:
    Snake(Wall* w=nullptr);

    QList<SnakeNode*> m_NodeList;
    SnakeNode* m_phead;
    Wall* m_pWall;
    char m_predirct;
    char m_nextdirct;
    static Snake* m_data;
	static unsigned m_count;
    static unsigned m_level;


    class rememberfree
    {
    public:
        ~rememberfree()
        {
            if (Snake::m_data)
            {
                delete m_data;
            }
        }
    };
    static rememberfree m_free;
    static std::mutex mtx;
    static rememberfree rember;
};

#endif // !SNAKE_H
