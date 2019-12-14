#include "rules.h"
#include <QPushButton>

Rules::Rules(QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(480, 400);
    ind = false;
    lab = new QLabel(this);
    lab->setPixmap(QPixmap(":/rule1.png"));
    prev = new QPushButton("Next", this);
    close = new QPushButton("Close", this);
    prev->setGeometry(40, 360, 100, 20);
    close->setGeometry(350, 360, 100, 20);
    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    connect(prev, SIGNAL(clicked()), this, SLOT(change()));


}

Rules::~Rules()
{
    delete lab;
    delete prev;
    delete close;
}


void Rules::change()
{
    if (!ind)
    {
        lab->setPixmap(QPixmap(":/rule2.png"));
        ind = true;
        prev->setText("Previous");
    }
    else
    {
        lab->setPixmap(QPixmap(":/rule1.png"));
        ind = false;
        prev->setText("Next");
    }
}
