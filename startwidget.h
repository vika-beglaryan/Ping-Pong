#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include "widget.h"


class StartWidget : public QWidget
{
    Q_OBJECT
public:
    StartWidget(QWidget * parent = 0 );
    Widget * getWidget();
    ~StartWidget();
    void keyPressEvent(QKeyEvent *);
public slots:
    void StartTheGame();
private:
    QLabel * label;
    QLineEdit * leftPlayer;
    QLineEdit * rightPlayer;
    QPushButton * button;
    Widget * w;

};

#endif // STARTWIDGET_H
