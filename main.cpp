#include "widget.h"
#include <QApplication>
#include "startwidget.h"
#include <QObject>
#include <QSize>
#include <iostream>
#include <QDebug>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWidget *st;
    st = new StartWidget();
    st->show();

    Widget * w = st->getWidget();
    QMenuBar mnuBar(w);
    QMenu* file = new QMenu("&File", w);
    QMenu* tools = new QMenu("&Tools", w);
    QMenu* help = new QMenu("&Help", w);

   // file->addAction("New", w, SIGNAL(newGame()));
    file->addAction("New Game", w, SLOT(f2()), Qt::Key_F2);
    file->addAction("Restart", w, SLOT(restart()), Qt::Key_R);
    file->addAction("Quit", w, SLOT(close()), Qt::ALT + Qt::Key_X);

    tools->addAction("Options", w, SLOT(_options()), Qt::Key_O);

    help->addAction("About", w, SLOT(about()));
    help->addAction("Rules", w, SLOT(rules()), Qt::Key_F1);

    mnuBar.addMenu(file);
    mnuBar.addMenu(tools);
    mnuBar.addMenu(help);

    return a.exec();
}


