
#pragma once
#include <QMainWindow>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void flushGameInfo();
    void gameEnd();
    void gameStart();
    void gamePause();
    void autoMoveEvent();

private:
    Ui::MainWindow *ui;
    QTimer *m_ptimer;
    bool m_gametag;
};

