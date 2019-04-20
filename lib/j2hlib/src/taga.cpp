#include "taga.h"

TagA::TagA(QString nm) : Tag(nm)
{

}
// для тега <a> content уходит в href и значение
QString TagA::toString(int level)
{
    QString nodetext = formatting(level);
    nodetext += "<" + name;
    nodetext +=" href=\"" + value + "\">" + value + "</" + name + ">";
    return nodetext;

}
