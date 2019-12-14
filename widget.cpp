#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QString>
#include <QMessageBox>
#include <QColor>
#include <QVBoxLayout>
#include <QPushButton>
#include "options.h"
#include "rules.h"



Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1000, 775);
    this->setWindowTitle("Pong");

    _ball = new QRectF(490, 415, 20, 20);
    QRect _left_pad(70, 350, 20, 150);
    QRect _right_pad(910, 350, 20, 150);

    left_pad = new Pads(_left_pad);
    right_pad = new Pads(_right_pad);
    label_1 = new QLabel(this);
    label_2 = new QLabel(this);
    score_label = new QLabel(this);
    ball = new Ball(*_ball);

    Player1 = "Player 1";
    Player2 = "Player 2";

    is1player = false;
    isSound = true;
    bgcolor = true;
    winNum = 10;
    is_ball_in_start_pos = true;

    iTimer = new QTimer(this);
    iTimer->setInterval(12);
    QObject::connect(iTimer, SIGNAL(timeout()), this, SLOT(tick()));


}

Widget::~Widget()
{
    delete iTimer;
    delete left_pad;
    delete right_pad;
    delete _ball;
    delete ball;
    delete label_1;
    delete label_2;
    delete score_label;
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QBrush _green(QColor(20, 135, 14));
    QBrush _black(Qt::black);
    QPen whitepen = QPen(Qt::white, 6, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin);
    if (bgcolor)
        painter.setBrush(_green);
    else
        painter.setBrush(_black);
    painter.drawRect(0, 0, 1000, 775);

    painter.setBrush(Qt::white);
    painter.setPen(whitepen);
    painter.drawRect(left_pad->getPad());
    painter.drawRect(right_pad->getPad());
    painter.drawEllipse(ball->getBall());

    painter.drawLine(3, 0, 3, 775); // left line
    painter.drawLine(997, 0, 997, 775); // right line
    painter.drawLine(0, 3, 1000, 3); // top line
    painter.drawLine(0, 75, 1000, 75); // top border line
    painter.drawLine(0, 772, 1000, 772); // bottom line
    painter.drawLine(500, 75, 500, 775);


    if (paused)
    {
        if (bgcolor)
            painter.setBrush(_green);
        else
            painter.setBrush(_black);
        painter.drawRect(300, 300, 400, 200);
        QFont pfont("Curier", 20, 20);
        pfont.setBold(true);
        painter.setFont(pfont);
        painter.drawText(0, 0, 1000, 750, Qt::AlignCenter, "Game is Paused \n Press P to Resume");
    }

    if (is_ball_in_start_pos)
    {
        // TODO: do not move the ball for 0.5 sec if it's in start position
        /*QEventLoop loop;
        QTimer::singleShot(500, &loop, SLOT(quit()));
        loop.exec();*/
    }

}


void Widget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up)
        right_pad->changeDir(1); // 1 = up, -1 = down
    if (event->key() == Qt::Key_Down)
        right_pad->changeDir(-1);
    if (!is1player)
    {
        if (event->key() == Qt::Key_W)
            left_pad->changeDir(1);
        if (event->key() == Qt::Key_S)
            left_pad->changeDir(-1);
    }
    if (event->key() == Qt::Key_P)
    {
        paused = !paused;
    }
}

void Widget::keyReleaseEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Up || event->key() == Qt::Key_Down)
        right_pad->changeDir(0);
    if (!is1player)
        if(event->key() == Qt::Key_W || event->key() == Qt::Key_S)
            left_pad->changeDir(0);
}


void Widget::Start(QString p1, QString p2)
{
    if (p1 != "")
        Player1 = p1;
    if (p2 != "")
        Player2 = p2;

    QString style = "QLabel { background-color : #094404; color : white; }";
    if (!bgcolor)
        style = "QLabel { background-color : black; color : white; }";
    QFont * font = new QFont();
    font->setBold(true);
    font->setPixelSize(40);

    label_1->setGeometry(3, 7, 440, 65);
    label_1->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
    label_1->setFont(*font);
    label_1->setText(Player1);
    label_1->setStyleSheet(style);

    label_2->setGeometry(547, 7, 446, 65);
    label_2->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    label_2->setFont(*font);
    label_2->setText(Player2);
    label_2->setStyleSheet(style);

    score_label->setGeometry(443, 7, 114, 65);
    score_label->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
    score_label->setFont(*font);
    score_label->setStyleSheet(style);

    left_pad->setPad(70, 350, 20, 150);
    right_pad->setPad(910, 350, 20, 150);

    QString score;
    left_score = 0;
    right_score = 0;
    score = QString::number(left_score) +  " : " + QString::number(right_score);
    score_label->setText(score);

    ball->setBall(*_ball);

    isOver = false;
    paused = false;
    iTimer->start();
    delete font;
    this->show();
}


