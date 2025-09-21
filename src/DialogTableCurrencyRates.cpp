#include "DialogTableCurrencyRates.hpp"

DTableCurrencyRates::DTableCurrencyRates( QWidget* parent) : QDialog(parent) {
    setModal(false);
    setWindowTitle("TabelCurrencyRates");
    setMinimumSize(300, 200);
    setMaximumSize(550, 600);
    move(100, 100);
}

void DTableCurrencyRates::createTable() {
    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(rowTable);
    tableWidget->setColumnCount(colTable);
    tableWidget->setShowGrid(true);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QStringList headers;
    headers << "ID" << "Name" << "CharCode" << "Nominal" << "Value(RUB)";
    tableWidget->horizontalHeader()->setVisible(true);
    tableWidget->setHorizontalHeaderLabels(headers);

    QLabel* label_date;
    if (date == "") {
        QDate today = QDate::currentDate();
        label_date = new QLabel("Information from: " + today.toString("dd/MM/yyyy"), this);
    }
    else 
        label_date = new QLabel("Information from: " + date, this);

    layout = new QVBoxLayout(this);
    layout->addWidget(label_date);
    layout->addWidget(tableWidget);
    setLayout(layout);
}

void DTableCurrencyRates::fillTable(const QList<CurrencyRate>& ListCurrencyRates) {
    for (int row = 0; row < rowTable; row++) {
        tableWidget->setItem(row, 0, new QTableWidgetItem(ListCurrencyRates[row].id));
        tableWidget->setItem(row, 1, new QTableWidgetItem(ListCurrencyRates[row].Name));
        tableWidget->setItem(row, 2, new QTableWidgetItem(ListCurrencyRates[row].CharCode));
        tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(ListCurrencyRates[row].Nominal)));
        tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(ListCurrencyRates[row].Value, 'f', 4)));
    }
    tableWidget->viewport()->update();
}