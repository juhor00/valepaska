#include "openedcard.h"


OpenedCard::OpenedCard(int rank, char suit, QWidget *parent):
    Card(rank, suit),
    CardWidget(OpenedCard::loadImage(), parent)
{}

OpenedCard::OpenedCard(std::string str, QWidget *parent):
    Card(str),
    CardWidget(OpenedCard::loadImage(), parent)
{}

QPixmap OpenedCard::loadImage() const
{
    std::string filename = ":/resources/"+toString() + ".png";
    return QPixmap(QString::fromStdString(filename));
}
