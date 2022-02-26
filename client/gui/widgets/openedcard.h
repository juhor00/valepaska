#ifndef OPENEDCARD_H
#define OPENEDCARD_H

#include "cardwidget.h"
#include "../card.h"

class OpenedCard : public CardWidget, public Card
{
public:
    OpenedCard(int rank, char suit, QWidget *parent = nullptr);
    OpenedCard(std::string str, QWidget *parent = nullptr);


private:

    QPixmap loadImage();


};

#endif // OPENEDCARD_H
