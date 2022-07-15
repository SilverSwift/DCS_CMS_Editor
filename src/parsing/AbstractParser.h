#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QObject>
#include <QVector>

namespace parsing{

    /*
     * Describes a CMS programm
     */
    struct CMSProgram {
        quint8 flare;
        quint8 chaff;
        quint8 intv;
        quint8 cycle;
    };

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

    };

}
#endif // ABSTRACTPARSER_H
