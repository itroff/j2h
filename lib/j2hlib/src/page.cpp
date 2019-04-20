#include "page.h"
#include <QStringList>
#include "tagimg.h"
#include "tagp.h"
#include "taga.h"

Page::Page()
{
    // тело любой html5 страницы
    mp_page = Page::createTag("html");
    Tag *head = Page::createTag("head");
    mp_page->addChild(head);
    Tag * meta = Page::createTag("meta");
    meta->addParam("charset", "UTF-8");
    head->addChild(meta);
    mp_title = Page::createTag("title");
    head->addChild(mp_title);

    mp_body = Page::createTag("body");
    mp_page->addChild(mp_body);

}

Page::~Page()
{
    delete mp_page;// Достаточно его, иначе будет двойное удаление
}

void Page::replaceTitle(QString newTitle){

    mp_title->setContent(newTitle);

}

QString Page::getText()
{
    return "<!DOCTYPE html>\n" + mp_page->toString();
}

Tag* Page::parseElem(QJsonObject elem){
    if(!elem.contains("tag")){
        throw conv_error("not tag");
    }
    Tag *tmptag = Page::createTag(elem["tag"].toString());

    if(elem.contains("content")){
        if(elem["content"].isArray()){
            for(auto v : elem["content"].toArray()){
                QJsonObject element = v.toObject();
                tmptag->addChild(parseElem(element));
            }
        }
        else{
            tmptag->setContent(elem["content"].toString());
        }
    }
    if(elem.contains("param")){
        QJsonObject param =  elem["param"].toObject();
        for(const QString& key:  param.keys()) {
            QJsonValue value = param.value(key);
            tmptag->addParam(key, value.toString());
        }
    }

    return tmptag;
}

/**
 * @brief Page::transform парсинг json и преобразование во внутреннее представление
 * @param json массив байтов
 * @return html текст
 */
QString Page::transform(QByteArray &json)
{
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    // проверка корректности Json
    if(doc.isNull()){
        throw conv_error("Error parsing JSON: " + error.errorString());
    }
    QJsonObject jsonObject = doc.object();
    QString mode = jsonObject["mode"].toString();
    // при сценарии write перезаписываем body и заменяем title
    if(QString::compare(mode, "write", Qt::CaseInsensitive) ==  0){
        mp_body->removeChilds();
    }
    // при сценарии add дополняем body и заменяем title
    else if(QString::compare(mode, "add", Qt::CaseInsensitive) == 0){

    }
    else{
        throw conv_error("wrong mode");
    }
    QJsonObject data = jsonObject["data"].toObject();

    QJsonArray body = data["body"].toArray();
    if(data.contains("title")){
        replaceTitle(data["title"].toString());
    }
    for(auto v : body){
        QJsonObject element = v.toObject();
        mp_body->addChild(parseElem(element));
    }

    return getText();
}
/**
 * @brief Page::createTag небольшая фабрика, по хорошему нужно запретить создание TAG кроме этой функции
 * @param name
 * @return
 */
Tag *Page::createTag(QString name)
{
    // при добавлении других нестандартных тегов расширяем тут
    if(QString::compare(name, "img", Qt::CaseInsensitive) == 0){
        return new TagImg(name);
    }
    else if(QString::compare(name, "p", Qt::CaseInsensitive) == 0){
        return new TagP(name);
    }
    else if(QString::compare(name, "a", Qt::CaseInsensitive) == 0){
        return new TagA(name);
    }
    else{
        return new Tag(name);
    }

}
