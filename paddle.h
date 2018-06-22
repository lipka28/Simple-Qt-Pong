#ifndef PADDLE_H
#define PADDLE_H

#include <QWidget>
#include <QPainter>

class paddle : public QWidget
{
    Q_OBJECT
public:
    explicit paddle(QWidget *parent = nullptr,bool player = true);
    QRect shape();
    void paddleReset();

private:

    QWidget *p = NULL;
    bool human;

    const int buffer = 5;

    int posXBack;
    int posYBack;

    int posX;
    int posY;

    const int pWidth = 10;
    const int pHeight = 80;
    const int AiSpeed = 7;

    void checkBasicColisions();

signals:


public slots:
    void drawPaddle(QPainter &painter);
    void movePaddle(QPoint &pos);
    void AIProce(QRect &ball);


};

#endif // PADDLE_H
