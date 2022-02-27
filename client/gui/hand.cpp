#include "hand.h"

Hand::Hand(QWidget *parent):
    CardLayout(parent)
{
    CardLayout::setSpacing(SPACING_PERCENT);
}

Hand::~Hand()
{
     QLayoutItem *item;
     while ((item = Hand::takeAt(0)))
         delete item;
}

QSize Hand::sizeHint() const
{
   QSize s(0,0);
   for(int i=0; i<count(); i++){
       QSize itemSize = itemAt(i)->sizeHint();
       s = QSize(s.width() + itemSize.width() + spacing(), s.height());
       s = s.expandedTo(itemSize);
   }
   return QSize(s.width()-spacing(), s.height()+HOVER_Y);
}

QSize Hand::minimumSize() const
{
    QSize s(0,0);

    int i = 0;
    while(i < count()){
        QSize itemSize = itemAt(i)->minimumSize();
        s = QSize(s.width() + itemSize.width() + spacing(), s.height());
        s = s.expandedTo(itemSize);
        ++i;
    }
    return QSize(s.width()-spacing(), s.height()+HOVER_Y);
}

QSize Hand::maximumSize() const
{
    QSize s(0,0);

    int i = 0;
    while(i < count()){
        QSize itemSize = itemAt(i)->maximumSize();
        s = QSize(s.width() + itemSize.width() + spacing(), s.height());
        s = s.expandedTo(itemSize);
        ++i;
    }
    return QSize(s.width()-spacing(), s.height()+HOVER_Y);
}

void Hand::setGeometry(const QRect &r)
{
    QLayout::setGeometry(r);

    if(count() == 0){
        return;
    }
    int w = ( r.width() - spacing() * (count()-1) ) / count();
    int h = r.height() - HOVER_Y;

    int i = 0;

    while(i < count()){
        QLayoutItem* o = itemAt(i);
        QRect geom(
                    // x, y, w, h
                    r.x() + i * (w + spacing()),
                    r.y()+HOVER_Y,
                    w,
                    h);
        o->setGeometry(geom);
        ++i;
    }
}
