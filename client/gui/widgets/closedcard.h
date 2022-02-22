#ifndef CLOSEDCARD_H
#define CLOSEDCARD_H

#include "cardwidget.h"

class ClosedCard : public CardWidget
{
public:
    ClosedCard(QWidget *parent);

private:

    QPixmap loadImage();
};

#endif // CLOSEDCARD_H
