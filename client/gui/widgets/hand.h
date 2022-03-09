#ifndef HAND_H
#define HAND_H

#include <QWidget>
#include <set>
#include "openedcard.h"

class Hand : public QWidget
{
    Q_OBJECT
public:

    Hand(QWidget *parent = nullptr);
    void add(OpenedCard* card);
    int size() const;

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;



protected:
    void moveEvent(QMoveEvent *) override;
    void resizeEvent(QResizeEvent *) override;


private slots:

    void onCardHover(QPointF position);
    void onCardHoverLeave();

private:

    void placeCards();
    QSize getCardsSize(QSize widgetSize);

    float getRatio(QSize s) const;
    int getSpacing(int width) const;

    int getHover(int height) const;
    int getHover(CardWidget* card) const;
    QSize withoutHover(QSize s) const;


    std::set<OpenedCard*> cards;
    const float overlapPercent = 20;
    const float hoverPercent = 20;

    CardWidget* liftedCard;


};

#endif // HAND_H
