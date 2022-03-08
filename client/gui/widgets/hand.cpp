#include "hand.h"

Hand::Hand(QWidget *parent):
    QWidget(parent),
    liftedCard(nullptr)
{}

void Hand::add(OpenedCard *card)
{
    card->setParent(this);
    cards.insert(card);
}

int Hand::size() const
{
    return cards.size();
}

void Hand::placeCards()
{
    QSize cardsSize = getCardsSize(geometry().size());


    int x = 0;
    int y = hover;
    int h = cardsSize.height();
    int w = (*cards.begin())->widthForHeight(h);

    if(geometry().size().width() > cardsSize.width()){
        x = (geometry().size().width() - cardsSize.width()) / 2;
    }

    QRect geometry(x, y, w, h);

    for(OpenedCard* card : cards){
        card->setGeometry(geometry);
        card->raise();
        x += getSpacing(w);
        geometry.moveLeft(x);
    }

}

QSize Hand::getCardsSize(QSize widgetSize)
{
    // Get cards size via card size hint
    QSize cardsSize = sizeHint().shrunkBy(QMargins(0,hover,0,0));

    // Max size
    widgetSize = widgetSize.shrunkBy(QMargins(0,hover,0,0));

    // Max cards size with aspect ratio
    if(getRatio(cardsSize) > getRatio(widgetSize)){
        return QSize(widgetSize.width(), widgetSize.width() / getRatio(cardsSize));
    } else {
        return QSize(getRatio(cardsSize) * widgetSize.height(), widgetSize.height());
    }
}

float Hand::getRatio(QSize s) const
{
    if(s.height() == 0){
        return 0;
    }
    return (float) s.width() / (float) s.height();
}

int Hand::getSpacing(int width) const
{
    return  (1 - overlapPercent / 100) * width;
}

void Hand::moveEvent(QMoveEvent *)
{
    placeCards();
}

void Hand::resizeEvent(QResizeEvent *)
{
    placeCards();
}

QSize Hand::sizeHint() const
{
    // Get cards size via card size hint
    QSize cardsSize;
    for(CardWidget* card : cards){
        if(!cardsSize.isValid()){
            cardsSize = cardsSize.expandedTo(card->sizeHint());
        } else {
            QMargins expand;
            expand.setRight(getSpacing(card->sizeHint().width()));
            cardsSize = cardsSize.grownBy(expand);
        }

    }
    return cardsSize.grownBy(QMargins(0,hover,0,0));
}

QSize Hand::minimumSizeHint() const
{
    // Get cards size via card size hint
    QSize cardsSize;
    for(CardWidget* card : cards){
        if(!cardsSize.isValid()){
            cardsSize = cardsSize.expandedTo(card->minimumSizeHint());
        } else {
            QMargins expand;
            expand.setRight(getSpacing(card->minimumSizeHint().width()));
            cardsSize = cardsSize.grownBy(expand);
        }

    }
    return cardsSize.grownBy(QMargins(0,hover,0,0));
}
