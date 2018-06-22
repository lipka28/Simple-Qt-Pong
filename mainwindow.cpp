#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "time.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));

    playerScore = 0;
    enemyScore = 0;

    centralWidget()->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);

    p = parent;
    setFixedSize(800,600);
    move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);


    timer = new QTimer(this);
    myBall = new ball(this);
    player = new paddle(this,true);
    enemy = new paddle(this,false);

    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(repaint()));
    QObject::connect(timer,&QTimer::timeout,myBall,&ball::moveBall);
    QObject::connect(timer,&QTimer::timeout,this,&MainWindow::colisionDetection);

    QObject::connect(myBall,&ball::ballMoves,enemy,&paddle::AIProce);

    QObject::connect(this,&MainWindow::draw,myBall,&ball::drawBall);
    QObject::connect(this,&MainWindow::draw,player,&paddle::drawPaddle);
    QObject::connect(this,&MainWindow::draw,enemy,&paddle::drawPaddle);
    QObject::connect(this,&MainWindow::reportPos,player,&paddle::movePaddle);
    QObject::connect(this,&MainWindow::bounce,myBall,&ball::bounce);

    QObject::connect(myBall,&ball::scored,this,&MainWindow::scored);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetGame()
{
    myBall->resetBall();
    player->paddleReset();
    enemy->paddleReset();
    playerScore = 0;
    enemyScore = 0;
    timer->stop();
    running = false;
    this->update();

}

void MainWindow::VictoryCheck()
{
    if(playerScore >= maxScore){
        QMessageBox::information(this,"Victory","You Won!!");
        resetGame();
    }
    else if(enemyScore >= maxScore){
        QMessageBox::information(this,"Defeat","You lost... Better luck next time!");
        resetGame();
    }

}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton && running == false){
        timer->start(16);
        running = true;


    }
    else if (e->button() == Qt::LeftButton && running == true){
        timer->stop();
        running = false;
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen(Qt::white,3,Qt::DashLine);

    painter.fillRect(rect(), QBrush(QColor(Qt::black)));
    painter.setPen(pen);
    painter.drawLine(405,0,405,600);

    painter.setPen(Qt::white);
    painter.setBrush(QBrush(QColor(Qt::white)));

    QString pl = "Palyer: "+QString::number(playerScore);
    QString ai = "Computer: "+QString::number(enemyScore);

    painter.drawText(185,50,pl);
    painter.drawText(555,50,ai);

    emit draw(painter);

    if(firstTime){
        QMessageBox::information(this,"Welcome!","One click to start or pause.\n Double click to reset.\n First with 10 points wins!!");
        firstTime = false;
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint point = e->pos();
    emit reportPos(point);
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    resetGame();
}

void MainWindow::scored(bool who)
{
    if(who){
        enemyScore++;
        myBall->resetBall();
    }
    else{
        playerScore++;
        myBall->resetBall();
    }

    VictoryCheck();

}

void MainWindow::colisionDetection()
{

    if(myBall->shape().x() < player->shape().x()+player->shape().width() && myBall->shape().y()+myBall->shape().height() > player->shape().y() && myBall->shape().y() < player->shape().y()+player->shape().height())emit bounce(rand()%2);
    if(myBall->shape().x()+myBall->shape().width() > enemy->shape().x() && myBall->shape().y()+myBall->shape().height() > enemy->shape().y() && myBall->shape().y() < enemy->shape().y()+enemy->shape().height())emit bounce(rand()%2);

}

