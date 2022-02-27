#include "hand.h"

Hand::Hand(QWidget *parent):
    QLayout(parent)
{
    this->Hand::setSpacing(SPACING_PERCENT);
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
        qDebug() << "ItemSize min" << itemSize;
        s = QSize(s.width() + itemSize.width() + spacing(), s.height());
        s = s.expandedTo(itemSize);
        ++i;
    }
    qDebug() << "MinSize hand" << QSize(s.width()-spacing(), s.height()+HOVER_Y);
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
        QLayoutItem* o = items_.at(i);
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

void Hand::addItem(QLayoutItem *item)
{
    items_.append(item);
}

QLayoutItem *Hand::itemAt(int idx) const
{
    // QVector::value() performs index checking, and returns nullptr if we are
    // outside the valid range
    return items_.value(idx);
}

QLayoutItem *Hand::takeAt(int idx)
{
    // QVector::take does not do index checking
    return idx >= 0 && idx < items_.size() ? items_.takeAt(idx) : 0;
}

int Hand::count() const
{
    // QVector::size() returns the number of QLayoutItems in m_items
    return items_.size();
}

int Hand::spacing() const
{
    if(items_.empty()){
        return 0;
    }
    return spacing_ * items_.at(0)->geometry().width() / 100;
}

void Hand::setSpacing(int s)
{
    spacing_ = s;
}
