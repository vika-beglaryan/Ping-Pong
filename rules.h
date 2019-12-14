#ifndef RULES_H
#define RULES_H
#include <QDialog>
#include <QWidget>
#include <QLabel>

class Rules : public QDialog
{
    Q_OBJECT
public:
    Rules(QWidget * parent = nullptr);
    ~Rules();

public slots:
    void change();
private:
    QLabel * lab;
    QPushButton * close;
    QPushButton * prev;
    bool ind;
};

#endif // RULES_H
