#ifndef DECK_H
#define DECK_H

#include "cardlayout.h"


class CardStack : public CardLayout
{
public:
    CardStack(QWidget* parent = nullptr);



    // QLayoutItem interface
public:
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &r) override;

private:

    int spacingX() const;
    int spacingY() const;
    const double SPACING_X = 89;
    const double SPACING_Y = 90;
    const int HOVER_Y = 20;
};

#endif // DECK_H
