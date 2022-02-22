#include "cardwidget.h"


CardWidget::CardWidget(QWidget *parent, int rank, char suit):
    QLabel(parent),
    Card(rank, suit),
    front_(loadFront()),
    back_(loadBack()),
    isShowing_(false)
{

}

CardWidget::CardWidget(QWidget *parent, std::string str):
    CardWidget(parent, Card::getRankFromStr(str), Card::getSuitFromStr(str))
{

}

void CardWidget::turn()
{
    isShowing_ = not isShowing_;
    this->setPixmap(isShowing_ ? front_ : back_);
}

QPixmap CardWidget::loadFront()
{
    std::string filename = Card::toString() + ".png";
    return QPixmap(QString::fromStdString(filename));
}

QPixmap CardWidget::loadBack()
{
    std::string filename = "red_back.png";
    return QPixmap(QString::fromStdString(filename));
}

