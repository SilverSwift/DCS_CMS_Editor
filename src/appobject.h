#ifndef APPOBJECT_H
#define APPOBJECT_H

#include <QObject>

#include "cmsmodel.h"

namespace parsing {
    class AbstractParser;
}


class AppObject : public QObject
{
    Q_OBJECT
public:
    explicit AppObject(QObject *parent = nullptr);

    Q_PROPERTY(CMSModel* model READ model NOTIFY modelChanged)

    inline CMSModel* model() const {return pModel;}

signals:
    void modelChanged(CMSModel* model);

private:
    parsing::AbstractParser* pParser = nullptr;
    CMSModel* pModel = nullptr;

};

#endif // APPOBJECT_H
