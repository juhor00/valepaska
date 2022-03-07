#ifndef ASPECTRATIO_H
#define ASPECTRATIO_H

#include <QWidget>
#include <QResizeEvent>
#include "layouts/cardlayout.h"

class AspectRatio : public QWidget
{
    Q_OBJECT
public:
    explicit AspectRatio(CardLayout* layout, QWidget *parent = nullptr);



signals:

private:

    int getAspectRatio() const;

    CardLayout* layout;
    float width;
    float height;


    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // ASPECTRATIO_H
