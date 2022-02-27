#ifndef HAND_H
#define HAND_H

#include <QLayout>
#include <QVector>
#include <QDebug>
#include <QString>
#include "widgets/cardwidget.h"

const int SPACING_PERCENT = -10;
const int HOVER_Y = 20;

class Hand : public QLayout
{
public:

    Hand(QWidget *parent = nullptr);
    ~Hand();


    // QLayoutItem interface
public:
    QSize sizeHint() const override;
    QSize minimumSize() const override;
    void setGeometry(const QRect &r) override;


    // QLayout interface
public:
    void addItem(QLayoutItem *) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    int count() const override;
    int spacing() const override;
    void setSpacing(int s) override;



private:

    QVector<QLayoutItem*> items_;
    int spacing_;

};



#endif // HAND_H
