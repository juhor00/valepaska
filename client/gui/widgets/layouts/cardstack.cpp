#include "cardstack.h"

CardStack::CardStack(QWidget* parent):
    CardLayout(parent)
{}

QSize CardStack::sizeHint() const
{
    QSize s(0,0);

    int i = 0;
    while(i < count()){
        QSize itemSize = itemAt(i)->sizeHint();

        if(i == 0){
            s = itemSize;
        } else {
            s = QSize(s.width() + (1 - SPACING_X/100) * itemSize.width(),
                      s.height() + (1 - SPACING_Y/100) * itemSize.height());
        }

        ++i;
    }
    return QSize(s.width(), s.height()+HOVER_Y);
}

QSize CardStack::minimumSize() const
{
    QSize s(0,0);
    int i = 0;
    while(i < count()){
        QSize itemSize = itemAt(i)->minimumSize();

        if(i == 0){
            s = itemSize;
        } else {
            s = QSize(s.width() + (1 - SPACING_X/100) * itemSize.width(),
                      s.height() + (1 - SPACING_Y/100) * itemSize.height());
        }

        ++i;
    }
    return QSize(s.width(), s.height()+HOVER_Y);
}

void CardStack::setGeometry(const QRect &r)
{
    //QLayout::setGeometry(r);

    if(count() == 0){
        return;
    }
    int w = ( r.width() - spacing() * (count() -1) ) / count();
    int h = r.height() - HOVER_Y;

    int i = 0;
    while(i < count()){
        QLayoutItem* o = itemAt(i);
        QRect geom(
                    // x y w h
                    r.x() + i * spacingX(),
                    r.y() + HOVER_Y + i * spacingY(),
                    w,
                    h);
        o->setGeometry(geom);
        ++i;
    }
}

int CardStack::spacingX() const
{
    if(count() == 0){
        return 0;
    }
    return (1 - SPACING_X/100) * itemAt(0)->geometry().width();
}

int CardStack::spacingY() const
{
    if(count() == 0){
        return 0;
    }
    return (1 - SPACING_Y/100) * itemAt(0)->geometry().width();
}
