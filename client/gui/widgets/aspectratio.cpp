#include "aspectratio.h"

AspectRatio::AspectRatio(CardLayout *layout, QWidget *parent)
    : QWidget{parent}, layout(layout), width(1), height(1)
{

}

int AspectRatio::getAspectRatio() const
{
    if(height != 0){
        return width / height;
    }
    return 0;
}

void AspectRatio::resizeEvent(QResizeEvent *event)
{
    float width = event->size().width();
    float height = event->size().height();
    float ratio = height != 0 ? width / height : 0;

    if(ratio > getAspectRatio()){   // Wider
        width = height * getAspectRatio();
    } else {    // Taller
        height = getAspectRatio() != 0 ? width / getAspectRatio() : 0;
    }
    event = new QResizeEvent(QSize(width, height), event->oldSize());
    QWidget::resizeEvent(event);
}
