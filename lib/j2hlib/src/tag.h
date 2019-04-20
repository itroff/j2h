#ifndef TAG_H
#define TAG_H

#include <QVector>
#include <QHash>
#include <QStringList>


class Tag
{
public:
    Tag(QString nm);
    virtual ~Tag();
    void setContent(QString val);
    void addParam(QString key, QString val);
    virtual QString toString(int level = 0);
    static Tag * createTag(QString name);
    QString getChildString(Tag *tg, int level);
    void addChild(Tag *tg);
    void removeChilds();


    QString formatting(int level);
protected:
    QString name;
    QVector<Tag *>childNodes;
    QHash<QString, QString> param;
    QString value;
    QStringList voidTags;
};


#endif // TAG_H