void Widget::endGame(char winner)
{
    iTimer->stop();
    QString msg = "Game Over! <br>";
    if (winner == 'l')
        msg += Player1;
    else
        msg += Player2;
    msg += " won this game! <br> Do you want to start another game?";
    QMessageBox * mbox = new QMessageBox;
    mbox->setText(msg);
    mbox->setWindowTitle("Ping Pong");
    mbox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int x = mbox->exec();
    delete mbox;
    this->close();
    if (x == QMessageBox::Yes)
        newGame();
}

void Widget::changeStyle()
{
    QString style = "QLabel { background-color : #094404; color : white; }";
    if (!bgcolor)
        style = "QLabel { background-color : black; color : white; }";
    label_1->setStyleSheet(style);
    label_2->setStyleSheet(style);
    score_label->setStyleSheet(style);
}


void Widget::tick()
{
    if (isOver)
        return;
    if (paused)
    {
        repaint();
        return;
    }
    is_ball_in_start_pos = false;
    ball->moveByFrame(left_pad->getPad(), right_pad->getPad());
    left_pad->move();
    right_pad->move();
    if (is1player)
    {
        QRect r = left_pad->getPad();
        QRectF b = ball->getBall();
        if (r.top() > b.y())
            left_pad->changeDir(1);
        else
        if (r.bottom() < b.y())
            left_pad->changeDir(-1);
        else
            left_pad->changeDir(0);

    }
    if (right_score == winNum)
    {
        isOver = true;
        endGame('r');// right player won
    }
    if (left_score == winNum)
    {
        isOver = true;
        endGame('l'); // left player won
    }
    if (ball->inLeftOut())
    {
        right_score++;
        ball->setAngle(0);
        ball->setBall(*_ball);
        is_ball_in_start_pos = true;
    }
    if (ball->inRightOut(1000))
    {
        left_score++;
        ball->setAngle(PI);
        ball->setBall(*_ball);
        is_ball_in_start_pos = true;
    }
    QString score;
    score += QString::number(left_score);
    score += " : ";
    score+= QString::number(right_score);
    score_label->setText(score);
    repaint();
}

void Widget::f2()
{
    paused = true;
    QString msg = "Your game will not be saved! <br> Are you sure you want to start a new game?";
    QMessageBox * mbox = new QMessageBox;
    mbox->setText(msg);
    mbox->setWindowTitle("Ping Pong");
    mbox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int x = mbox->exec();
    delete mbox;
    if (x == QMessageBox::Yes)
    {
        this->close();
        newGame();
    }
}

void Widget::restart()
{
    iTimer->stop();
    QString msg = "Your game will not be saved! <br> Are you sure you want to restart?";
    QMessageBox * mbox = new QMessageBox;
    mbox->setText(msg);
    mbox->setWindowTitle("Ping Pong");
    mbox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int x = mbox->exec();
    delete mbox;
    if (x == QMessageBox::Yes)
        Start(Player1, Player2);
    else
        iTimer->start();
}

void Widget::about()
{
    paused = true;
    QDialog* a = new QDialog(this);
    a->setFixedSize(400, 200);
    QString str ;
    str += "<br><br> <b> Ping Pong </b> <br><br>";
    str.push_back("©");
    str += " 2018 Victoria Beglaryan.";
    str += "<br> All rights reserved. <br>";
    QLabel* n = new QLabel(str, a);
    QLabel * logo = new QLabel(a);
    logo->setPixmap(QPixmap(":/logo.jpg"));
    //n.setText(str);
    n->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    n->setGeometry(220, 20, 150, 200);
    QPushButton * button = new QPushButton("Close", a);
    button->setGeometry(300, 160, 80, 30);
    connect(button, SIGNAL(clicked()), a, SLOT(close()));
    a->exec();
}

void Widget::rules()
{
    paused = true;
    Rules * rule = new Rules(this);
    rule->exec();
}

void Widget::_options()
{
    paused = true;
    Options * op = new Options(this);
    op->exec();
}
