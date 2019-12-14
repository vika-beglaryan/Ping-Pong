#include "ball.h"
#include <ctime>


Ball::Ball(const QRectF bounds, double _speed, double _angle)
{
    ball = new QRectF(bounds);
    angle = _angle;
    speed = _speed;
    srand(time_t(NULL));
    player = new QMediaPlayer();
    player->setMedia(QUrl("qrc:/pong_mp3.mp3"));

}

void Ball::moveByFrame(QRect leftPaddleBounds,  QRect rightPaddleBounds)
{
    const double dx = speed * cos(angle);
    const double dy = speed * sin(angle);
    ball->setLeft(ball->left() + dx);
    ball->setRight(ball->right() + dx);
    ball->setTop(ball->top() + dy);
    ball->setBottom(ball->bottom() + dy);

    // Bounce from the top and bottom edges
    if (ball->top() <= 75 || ball->bottom() >= 775)
    {
        setAngle(-angle);
    }

    // Bounce from the paddles
    if (ball->intersects(leftPaddleBounds))
    {

        ball->setLeft(90);
        ball->setRight(110);
        changeAngle();
        if (playSound)
            player->play();

    }
    if (ball->intersects(rightPaddleBounds))
    {

        ball->setLeft(890);
        ball->setRight(910);
        changeAngle();
        if (playSound)
            player->play();
    }

}

void Ball::setAngle(double _angle)
{
    angle = fmod(_angle, 2 * PI);
}

void Ball::setBall(QRectF _ball)
{
    ball->setRect(_ball.x(), _ball.y(), _ball.width(), _ball.height());
}


Ball::~Ball()
{
    delete ball;
    delete player;
}


void Ball::changeAngle()
{
    const double deviation = static_cast<double>(((rand() % 200) - 100) / 1000.0 * PI);
    double angl = fmod(-angle + PI + deviation, 2 * PI);
    // TODO: get rid of unsafe comparison of floats
    if (angl == 0 || abs(angl) == PI_2 || abs(angl) == PI || abs(angl) == PI + PI_2)
    {
           angl += 0.05;
    }
    angle = angl;
}


