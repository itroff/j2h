#ifndef PAGE_H
#define PAGE_H

#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <iostream>

class conv_error{

private:
    QString error;
    public:
    conv_error(QString er): error(er){}
    QString msg();



};
inline QString conv_error::msg(){
    return error;
}

class Page
{


public:
    Page();
    QString transform(QByteArray &json);

    QDomElement parseElem(QDomDocument &document, QJsonObject elem);
    void replaceTitle(QString newTitle);
    void appendBody(QDomElement appex);
    QString getText();
private:
    QDomDocument m_docXml;//("html");
};

#endif // PAGE_H
