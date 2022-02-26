#include "openedcard.h"


OpenedCard::OpenedCard(int rank, char suit, QWidget *parent):
    CardWidget(loadImage(), parent),
    Card(rank, suit)
{}

OpenedCard::OpenedCard(std::string str, QWidget *parent):
    CardWidget(loadImage(), parent),
    Card(str)
{}

QPixmap OpenedCard::loadImage()
{
    std::string filename = Card::toString() + ".png";
    return QPixmap(QString::fromStdString(filename));
}
