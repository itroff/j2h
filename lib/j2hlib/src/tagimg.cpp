#include "tagimg.h"

TagImg::TagImg(QString nm) : Tag(nm)
{

}
// для тега <img> необходимо добавлять content в параметр src
QString TagImg::toString(int level)
{
    QString nodetext = formatting(level);
    nodetext  += "<" + name;
    nodetext +=" src=\"" + value + "\">";
    return nodetext;

}
