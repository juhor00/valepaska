#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QLabel>
#include "../card.h"

class CardWidget : public QLabel, public Card
{
    Q_OBJECT
public:
    CardWidget(QWidget *parent, int rank, char suit);
    CardWidget(QWidget *parent, std::string str);

    void turn();

signals:


private:

    QPixmap loadFront();
    QPixmap loadBack();


    QPixmap front_;
    QPixmap back_;
    bool isShowing_;
};

#endif // CARDWIDGET_H
