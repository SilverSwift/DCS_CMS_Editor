#ifndef JF17PARSER_H
#define JF17PARSER_H

#include "abstractparser.h"

namespace parsing{

class JF17Parser : public AbstractParser
{
    Q_OBJECT
public:
    explicit JF17Parser(QObject *parent = nullptr);

    virtual QVector <CMSProgram> data() const override;
    virtual void setData(const QVector<CMSProgram> dataArg) override;
    virtual bool readFromFile(QString path) override;
    virtual void writeToFile(QString path = {}) override;

#ifdef QT_DEBUG
    virtual void serialize(QString outputFile) override;
#endif
    virtual void initFromDefaults(QString name) override;

private:
    bool readData();
    bool parseData();

    QVector<CMSProgram> mData;

    QString mPath;

    QString mHeader;
    QString mContent;
    QString mFooter;

    enum Parameters{
        Comment = 2,
        Name,
        ChaffBrstItrv,
        ChaffSeqItrv,
        ChaffBrstQty,
        ChaffSeqQty,
        FlareBrstItrv,
        FlareSeqItrv,
        FlareBrstQty,
        FlareSeqQty
    };

    qint16 parseInt16(qint16& value, Parameters param,
                      QRegularExpressionMatch match,
                      bool& ok);

    qint16 parseInterval(qint16& value, Parameters param,
                         QMap<qint16, qint16> params,
                         QRegularExpressionMatch match,
                         bool& ok);
};

}
#endif // JF17PARSER_H
