#ifndef HICON_H
#define HICON_H

#include <QWidget>
#include <QPainter>
#include <QDebug>

class InputIcon : public QWidget
{
    Q_OBJECT
public:
    explicit InputIcon(QWidget *parent = nullptr);
    void upDraw(QString iconPath,int rotate,double scale);

private:
    QString path = nullptr;
    int rot = 0;
    double scl = 1;
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // HICON_H
