#ifndef CARDLAYOUT_H
#define CARDLAYOUT_H

#include <QLayout>
#include <QDebug>

class CardLayout : public QLayout
{
public:
    CardLayout(QWidget* parent = nullptr);
    virtual ~CardLayout();

    // QLayout interface
public:
    void addItem(QLayoutItem *item) override;
    QLayoutItem *itemAt(int index) const override;
    QLayoutItem *takeAt(int index) override;
    int count() const override;
    int spacing() const override;
    void setSpacing(int s) override;
    void setSpacing(double d);



private:

    QVector<QLayoutItem*> items_;
    double spacing_;
};

#endif // CARDLAYOUT_H
