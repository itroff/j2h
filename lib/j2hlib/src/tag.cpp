#include "tag.h"


Tag::Tag(QString nm) : name(nm)
{
   // теги, которые не нужно закрывать! TODO make const static
   voidTags = QStringList{"area", "base", "br", "col", "command", "embed", "hr",
                                  "img", "input", "keygen", "link", "meta", "param", "source",
                                   "track", "wbr"};
}

Tag::~Tag()
{
   removeChilds();

}

void Tag::setContent(QString val)
{
    this->value = val;
}

void Tag::addParam(QString key, QString val)
{
    param.insert(key, val);
}

/**
 * @brief Tag::toString обычное строковое представление тэга с name, parameters, value
 * @param level
 * @return
 */
QString Tag::toString(int level)
{
    QString nodetext = formatting(level);
    nodetext += "<" + name;
    for(auto &p : param.keys()){
        nodetext += " " + p + "=\"" + param[p] + "\"";
    }
    nodetext+= ">";
    if(voidTags.contains(name)){
        return nodetext;
    }
    nodetext += getChildString(this, level + 1);

    nodetext += "</" + name + ">";
    return nodetext;

}

/**
 * @brief Tag::getChildString получение у вложенных тегов его строчного предсставления
 * @param tg
 * @param level
 * @return
 */
QString Tag::getChildString(Tag *tg, int level)
{
    QString nodetext;
    if(childNodes.size() > 0){
        for(Tag* t: tg->childNodes){
            nodetext += t->toString(level);
        }

        nodetext +="\n";
        for(int i =0; i < level - 1; i++){
            nodetext+="    ";
        }
    }
    else{
          nodetext+= value;

    }
    return nodetext;
}

/**
 * @brief Tag::formatting в зависимости от уровня вложенности добавляем
 * количество пробелов и если нужен, то перевод строки
 * @param level
 * @return
 */
QString Tag::formatting(int level){
    QString nodetext;
    if(level >0){
        nodetext +="\n";
    }
    for(int i =0; i < level; i++){
        nodetext+="    ";
    }
    return nodetext;
}

void Tag::addChild(Tag *tg)
{
    childNodes.append(tg);
}

/**
 * @brief Tag::removeChilds удаляем зависимые тэги попутно чистя память
 */
void Tag::removeChilds()
{
    for(Tag * tg : childNodes){
        delete tg;
    }
    childNodes.clear();
}


