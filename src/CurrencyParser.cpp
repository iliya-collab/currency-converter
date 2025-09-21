#include "CurrencyParser.hpp"

#include <QEventLoop>

void CurrencyParser::makeRequest(const QString& date_req) {
    QNetworkReply *reply;
    if (date_req == "")
        reply = manager->get(QNetworkRequest( QUrl(url_dailyXML) ));
    else
        reply = manager->get(QNetworkRequest( QUrl(url_dailyXML+QString("?date_req=")+date_req) ));

    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError)
        parseCurrencies(reply->readAll());
    else
        qWarning() << "Error:" << reply->errorString();

    reply->deleteLater();
}

void CurrencyParser::parseCurrencies(const QByteArray &data) {
    ListCurrencyRates.clear();
    QXmlStreamReader xml(data);
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement && xml.name() == "Valute")
            ListCurrencyRates.append(parseValute(xml));
    }
}

CurrencyRate CurrencyParser::parseValute(QXmlStreamReader& xml) {
    CurrencyRate rate;
    while (!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "Valute")) {
        if (xml.tokenType() == QXmlStreamReader::StartElement) {
            QString elem = xml.name().toString();
            if (elem == "Valute")
                rate.id = xml.attributes().value("ID").toString();
            else if (elem == "CharCode")
                rate.CharCode = xml.readElementText();
            else if (elem == "Nominal")
                rate.Nominal = xml.readElementText().toInt();
            else if (elem == "Name")
                rate.Name = xml.readElementText();
            else if (elem == "Value")
                rate.Value = xml.readElementText().replace(',', '.').toDouble();
        }
        xml.readNext();
    }
    return rate;
}

/*void CurrencyParser::onNetworkRequest(const QByteArray &data) {
    QXmlStreamReader xml(data);
    
    while (!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartElement && xml.name() == "Valute")
            ListCurrencyRates.append(parseValute(xml));
    }
}

void CurrencyParser::onNetworkError(const QString &error) {
    qDebug() << "Error:" << error;
}*/