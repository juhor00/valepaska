#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QLabel>

const int IMG_W = 1051;
const int IMG_H = 681;
const int MIN_W = 50;
const int DEFAULT_W = 130;

class CardWidget : public QLabel
{
public:

    CardWidget(const QPixmap &pixmap, QWidget *parent = nullptr);
    CardWidget(const QPixmap &pixmap);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int w) const override;
    bool hasHeightForWidth() const override;



signals:


private:
};

#endif // CARDWIDGET_H
