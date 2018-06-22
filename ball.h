#ifndef BALL_H
#define BALL_H

#include <QWidget>
#include <QPainter>

class ball : public QWidget
{
    Q_OBJECT
public:
    explicit ball(QWidget *parent = nullptr);
    QRect shape();

private:

    QWidget *p;
    const int ballspeed = 5;
    const int ballshape = 10;
    int x;
    int y;
    int moveX = ballspeed;
    int moveY = ballspeed;


signals:
    void ballMoves(QRect &ball);
    void scored(bool who);

public slots:
    void moveBall();
    void drawBall(QPainter &painter);
    void resetBall();
    void bounce(int type);

};

#endif // BALL_H
