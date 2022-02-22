#ifndef OPENEDCARD_H
#define OPENEDCARD_H

#include "cardwidget.h"
#include "../card.h"

class OpenedCard : public CardWidget, public Card
{
public:
    OpenedCard(QWidget *parent, int rank, char suit);
    OpenedCard(QWidget *parent, std::string str);

private:

    QPixmap loadImage();


};

#endif // OPENEDCARD_H
