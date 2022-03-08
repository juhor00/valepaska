#include "hand.h"

Hand::Hand(QWidget *parent) : QWidget(parent)
{}

void Hand::add(CardWidget *card)
{
    cards.push_back(card);
}

int Hand::size() const
{
    return cards.size();
}

void Hand::placeCards()
{
    QSize cardsSize = getCardsSize(geometry().size());
    qDebug() << "Cards size: " << cardsSize;
}

QSize Hand::getCardsSize(QSize widgetSize)
{
    if(cards.empty()){
        return QSize();
    }
    // Get cards size via card size hint
    QSize cardsSize;
    for(CardWidget* card : cards){
        if(!cardsSize.isValid()){
            qDebug() << "Card size hint: " << card->sizeHint();
            cardsSize = cardsSize.expandedTo(card->sizeHint());
        } else {
            QMargins expand;
            expand.setRight(card->sizeHint().width() * (1 - overlapPercent / 100));
            cardsSize = cardsSize.grownBy(expand);
        }

        qDebug() << "Cards size (hint): " << cardsSize;
    }

    if(getRatio(cardsSize) > getRatio(widgetSize)){ // height limits
        return QSize(getRatio(cardsSize) * widgetSize.height(), widgetSize.height());
    } else {
        return QSize(widgetSize.width(), widgetSize.width() / getRatio(cardsSize));
    }
}

float Hand::getRatio(QSize s) const
{
    if(s.height() == 0){
        return 0;
    }
    return (float) s.width() / (float) s.height();
}

void Hand::moveEvent(QMoveEvent *)
{
    placeCards();
}

void Hand::resizeEvent(QResizeEvent *)
{
    placeCards();
}
