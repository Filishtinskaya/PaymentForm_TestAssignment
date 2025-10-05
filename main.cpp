#include "CheckPaymentForm.h"

#include <QApplication>
#include <QVector>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProductsList pl{QVector<Product>{Product{.name = "product1", .qty=10, .price=5.5},
                    Product{.name = "product2", .qty=1, .price=12.0},
                    Product{.name = "product3", .qty=1, .price=40.333333333}}};
    CheckPayment w(nullptr, &pl);
    w.show();
    return a.exec();
}
