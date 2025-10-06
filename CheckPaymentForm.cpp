#include "CheckPaymentForm.h"
#include "./ui_CheckPaymentForm.h"

#include <QMessageBox>

namespace {
    static consteval size_t columnsN() {
        return static_cast<size_t>(ProductsTableModel::Columns::NN);
    }
    static constexpr std::string_view columnsNames[columnsN()] = {"Product", "Price", "Qty", "Total"};

    QString priceToString(float price) {
        return QString::number(price, 'f', 2);
    }
}

CheckPayment::CheckPayment(QWidget *parent, ProductsList* productsList)
    : QWidget(parent)
    , ui(new Ui::CheckPayment)
{
    ui->setupUi(this);

    tableModel.setProductsList(productsList);
    totalPrice = productsList ? productsList->totalPrice() : 0;

    ui->priceNumLbl->setText(priceToString(totalPrice));
    ui->productsListTbl->setModel(&tableModel);

    cash = 0;
    refreshMoneyUi();

    connect(ui->cancelBtn, &QPushButton::clicked, this, &QWidget::close);

    connect(ui->paymentBtn, &QPushButton::clicked, this, [&](){
        QMessageBox::information(this, "Info", QString("Payment successful, remaining money: %1").arg(priceToString(cash - totalPrice)));
        close();
    });

    connect(ui->emulatedAddMoneyBtn, &QPushButton::clicked, this, [&](){
        cashAdded(10);
    });
}

CheckPayment::~CheckPayment()
{
    delete ui;
}

void CheckPayment::refreshMoneyUi()
{
    ui->paymentBtn->setEnabled(totalPrice != 0 && cash >= totalPrice);
    ui->moneyNumLbl->setText(priceToString(cash));
}

void CheckPayment::cashAdded(int amount)
{
    cash += amount;
    refreshMoneyUi();
}

void ProductsTableModel::setProductsList(ProductsList *aList) {
    list = aList;
}
int ProductsTableModel::rowCount(const QModelIndex &) const {
    return list ? list->data.size() : 0;
}
int ProductsTableModel::columnCount(const QModelIndex &) const {
    return columnsN();
}
QVariant ProductsTableModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const {
    if (role != Qt::DisplayRole)
        return {};
    switch (orientation) {
    case Qt::Orientation::Horizontal: {
        return QString::fromUtf8(columnsNames[section].data());
    }
    case Qt::Orientation::Vertical: {
        return section + 1;
    }
    }
    return {};
}

QVariant ProductsTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return {};

    int col = index.column(), row = index.row();
    assert(!list || row < list->data.size());
    assert(col < columnsN());

    using enum ProductsTableModel::Columns;
    switch(static_cast<ProductsTableModel::Columns>(col)) {
    case Product:
        return list->data[row].name;
    case Price:
        return priceToString(list->data[row].price);
    case Qty:
        return list->data[row].qty;
    case Total:
        return priceToString(list->data[row].qty * list->data[row].price);
    case NN:
        return {};
    }
    return {};
}
