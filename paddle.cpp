#include "paddle.h"

paddle::paddle(QWidget *parent, bool player) : QWidget(parent)
{
    p = parent;
    human = player;
    if(human == true){
        posX = buffer;
        posY = p->rect().height()/2 - pHeight/2;
        posXBack = posX;
        posYBack = posY;
    }else{

        posX = p->rect().width() - buffer - pWidth;
        posY = p->rect().height()/2-pHeight/2;
        posXBack = posX;
        posYBack = posY;

    }

}

QRect paddle::shape()
{
    QRect out(posX,posY,pWidth,pHeight);
    return out;
}

void paddle::paddleReset()
{
    posX = posXBack;
    posY = posYBack;
}

void paddle::checkBasicColisions()
{
    if(posY < 0)posY = 0;
    if(posY+pHeight > p->rect().height())posY = p->rect().height()-pHeight;
}

void paddle::drawPaddle(QPainter &painter)
{
    painter.drawRect(posX,posY,pWidth,pHeight);

}

void paddle::movePaddle(QPoint &pos)
{
  posY = pos.y()-(pHeight/2);
  checkBasicColisions();
}

void paddle::AIProce(QRect &ball)
{
    if(ball.y() > posY+pHeight/2)posY += AiSpeed;
    if(ball.y() < posY+pHeight/2)posY -= AiSpeed;
    checkBasicColisions();

}

