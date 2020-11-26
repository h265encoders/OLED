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
    void upDraw(QString iconPath,double scale);

private:
    QString path = nullptr;
    double scl = 1;
    void paintEvent(QPaintEvent *);

signals:

public slots:
};

#endif // HICON_H
