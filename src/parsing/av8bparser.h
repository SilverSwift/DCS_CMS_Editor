#ifndef AV8BPARSER_H
#define AV8BPARSER_H

#include "abstractparser.h"

namespace parsing{
    class AV8BParser : public AbstractParser
    {
    public:
        explicit AV8BParser(QObject *parent = nullptr);
        virtual ~AV8BParser() override = default;

        virtual QVector <CMSProgram> data() const override;
        virtual void setData(const QVector<CMSProgram> dataArg) override;
        virtual void readFromFile(QString path) override;
        virtual void writeToFile(QString path = {}) override;

    private:
        bool readData();
        bool parseData();

        QVector<CMSProgram> mData;

        QString mPath;
        QString mHeader;
        QString mContent;
        QString mFooter;
    };
}
#endif // AV8BPARSER_H
