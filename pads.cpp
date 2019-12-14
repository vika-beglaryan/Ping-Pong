#include "pads.h"
#include <QDebug>

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}


Pads::Pads(QRect rect)
{
    pad = new QRect(rect);
    speed = 5;
    dir = 0;
}


void Pads::move()
{
    if (dir > 0)
    {
        int dif = min(pad->top() - 75, speed);
        pad->setTop(pad->top() - dif);
        pad->setBottom(pad->bottom() - dif);
    }
    if (dir < 0)
    {
        int dif = min(775 - pad->bottom(), speed);
        pad->setTop(pad->top() + dif);
        pad->setBottom(pad->bottom() + dif);
    }
}

void Pads::changeDir(int x)
{
    dir = x;
}

void Pads::setPad(int x, int y, int w, int h)
{
    pad->setRect(x, y, w, h);
}

Pads::~Pads()
{
    delete pad;
}

