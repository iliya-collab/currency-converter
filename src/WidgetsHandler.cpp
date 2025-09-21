#include "mainwindow.hpp"

void MainWindow::onClickedButtonStart() {
    QString data = editValute->text();
    if (data != "") {
        double res = 0;
        data = data.replace(',', '.');
        data = data.replace('_', "");
        qDebug() << "Data valute:" << data;
        double val = data.toDouble();

        double CurrencyIn = 1, CurrencyOut = 1;
        int cnt = 0;
        QString prefOut = "RUB";  
        auto ListRates = parser.getCurrencyRates();
        
        for (auto i : ListRates) {
            if (i.CharCode == dataValuteIn) {
                CurrencyIn = i.Value/i.Nominal;
                cnt += 1;
            }
            if (i.CharCode == dataValuteOut) {
                prefOut = i.CharCode;
                CurrencyOut = i.Value/i.Nominal;
                cnt += 1;
            }
            if (cnt == 2)
                break;
        }

        res = val * CurrencyIn / CurrencyOut;
    
        outputResult->clear();
        outputResult->setText(QString::number(res, 'f', 2) + " " + prefOut);
    }
}

void MainWindow::onClickedButtonUpdate() {
    if (editDate1->text() != "") {
        parser.makeRequest(editDate1->text());
    }
}

void MainWindow::onComboBoxInActivated(int index)
{
    dataValuteIn = valuteInComboBox->itemText(index);
    qDebug() << "Valute In:" << dataValuteIn;
}

void MainWindow::onComboBoxOutActivated(int index)
{
    dataValuteOut = valuteOutComboBox->itemText(index);
    qDebug() << "Valute Out:" << dataValuteOut;
}

void MainWindow::onCurrencyRatesActivated() {
    DTable = new DTableCurrencyRates(this);
    DTable->size(5, parser.getCurrencyRates().size());
    DTable->setDate(editDate1->text());
    DTable->createTable();
    DTable->fillTable(parser.getCurrencyRates());
    DTable->setAttribute(Qt::WA_DeleteOnClose);
    DTable->show();
}