#ifndef F16CPARSER_H
#define F16CPARSER_H

#include "abstractparser.h"
namespace parsing{
class F16CParser : public AbstractParser
{
public:
    explicit F16CParser(QObject *parent = nullptr);

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
#endif // F16CPARSER_H
