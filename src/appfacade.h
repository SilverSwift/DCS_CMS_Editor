#ifndef APPFACADE_H
#define APPFACADE_H

#include <QObject>

#include "cmsmodel.h"
namespace model{
    class AbstractValidator;
}
namespace parsing {
    class AbstractParser;
}

class AppFacade : public QObject{
    Q_OBJECT
public:
    explicit AppFacade(QObject *parent = nullptr) ;

    Q_PROPERTY(model::CMSModel* model READ model NOTIFY modelChanged);

    inline model::CMSModel* model() const {return pModel;}

signals:
    void modelChanged(model::CMSModel* model);

private:
    parsing::AbstractParser* pParser = nullptr;
    model::AbstractValidator* pValidator = nullptr;
    model::CMSModel* pModel = nullptr;

};

#endif // APPFACADE_H
