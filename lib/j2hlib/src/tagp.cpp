#include "tagp.h"

TagP::TagP(QString nm) : Tag(nm)
{

}
// для тега <p> param необходимо раскладывать в style
QString TagP::toString(int level)
{
    QString nodetext = formatting(level);
     nodetext += "<" + name;
    if(param.size() > 0){
        nodetext +=" style=\"";

        for(auto &p : param.keys()){
            nodetext +=  p + ":" + param[p] + "; ";
        }
        nodetext +=+ "\"";
    }
    nodetext +=+ ">";
    nodetext += getChildString(this, level + 1);
    nodetext+=  "</" + name + ">";
    return nodetext;

}
