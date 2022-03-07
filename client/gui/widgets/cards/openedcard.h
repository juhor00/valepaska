#ifndef OPENEDCARD_H
#define OPENEDCARD_H

#include "cardwidget.h"
#include "../card.h"
#include <QDebug>

class OpenedCard : public Card, public CardWidget
{
public:
    OpenedCard(int rank, char suit, QWidget *parent = nullptr);
    OpenedCard(std::string str, QWidget *parent = nullptr);





    // CardWidget interface
protected:
    QPixmap loadImage() const override;
};

#endif // OPENEDCARD_H
