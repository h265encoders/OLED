#ifndef GPIO_H
#define GPIO_H
#include "own.h"
#include "Link.h"
#include <QTimer>

class OwnGPIO : public Owns
{
public:
    explicit OwnGPIO(Owns *parent = 0);
    void init(const QVariantList &param = QVariantList());

private:
    LinkObject *gpio = nullptr;
    QTimer *pressTimer = nullptr;
    QString btnName = nullptr;

public slots:
    void onGPIO(QString type, QVariant info);
};

#endif // GPIO_H
