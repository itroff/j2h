#ifndef TAGA_H
#define TAGA_H

#include "tag.h"

class TagA : public Tag
{
public:
    TagA(QString nm);
    QString toString(int level = 0);
};

#endif // TAGA_H
