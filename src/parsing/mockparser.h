#ifndef MOCKPARSER_H
#define MOCKPARSER_H

#include "abstractparser.h"

namespace parsing {
    class MockParser : public AbstractParser
    {
        Q_OBJECT
    public:
        explicit MockParser(QObject *parent = nullptr);
        ~MockParser() override;

        virtual QVector <CMSProgram> data() const override;
        virtual void setData(const QVector<CMSProgram> dataArg) override;
        virtual void readFromFile(QString path) override;
        virtual void writeToFile(QString path = {}) override;

    private:
         QVector<CMSProgram> mProgramms;

    };
}
#endif // MOCKPARSER_H
