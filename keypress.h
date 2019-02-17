#ifndef KEYPRESS_H
#define KEYPRESS_H

#include <QObject>

class KeyPress : public QObject
{

    Q_OBJECT

public:
    explicit KeyPress(QObject *parent = 0);

    Q_INVOKABLE void virtKeyPress(const int& Char);

signals:
    void virtKeyPressed(const int& source);

private:
    int vKey;
};

#endif // KEYPRESS_H
