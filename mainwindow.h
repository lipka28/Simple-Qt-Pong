#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QMessageBox>
#include "ball.h"
#include "paddle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    int playerScore;
    int enemyScore;
    bool firstTime = true;
    const int maxScore = 10;

    QWidget *p;
    paddle *player;
    paddle *enemy;
    ball *myBall;
    Ui::MainWindow *ui;
    QTimer *timer;
    bool running = false;

    void resetGame();
    void VictoryCheck();

protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *);

signals:
    void draw(QPainter &painter);
    void reportPos(QPoint &pos);
    void bounce(int choose);

public slots:
    void scored(bool who);

private slots:
    void colisionDetection();


};

#endif // MAINWINDOW_H
