#include "closedcard.h"

ClosedCard::ClosedCard(QWidget *parent):
    CardWidget(ClosedCard::loadImage(), parent)
{

}

QPixmap ClosedCard::loadImage() const
{
    std::string filename = ":/resources/red_back.png";
    return QPixmap(QString::fromStdString(filename));
}
