#ifndef SNAKE_H
#define SNAKE_H
#include <QList>
#include <mutex>

class Wall;
struct SnakeNode;

class Snake {
public:
    ~Snake();
    Snake(const Snake&) = delete;
    Snake(Snake&&) = delete;
    Snake& operator=(const Snake&) = delete;
    Snake& operator=(Snake&&) = delete;

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
    static void initial_data_once();
    QList<SnakeNode*> m_NodeList;
    SnakeNode* m_phead;
    Wall* m_pWall;
    char m_predirct;
    char m_nextdirct;
    static Snake* m_data;
	static unsigned m_count;
    static unsigned m_level;

    class RememberFree {     //RAII
    public:
        ~RememberFree(){
            if (Snake::m_data){
                delete m_data;
            }
        }
    };

    static std::once_flag m_flag_snake;
    static RememberFree m_free;
};

#endif // !SNAKE_H
