#include "appobject.h"
#include "a10cparser.h"

#include <QSharedPointer>

AppObject::AppObject(QObject *parent)
    : QObject{parent}
    , pParser (new parsing::A10CParser(this))
    , pModel (new CMSModel(pParser, this))
{

    connect(pParser, &parsing::AbstractParser::dataUpdated,
            pModel, &CMSModel::onDataChanged);
    connect(pParser, &parsing::AbstractParser::errorOccured,
            this, [](parsing::Error error){qDebug()<<error.errorMsg;});
}
