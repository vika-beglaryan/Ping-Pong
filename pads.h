#ifndef PADS_H
#define PADS_H

#include <QRect>

class Pads
{
public:
    Pads(QRect);
    void move();
    void changeDir(int x);
    QRect getPad()
    {
        return *pad;
    }
    void setPad(int, int, int, int);
    ~Pads();
private:
    QRect * pad;
    int speed;
    int dir;
};

#endif // PADS_H
