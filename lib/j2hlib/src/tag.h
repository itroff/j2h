#ifndef TAG_H
#define TAG_H


#include <QString>
#include <QVector>
#include <QHash>

class Tag
{
private:
    QString name;
    QVector<Tag *> childTags;
    QString content;
    QHash<QString, QString> params;

public:
    Tag();
    Tag(QString name, QString value);
    void fromJson();
    void toHtml();
};

#endif // TAG_H
