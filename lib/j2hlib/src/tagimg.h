#ifndef TAGIMG_H
#define TAGIMG_H
#include "tag.h"

class TagImg : public Tag
{
public:
    TagImg(QString nm);
    QString toString(int level = 0);
};

#endif // TAGIMG_H
