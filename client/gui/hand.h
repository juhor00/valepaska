#ifndef HAND_H
#define HAND_H

#include <QVector>
#include "cardlayout.h"
#include "widgets/cardwidget.h"


class Hand : public CardLayout
{
public:

    Hand(QWidget *parent = nullptr);
    ~Hand();


    // QLayoutItem interface
public:
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;
    void setGeometry(const QRect &r) override;



private:
    const int SPACING_PERCENT = -10;
    const int HOVER_Y = 20;

};



#endif // HAND_H
