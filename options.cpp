#include "options.h"
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QInputDialog>




Options::Options(Widget *parent) : QDialog(parent), w(parent)
{
    layout = new QGridLayout(this);

    onePlayer = new QRadioButton("1 Player");
    twoPlayer = new QRadioButton("2 Player");
    if (w->is1player)
        onePlayer->setChecked(true);
    else
        twoPlayer->setChecked(true);
    mode = new QGroupBox("Mode");
    vbox1 = new QVBoxLayout;
    vbox1->addWidget(onePlayer);
    vbox1->addWidget(twoPlayer);
    mode->setLayout(vbox1);
    layout->addWidget(mode, 0, 0);

    soundON = new QRadioButton("ON");
    soundOFF = new QRadioButton("OFF");
    sound = new QGroupBox("Sound");
    if (w->isSound)
        soundON->setChecked(true);
    else
        soundOFF->setChecked(true);
    vbox2 = new QVBoxLayout;
    vbox2->addWidget(soundOFF);
    vbox2->addWidget(soundON);
    sound->setLayout(vbox2);
    layout->addWidget(sound, 0, 1);

    save = new QPushButton("Save");
    cancel = new QPushButton("Cancel");
    connect(save, SIGNAL(clicked()), this, SLOT(Save()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(close()));

    hbox = new QHBoxLayout();
    hbox->addWidget(save);
    hbox->addWidget(cancel);
    layout->addLayout(hbox, 1, 1);

    BlackBoard = new QRadioButton("Black");
    GreenBoard = new QRadioButton("Green");
    board = new QGroupBox("Board");
    BlackBoard->setStyleSheet("QRadioButton {color: black; font: bold}");
    GreenBoard->setStyleSheet("QRadioButton {color : rgb(20, 135, 14); font: bold}");
    if (w->bgcolor)
        GreenBoard->setChecked(true);
    else
        BlackBoard->setChecked(true);
    vbox3 = new QVBoxLayout;
    vbox3->addWidget(GreenBoard);
    vbox3->addWidget(BlackBoard);
    board->setLayout(vbox3);
    layout->addWidget(board, 1, 0);
}


Options::~Options()
{
    delete sound;
    delete onePlayer;
    delete twoPlayer;
    delete soundON;
    delete soundOFF;
    delete save;
    delete cancel;
    delete layout;
    delete mode;
    delete vbox1;
    delete vbox2;
    delete vbox3;
    delete BlackBoard;
    delete GreenBoard;
    delete w;
}

void Options::Save()
{
    if (onePlayer->isChecked())
    {
        if (!w->is1player)
        {
            w->is1player = true;
            w->Start(w->Player1, w->Player2);
        }
    }
    else
    {
        if (w->is1player)
        {
            w->is1player = false;
            w->Start(w->Player1, w->Player2);
        }
    }

    if (soundON->isChecked())
        w->playSound(true);
    else
        w->playSound(false);

    if (BlackBoard->isChecked())
        w->bgcolor = false;
    else
        w->bgcolor = true;
    w->changeStyle();

    this->close();
}
