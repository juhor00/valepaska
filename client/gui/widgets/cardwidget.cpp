#include "cardwidget.h"


CardWidget::CardWidget(QWidget *parent, QPixmap image):
    QLabel(parent),
    image_(image)
{
    this->setPixmap(image);
}
