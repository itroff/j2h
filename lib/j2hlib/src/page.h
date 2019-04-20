#ifndef PAGE_H
#define PAGE_H

#include <QString>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include "tag.h"

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
    ~Page();
    QString transform(QByteArray &json);

    Tag *parseElem(QJsonObject elem);
    void replaceTitle(QString newTitle);
    QString getText();
    static Tag *createTag(QString name);
private:
    Tag *mp_page;
    Tag *mp_title;
    Tag *mp_body;
};

#endif // PAGE_H
