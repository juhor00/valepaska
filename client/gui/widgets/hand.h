#ifndef HAND_H
#define HAND_H

#include <QWidget>
#include <QVector>
#include "cardwidget.h"

class Hand : public QWidget
{
public:
    Hand(QWidget *parent = nullptr);
    void add(CardWidget* card);
    int size() const;


private:

    void placeCards();
    QSize getCardsSize(QSize widgetSize);
    float getRatio(QSize s) const;

    QVector<CardWidget*> cards;
    const float overlapPercent = 10;


    // QWidget interface
protected:
    void moveEvent(QMoveEvent *) override;
    void resizeEvent(QResizeEvent *) override;
};

#endif // HAND_H
