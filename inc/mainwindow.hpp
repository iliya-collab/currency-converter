#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QApplication>
#include <QMainWindow>

#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>

#include "CurrencyParser.hpp"
#include "DialogTableCurrencyRates.hpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QWidget* mainWindow;
    QGridLayout* mainLayout;

    QLineEdit* editValute;
    QLineEdit* editDate1;
    QLineEdit* editDate2;
    QPushButton* btnStart;
    QPushButton* btnUpdate;
    QLineEdit* outputResult;
    QComboBox *valuteInComboBox;
    QComboBox *valuteOutComboBox;
    QAction* actionTabelCurrencyRates;

    DTableCurrencyRates* DTable;

    QString dataValuteIn = "RUB";
    QString dataValuteOut = "RUB";
    CurrencyParser parser;

    void setupUI();
    void connectionSignals();

private slots:

    void onClickedButtonStart();
    void onClickedButtonUpdate();
    void onComboBoxInActivated(int index);
    void onComboBoxOutActivated(int index);
    void onCurrencyRatesActivated();

};

#endif