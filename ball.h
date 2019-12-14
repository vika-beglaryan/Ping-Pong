#ifndef BALL_H
#define BALL_H
#include <QRectF>
#include <QObject>
#include <QtMultimedia/QMediaPlayer>
#define PI acos(-1.0)
#define PI_2 acos(0.0)

class Ball
{
public:
    Ball(const QRectF bounds, double _speed = 8, double _angle = 0);
    void moveByFrame(QRect leftPaddleBounds, QRect rightPaddleBounds);
    bool inLeftOut()
    {
        return ball->left() <= 0;
    }
    bool inRightOut(double fieldWidth)
    {
        return ball->right() >= fieldWidth;
    }
    void setAngle(double);
    QRectF getBall()
    {
        return *ball;
    }
    void setBall(QRectF);
    bool playSound;
    ~Ball();
private:
    double angle;  // 0 <= angle < 2 * PI
    QRectF* ball;
    double speed;
    QMediaPlayer *player;
    void changeAngle();
};

#endif // BALL_H


