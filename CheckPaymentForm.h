#ifndef CHECKPAYMENTFORM_H
#define CHECKPAYMENTFORM_H

#include "ProductsList.h"
#include <QWidget>
#include <QAbstractTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class CheckPayment;
}
QT_END_NAMESPACE

class ProductsTableModel : public QAbstractTableModel
{
public:
    enum class Columns {Product, Price, Qty, Total, NN};

    void setProductsList(ProductsList *aList);
    int rowCount(const QModelIndex &) const final;
    int columnCount(const QModelIndex &) const final;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role) const;
    QVariant data(const QModelIndex &index, int role) const;

private:
    ProductsList* list = nullptr;
};

class CheckPayment : public QWidget
{
    Q_OBJECT

public:
    CheckPayment(QWidget *parent = nullptr, ProductsList* productsList = nullptr);
    ~CheckPayment();

private:
    void refreshMoneyUi();

    Ui::CheckPayment *ui;
    ProductsTableModel tableModel;
    float cash = 0;
    float totalPrice = 0;
public slots:
    void cashAdded(int amount);
};
#endif // CHECKPAYMENTFORM_H
