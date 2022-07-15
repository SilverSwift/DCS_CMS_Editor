#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QObject>
#include <QVector>

namespace parsing{

    /*
     * Describes a CMS programm
     */
    struct CMSProgram {
        QString comment;
        char name;
        //intv*0.25s = interval in seconds
        quint8 intv;
        quint8 flare;
        quint8 chaff;
        quint8 cycle;
    };

    struct Error {
        QString errorMsg;
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
        void errorOccured(Error);

    };

}
#endif // ABSTRACTPARSER_H
