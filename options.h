#ifndef OPTIONS_H
#define OPTIONS_H
#include <QDialog>
#include "widget.h"
#include <QRadioButton>
#include <QGroupBox>
#include <QGridLayout>

class Options : public QDialog
{
    Q_OBJECT
public:
    explicit Options(Widget * parent = 0);
    ~Options();

signals:

public slots:
    void Save();
private:
    Widget * w;
    QRadioButton * BlackBoard;
    QRadioButton * GreenBoard;
    QRadioButton * onePlayer;
    QRadioButton * twoPlayer;
    QRadioButton * soundON;
    QRadioButton * soundOFF;
    QPushButton * save;
    QPushButton * cancel;
    QGridLayout * layout;
    QGroupBox * mode;
    QGroupBox * sound;
    QGroupBox * board;
    QVBoxLayout *vbox1;
    QVBoxLayout * vbox2, * vbox3;
    QHBoxLayout * hbox;
};

#endif // OPTIONS_H

