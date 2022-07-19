#ifndef ABSTRACTPARSER_H
#define ABSTRACTPARSER_H

#include <QObject>
#include <QVariant>
#include <QVector>

namespace parsing{

    /*
     * Describes an expandable counter measures resource
     */
    struct Expendable{
        QString burstQuantityLabel;
        QString burstIntervalLabel;
        QString sequenceQuantityLabel;
        QString sequenceIntervalLabel;

        qint16 burstQuantity;
        qint16 burstInterval;
        qint16 sequenceQuantity;
        qint16 sequenceInterval;

        bool isBurstQuantitySet = false;
        bool isBurstIntervalSet = false;
        bool isSequenceQuantitySet = false;
        bool isSequenceIntervalSet = false;
    };
    /*
     * Describes a CMS programm
     */
    struct CMSProgram {
        QString comment;
        char name;        
        Expendable flare;
        Expendable chaff;
        Expendable other1;
        Expendable other2;
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
        void errorOccured(Error error);

    };

}
#endif // ABSTRACTPARSER_H
