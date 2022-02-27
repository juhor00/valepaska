#include "cardwidget.h"


CardWidget::CardWidget(const QPixmap pixmap, QWidget *parent) :
    QLabel(parent),
    pix_(pixmap)
{
    QLabel::setPixmap(pixmap);
}

QSize CardWidget::sizeHint() const
{
    return QSize(DEFAULT_W, CardWidget::heightForWidth(DEFAULT_W));
}

QSize CardWidget::minimumSizeHint() const
{
    return QSize(MIN_W, CardWidget::heightForWidth(MIN_W));
}

int CardWidget::heightForWidth(int w) const
{
    QSize s = pix_.size();
    return w * s.height() / s.width();
}


void CardWidget::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    this->setPixmap(pix_.scaled(event->size(), Qt::KeepAspectRatio));
}
