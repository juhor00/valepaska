#ifndef HAND_H
#define HAND_H

#include <QWidget>
#include <unordered_set>
#include "openedcard.h"

class Hand : public QWidget
{
public:
    Hand(QWidget *parent = nullptr);
    void add(OpenedCard* card);
    int size() const;




private:

    void placeCards();
    QSize getCardsSize(QSize widgetSize);
    float getRatio(QSize s) const;
    int getSpacing(int width) const;
    int getHover(int height) const;
    QSize withoutHover(QSize s) const;

    std::unordered_set<OpenedCard*> cards;
    const float overlapPercent = 20;
    const float hoverPercent = 20;
    CardWidget* liftedCard;


    // QWidget interface
protected:
    void moveEvent(QMoveEvent *) override;
    void resizeEvent(QResizeEvent *) override;

    // QWidget interface
public:
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
};

#endif // HAND_H
