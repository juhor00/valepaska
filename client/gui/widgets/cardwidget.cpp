#include "cardwidget.h"


CardWidget::CardWidget(const QPixmap pixmap, QWidget *parent) :
    QLabel(parent),
    pix_(pixmap)
{
    QLabel::setPixmap(pixmap);
    this->setMinimumWidth(MIN_W);
    this->setMouseTracking(true);
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

int CardWidget::widthForHeight(int h) const
{
    QSize s = pix_.size();
    return h * s.width() / s.height();
}


void CardWidget::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    this->setPixmap(pix_.scaled(event->size(), Qt::KeepAspectRatio));
}

void CardWidget::enterEvent(QEnterEvent *event)
{
    emit hovered(event->position());
    QLabel::enterEvent(event);
}

void CardWidget::leaveEvent(QEvent *event)
{
    emit hoveredLeft();
    QLabel::leaveEvent(event);
}

void CardWidget::mouseMoveEvent(QMouseEvent *event)
{
    emit hovered(event->position());
    QLabel::mouseMoveEvent(event);
}
