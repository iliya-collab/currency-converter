#ifndef _DIALOG_TABEL_CURRENCY_RATES_
#define _DIALOG_TABEL_CURRENCY_RATES_

#include "CurrencyParser.hpp"

#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QLabel>
#include <QDate>

class DTableCurrencyRates : public QDialog {
    Q_OBJECT
public:
    DTableCurrencyRates(QWidget* parent = nullptr);

    void size(int cols, int rows) {
        colTable = cols;
        rowTable = rows;
    }

    void setDate(const QString& _date) {
        date = _date;
    }
    void createTable();
    void fillTable(const QList<CurrencyRate>& ListCurrencyRates);

private:

    QString date = "";
    int colTable = 0;
    int rowTable = 0;

    QTableWidget* tableWidget;
    QVBoxLayout* layout;
};

#endif