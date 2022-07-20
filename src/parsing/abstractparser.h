#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QObject>
#include <QVariant>
#include <QVector>

#include "parsing_types.h"

namespace parsing{

    /*
     * Interface for all custom parsers
     * doing CRUD stuff with scripts
     */
    class AbstractParser : public QObject{
        Q_OBJECT
    public:
        explicit AbstractParser(QObject* parent = nullptr) : QObject(parent) {}
        virtual ~AbstractParser() override = default;
        virtual QVector <CMSProgram> data() const = 0;
        virtual void setData(const QVector<CMSProgram> dataArg) = 0;
        virtual void readFromFile(QString path) = 0;
        virtual void writeToFile(QString path = {}) = 0;
    signals:
        void dataUpdated();
        void errorOccured(Error error);

    };

}
#endif // ABSTRACTPARSER_H
