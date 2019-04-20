#include "tag.h"
#include "page.h"
#include <QDebug>

void testTag(){
    Tag *tg = Page::createTag("p");
    tg->addParam("color", "red");
    tg->addParam("font", "Tahoma");
    tg->setContent("this is test");
    qDebug() << tg->toString();


    Tag *tg2 = new Tag("img");
    tg2->addParam("src", "red");
    tg->addChild(tg2);

    tg2->setContent("tgreas");
    qDebug() << tg2->toString();

    Tag *tg3 = Page::createTag("img");
    tg3->setContent("tgreas");
    qDebug() << tg3->toString();


    Tag *tg4 = Page::createTag("p");
    tg4->addChild(tg);
    tg4->addChild(tg3);

    qDebug() << tg4->toString();
    delete tg4;
}


int main(){


    testTag();
    return 0;
}
