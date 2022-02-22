#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QLabel>

class CardWidget : public QLabel
{
    Q_OBJECT
public:
    CardWidget(QWidget *parent, QPixmap image);

signals:


private:

    QPixmap image_;
};

#endif // CARDWIDGET_H
