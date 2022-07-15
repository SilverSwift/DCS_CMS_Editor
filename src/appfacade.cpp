#include "appfacade.h"
#include "a10cparser.h"
#include "a10cvalidator.h"

AppFacade::AppFacade(QObject *parent)
    : QObject(parent)
    , pParser (new parsing::A10CParser(this))
    , pValidator(new model::A10CValidator())
    , pModel (new model::CMSModel(pParser, pValidator, this))
{

    connect(pParser, &parsing::AbstractParser::dataUpdated,
            pModel, &model::CMSModel::onDataChanged);
    connect(pParser, &parsing::AbstractParser::errorOccured,
            this, [](parsing::Error error){qDebug()<<error.errorMsg;});

}
