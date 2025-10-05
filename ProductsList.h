#ifndef PRODUCTSLIST_H
#define PRODUCTSLIST_H

#include <QString>
#include <QVector>

struct Product
{
    QString name;
    int qty;
    float price;
};

struct ProductsList
{
    float totalPrice();
    QVector<Product> data;
};

#endif // PRODUCTSLIST_H
