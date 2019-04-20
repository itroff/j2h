#include "page.h"
#include <QStringList>

Page::Page()
{
    m_docXml.setNodeValue("html");
    QDomElement html = m_docXml.createElement("html");
    m_docXml.appendChild(html);
    QDomElement head = m_docXml.createElement("head");
    html.appendChild(head);
    QDomElement meta = m_docXml.createElement("meta");
    meta.setAttribute("charset", "UTF-8");
    head.appendChild(meta);

    QDomElement title = m_docXml.createElement("title");


    head.appendChild(title);
  //   m_title = &title;
    QDomElement bod = m_docXml.createElement("body");
    // mp_body = &bod;
    html.appendChild(bod);

}

void Page::replaceTitle(QString newTitle){
    QDomNode list = m_docXml.firstChild();//  .elementsByTagName("head");
     QDomNodeList list2 =   list.toElement().elementsByTagName("head");
//     for(auto &node : list2){

//     }

}

void Page::appendBody(QDomElement appex){

}

QString Page::getText()
{
    return m_docXml.toString();
}

QDomElement Page::parseElem(QDomDocument &document, QJsonObject elem){
    if(!elem.contains("tag")){
        throw conv_error("not tag");
    }
    QDomElement domElem = document.createElement(elem["tag"].toString());
 //   domElem.setTagName(elem["tag"].toString());

    if(elem.contains("content")){
        if(elem["content"].isArray()){
            for(auto v : elem["content"].toArray()){
                QJsonObject element = v.toObject();
                domElem.appendChild(parseElem(document, element));
            }
        }
        else{
            QDomText text = document.createTextNode(elem["content"].toString());
            domElem.appendChild(text);
        }
    }
    if(elem.contains("param")){
        QJsonObject param =  elem["param"].toObject();
        for(const QString& key:  param.keys()) {
            QJsonValue value = param.value(key);
            domElem.setAttribute(key, value.toString());
        }
    }

    return domElem;
}


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

    if(QString::compare(mode, "write", Qt::CaseInsensitive)){

    }
    else if(QString::compare(mode, "add", Qt::CaseInsensitive)){

    }
    else{
        throw conv_error("wrong mode");
    }
    QJsonObject data = jsonObject["data"].toObject();
   // QString head = data["title"].toString();

    QJsonArray body = data["body"].toArray();
    if(data.contains("title")){
        QDomText text = m_docXml.createTextNode( data["title"].toString());
     //   mp_title->appendChild(text);

    }
    for(auto v : body){
        QJsonObject element = v.toObject();
  //      mp_body->appendChild( parseElem(m_docXml, element));
    }

    return m_docXml.toString();
}
