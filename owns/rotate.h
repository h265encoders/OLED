#ifndef ROTATE_H
#define ROTATE_H
#include "own.h"
#include "Link.h"
#include <QTimer>

class OwnROTATE : public Owns
{
public:
    explicit OwnROTATE(Owns *parent = 0);
    void init(const QVariantList &param = QVariantList());

};

#endif // ROTATE_H
