#include "startwidget.h"
#include <QDebug>
#include <QMenu>
#include <QMenuBar>

StartWidget::StartWidget(QWidget * parent) : QWidget(parent)
{
    w = new Widget();



    this->setFixedSize(250, 250);
    label = new QLabel(this);
    leftPlayer = new QLineEdit(this);
    rightPlayer = new QLineEdit(this);
    button = new QPushButton(this);

    label->setGeometry(20, 20, 200, 50);
    leftPlayer->setGeometry(20, 80, 200, 30);
    rightPlayer->setGeometry(20, 130, 200, 30);
    button->setGeometry(90, 200, 75, 30);
    button->setText("OK");
    label->setText("Enter the names of players <br> and press the button to start");

    QObject::connect(button, SIGNAL(released()), this, SLOT(StartTheGame()));
    QObject::connect(w, SIGNAL(newGame()), this, SLOT(show()));

}

Widget *StartWidget::getWidget()
{
    return w;
}

StartWidget::~StartWidget()
{
    delete leftPlayer;
    delete rightPlayer;
    delete button;
    delete label;
    delete w;
}

void StartWidget::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Enter)
        StartTheGame();
}


void StartWidget::StartTheGame()
{
    QString player1 = leftPlayer->text();
    QString player2 = rightPlayer->text();
    this->hide();
    w->Start(player1, player2);
    w->show();
}


