#include "closedcard.h"

ClosedCard::ClosedCard(QWidget *parent):
    CardWidget(loadImage(), parent)
{

}

QPixmap ClosedCard::loadImage()
{
    std::string filename = "red_back.png";
    return QPixmap(QString::fromStdString(filename));
}
