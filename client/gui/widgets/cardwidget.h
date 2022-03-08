#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QLabel>
#include <QObject>
#include <QResizeEvent>

const int MIN_W = 120;
const int DEFAULT_W = 140;

class CardWidget : public QLabel
{
    Q_OBJECT
public:

    CardWidget(const QPixmap pixmap, QWidget *parent = nullptr);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;
    int heightForWidth(int w) const override;
    int widthForHeight(int h) const;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
    virtual QPixmap loadImage() const = 0;


signals:

    void hovered(QPointF position);
    void hoveredLeft();


private:

    const QPixmap pix_;

    // QWidget interface
protected:
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;


    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // CARDWIDGET_H
