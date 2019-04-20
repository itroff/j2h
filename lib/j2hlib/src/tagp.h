#ifndef TAGP_H
#define TAGP_H
#include "tag.h"

class TagP: public Tag
{
public:
    TagP(QString nm);
     QString toString(int level = 0);
};

#endif // TAGP_H
