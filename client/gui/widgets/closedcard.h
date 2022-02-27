#ifndef CLOSEDCARD_H
#define CLOSEDCARD_H

#include "cardwidget.h"

class ClosedCard : public CardWidget
{
public:
    ClosedCard(QWidget *parent);




    // CardWidget interface
protected:
    QPixmap loadImage() const override;
};

#endif // CLOSEDCARD_H
