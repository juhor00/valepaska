#include "cardlayout.h"

CardLayout::CardLayout(QWidget* parent):
    QLayout(parent)
{
    CardLayout::setSpacing(0);
}

CardLayout::~CardLayout()
{
    QLayoutItem *item;
    while ((item = CardLayout::takeAt(0)))
        delete item;
}

void CardLayout::addItem(QLayoutItem *item)
{
    items_.append(item);
}

QLayoutItem *CardLayout::itemAt(int index) const
{
    return items_.value(index);
}

QLayoutItem *CardLayout::takeAt(int index)
{
    return index >= 0 && index < items_.size() ? items_.takeAt(index) : 0;
}

int CardLayout::count() const
{
    return items_.size();
}

int CardLayout::spacing() const
{
    if(items_.empty()){
        return 0;
    }
    return spacing_ * items_.at(0)->geometry().width() / 100;
}

void CardLayout::setSpacing(int s)
{
    spacing_ = s;
}

void CardLayout::setSpacing(double d)
{
    spacing_ = d;
}
