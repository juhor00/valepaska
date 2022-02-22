#include "openedcard.h"


OpenedCard::OpenedCard(QWidget *parent, int rank, char suit):
    CardWidget(parent, loadImage()),
    Card(rank, suit)
{

}

OpenedCard::OpenedCard(QWidget *parent, std::string str):
    CardWidget(parent, loadImage()),
    Card(str)
{

}

QPixmap OpenedCard::loadImage()
{
    std::string filename = Card::toString() + ".png";
    return QPixmap(QString::fromStdString(filename));
}
