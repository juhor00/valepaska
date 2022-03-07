#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QLabel>
#include <QResizeEvent>

const int MIN_W = 120;
const int DEFAULT_W = 140;

class CardWidget : public QLabel
{
public:

    CardWidget(const QPixmap pixmap, QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int w) const override;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
    virtual QPixmap loadImage() const = 0;





signals:


private:

    const QPixmap pix_;
};

#endif // CARDWIDGET_H
