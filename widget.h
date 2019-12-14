#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRect>
#include <QPaintEvent>
#include <QPainter>
#include <QBrush>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QFont>
#include <process.h>
#include <stdio.h>
#include <Windows.h>
#include <QMenu>
#include <QMenuBar>
#include "ball.h"
#include "pads.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    void Start(QString p1, QString p2);
    void endGame(char);
    QString getPlayer1(){ return Player1;}
    QString getPlayer2(){ return Player2;}
    bool is1player;
    bool isSound;
    bool bgcolor; // true = green, false = black
    void playSound(bool x)
    {
        if (x)
        {
            ball->playSound = true;
            isSound = true;
        }
        else
        {
            ball->playSound = false;
            isSound = false;
        }
    }
    void changeStyle();
    QString Player1;
    QString Player2;
    void setNumber(int x){
        winNum = x;
    }

signals:
    void newGame();
public slots:
    void tick();
    void f2();
    void restart();
    void about();
    void rules();
    void _options();

private:
    Ui::Widget *ui;
    Pads* left_pad;
    Pads* right_pad;
    QLabel * label_1, * label_2, * score_label;
    Ball* ball;
    QTimer * iTimer;
    QRectF* _ball;
    int left_score;
    int right_score;
    bool isOver;
    bool paused;
    int winNum;
    bool is_ball_in_start_pos;

};

#endif // WIDGET_H
