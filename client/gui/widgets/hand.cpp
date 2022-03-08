#include "hand.h"

Hand::Hand(QWidget *parent):
    QWidget(parent),
    liftedCard(nullptr)
{}

void Hand::add(OpenedCard *card)
{
    card->setParent(this);
    connect(card, SIGNAL(hovered(QEnterEvent*)),
            this, SLOT(onCardHover(QEnterEvent*)));
    cards.insert(card);
}

int Hand::size() const
{
    return cards.size();
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
    return cardsSize.grownBy(QMargins(0,getHover(cardsSize.height()),0,0));
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
    return cardsSize.grownBy(QMargins(0,getHover(cardsSize.height()),0,0));
}

void Hand::moveEvent(QMoveEvent *)
{
    placeCards();
}

void Hand::resizeEvent(QResizeEvent *)
{
    placeCards();
}

void Hand::onCardHover(QEnterEvent* event)
{
    CardWidget* card = dynamic_cast<CardWidget*>(sender());
    qDebug() << "Hover " << card << event;

    if(event->position().y() < card->geometry().height() - getHover(card->geometry().height())){

        // Already lifted
        if(liftedCard == card){
            qDebug() << "Already lifted";
            return;
        // Other card is lifted
        } else if(liftedCard){
            qDebug() << "Lowering card " << liftedCard;
            QRect geometry = liftedCard->geometry().translated(0, getHover(liftedCard));
            liftedCard->setGeometry(geometry);
        }

        qDebug() << "Lifting card " << card;
        QRect geometry = card->geometry().translated(0, -getHover(card));
        card->setGeometry(geometry);

        liftedCard = card;
    }
}

void Hand::placeCards()
{
    QSize cardsSize = getCardsSize(geometry().size());


    int x = 0;
    int y = cardsSize.height() - withoutHover(cardsSize).height();
    int h = withoutHover(cardsSize).height();
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
    QSize cardsSize = sizeHint();

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

int Hand::getHover(int height) const
{
    return hoverPercent / 100 * height;
}

int Hand::getHover(CardWidget *card) const
{
    return getHover(card->geometry().height());
}

QSize Hand::withoutHover(QSize s) const
{
    return QSize(s.width(), 100*s.height() / (hoverPercent + 100));
}
