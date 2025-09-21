#ifndef _PARSE_CURRENCY_
#define _PARSE_CURRENCY_

#include <QXmlStreamReader>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <QList>

struct CurrencyRate {
    QString id;
    QString CharCode;
    QString Name;
    int Nominal;
    double Value;
};



class CurrencyParser : public QObject {
    Q_OBJECT
public:

    CurrencyParser() {
        manager = new QNetworkAccessManager(this);
    }

    ~CurrencyParser() {
        delete manager;
    }

    void makeRequest(const QString& date_req = "");

    QList<CurrencyRate> getCurrencyRates() {
        return ListCurrencyRates;
    }

private:

    const QString url_dailyXML = "https://www.cbr.ru/scripts/XML_daily.asp";

    QNetworkAccessManager *manager;
    QList<CurrencyRate> ListCurrencyRates;

    void parseCurrencies(const QByteArray &data);
    CurrencyRate parseValute(QXmlStreamReader& xml);

};

#endif