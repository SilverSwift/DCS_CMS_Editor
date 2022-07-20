#ifndef M2000CPARSER_H
#define M2000CPARSER_H

#include "abstractparser.h"
namespace parsing{
    class M2000CParser : public AbstractParser
    {
    public:
        explicit M2000CParser(QObject *parent = nullptr);
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
#endif // M2000CPARSER_H
