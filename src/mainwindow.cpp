#include "mainwindow.hpp"

#include <QWidgetAction>
#include <QMenuBar>
#include <QMenu> 
#include <QAction>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    parser.makeRequest();
    setupUI();
    connectionSignals();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    setWindowTitle("app");
    resize(400, 300);
    setMaximumSize({400, 300});

    QWidget* mainWindow = new QWidget(this);
    setCentralWidget(mainWindow);

    auto Rates = parser.getCurrencyRates();

    QMenuBar* menuBar = this->menuBar();

    QMenu* menuValuteIn = menuBar->addMenu("Valute In");
    QMenu* menuValuteOut = menuBar->addMenu("Valute Out");
    QMenu* menuTabel = menuBar->addMenu("Tabel");
    QMenu* menuDates = menuBar->addMenu("Dates");

    valuteInComboBox = new QComboBox(this);
    valuteOutComboBox = new QComboBox(this);
    valuteInComboBox->addItem("RUB");
    valuteOutComboBox->addItem("RUB");
    QString item;
    for (auto i : Rates) {
        item = i.CharCode;
        valuteInComboBox->addItem(item);
        valuteOutComboBox->addItem(item);
    }
    editDate1 = new QLineEdit(this);
    editDate1->setPlaceholderText("dd/mm/yyyy");
    editDate1->setMaxLength(10);
    editDate2 = new QLineEdit(this);
    editDate2->setPlaceholderText("dd/mm/yyyy");
    editDate2->setMaxLength(10);

    QWidgetAction* comboActionIn = new QWidgetAction(this);
    comboActionIn->setDefaultWidget(valuteInComboBox);
    QWidgetAction* comboActionOut = new QWidgetAction(this);
    comboActionOut->setDefaultWidget(valuteOutComboBox);
    QWidgetAction* editActionDate1 = new QWidgetAction(this);
    editActionDate1->setDefaultWidget(editDate1);
    QWidgetAction* editActionDate2 = new QWidgetAction(this);
    editActionDate2->setDefaultWidget(editDate2);
    actionTabelCurrencyRates = new QAction("Currency rates");

    menuValuteIn->addAction(comboActionIn);
    menuValuteOut->addAction(comboActionOut);
    menuTabel->addAction(actionTabelCurrencyRates);
    menuDates->addAction(editActionDate1);
    menuDates->addAction(editActionDate2);


    mainLayout = new QGridLayout(mainWindow);
    const int Row = 10, Col = 10;
    for (int row = 0; row < Row; ++row) {
        mainLayout->setRowStretch(row, 1);
        mainLayout->setRowMinimumHeight(row, 5);
    }
    for (int col = 0; col < Col; ++col) {
        mainLayout->setColumnStretch(col, 1);
        mainLayout->setColumnMinimumWidth(col, 5);
    }
    for (int row = 0; row < Row; ++row)
        for (int col = 0; col < Col; ++col) {
            /*QString name = "%1,%2";
            name = name.arg(row).arg(col);
            mainLayout->addWidget(new QLabel(name), row, col);*/
            mainLayout->addWidget(new QWidget, row, col);
        }

    editValute = new QLineEdit(this);
    QLabel* label = new QLabel("Input valute", this);
    btnStart = new QPushButton("Ok", this);
    btnUpdate = new QPushButton("Update", this);
    outputResult = new QLineEdit(this);
    outputResult->setReadOnly(true);

    mainLayout->addWidget(label, 0, 0, 1, 2);
    mainLayout->addWidget(editValute, 0, 1, 1, 8);
    mainLayout->addWidget(outputResult, 1, 0, 1, 9);
    mainLayout->addWidget(btnStart, 9, 0, 1, 1);
    mainLayout->addWidget(btnUpdate, 9, 9, 1, 1);
}

void MainWindow::connectionSignals() {
    QObject::connect(btnStart, &QPushButton::clicked, this, &MainWindow::onClickedButtonStart);
    QObject::connect(btnUpdate, &QPushButton::clicked, this, &MainWindow::onClickedButtonUpdate);
    QObject::connect(valuteInComboBox, &QComboBox::activated, this, &MainWindow::onComboBoxInActivated);
    QObject::connect(valuteOutComboBox, &QComboBox::activated, this, &MainWindow::onComboBoxOutActivated);
    QObject::connect(actionTabelCurrencyRates, &QAction::triggered, this, &MainWindow::onCurrencyRatesActivated);
}