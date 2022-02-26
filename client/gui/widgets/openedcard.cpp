#include "openedcard.h"


OpenedCard::OpenedCard(int rank, char suit, QWidget *parent):
    Card(rank, suit),
    CardWidget(loadImage(), parent)
{}

OpenedCard::OpenedCard(std::string str, QWidget *parent):
    Card(str),
    CardWidget(loadImage(), parent)
{}

QPixmap OpenedCard::loadImage()
{
    qDebug() << QString::fromStdString(toString());
    std::string filename = ":/resources/"+toString() + ".png";
    QPixmap pix = QString::fromStdString(filename);

    return pix.scaledToWidth(DEFAULT_W);
}
