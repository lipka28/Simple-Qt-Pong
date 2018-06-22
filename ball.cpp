#include "ball.h"

ball::ball(QWidget *parent) : QWidget(parent)
{
    p = parent;
    x = p->rect().width()/2;
    y = p->rect().height()/2;

}

QRect ball::shape()
{
    QRect out(x,y,ballshape,ballshape);
    return out;
}

void ball::moveBall()
{
    if(x <= 0){
        emit scored(true);
    }else if(x+ballshape >= p->rect().width()){
        emit scored(false);
    }
    if(y <= 0 || y+ballshape >= p->rect().height())moveY *= -1;

    x += moveX;
    y += moveY;

    QRect myRect(x,y,ballshape,ballshape);
    emit ballMoves(myRect);
}

void ball::drawBall(QPainter &painter)
{
    painter.drawEllipse(x,y,ballshape,ballshape);
}

void ball::resetBall()
{
    x = p->rect().width()/2;
    y = p->rect().height()/2;
    if(rand()%2){
    moveX = ballspeed;
    moveY = ballspeed;
    }
    else{
    moveX = -1*ballspeed;
    moveY = -1*ballspeed;
    }
}

void ball::bounce(int type)
{
    switch (type) {
    case 0:
        moveX *= -1.5;
        moveY = -1*(moveY+1);
        x += moveX;
        y += moveY;
        break;

    case 1:
        moveX *= -1;
        moveY = -1*(moveY+6);
        x += moveX;
        y += moveY;
        break;
    default:
        break;
    }
}

