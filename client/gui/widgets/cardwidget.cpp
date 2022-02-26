#include "cardwidget.h"


CardWidget::CardWidget(const QPixmap &pixmap, QWidget *parent) :
    QLabel(parent)
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
    return (w / IMG_W) * IMG_H;
}

bool CardWidget::hasHeightForWidth() const
{
    return true;
}
