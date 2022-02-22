#include "closedcard.h"

ClosedCard::ClosedCard(QWidget *parent):
    CardWidget(parent, loadImage())
{

}

QPixmap ClosedCard::loadImage()
{
    std::string filename = "red_back.png";
    return QPixmap(QString::fromStdString(filename));
}
