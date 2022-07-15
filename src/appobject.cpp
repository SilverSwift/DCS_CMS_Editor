#include "appobject.h"
#include "mockparser.h"

#include <QSharedPointer>

AppObject::AppObject(QObject *parent)
    : QObject{parent}
    , pParser (new parsing::MockParser(this))
    , pModel (new CMSModel(pParser, this))
{

    connect(pParser, &parsing::AbstractParser::dataUpdated,
            pModel, &CMSModel::onDataChanged);
    pParser->readFromFile("some/path");
}
