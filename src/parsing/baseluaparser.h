#ifndef BASELUAPARSER_H
#define BASELUAPARSER_H

#include "abstractparser.h"
#include "numericutills.h"
#include <QRegularExpressionMatch>

namespace parsing {

/*
 * BaseLuaParser class implemets generic
 * read methods for DCS modules.
 *
 */

class BaseLuaParser : public AbstractParser
{
public:
    explicit BaseLuaParser(QObject *parent = nullptr);
    virtual ~BaseLuaParser() override = default;

    virtual QVector<CMSProgram> data() const override;
    void setData(const QVector<CMSProgram> dataArg) override;
    void readFromFile(QString path) override;
    void writeToFile(QString path = {}) override;

protected:
    template <typename Parameters>
    inline bool parseInt16(qint16& value, Parameters param,
                           QRegularExpressionMatch match,
                           bool& ok){
        value = NumericUtills::parseInt16( match.captured(param), &ok);
        if (!ok){
            QString details =
                    tr("Parsing faield due to unexpected value: %1")
                    .arg(match.captured(param));
            emit this->errorOccured(Error{details});
        }
        return ok;
    }

    template <typename Parameters>
    inline bool parseInterval(qint16& value, Parameters param,
                              float precision,
                              QRegularExpressionMatch match,
                              bool& ok)
    {
        value = NumericUtills::parseInterval(match.captured(param), precision, &ok);
        if (!ok){
            QString details =
                    tr("Parsing interval faield due to unexpected value: %1")
                    .arg(match.captured(param));
            emit this->errorOccured(Error{details});
        }
        return ok;
    }

    virtual bool parseData() = 0;
    virtual void saveContent(QTextStream& stream) = 0;
    virtual bool readData();
    virtual QString programmsStart() const = 0;
    virtual QString programmsEnd() const = 0;

    QVector<CMSProgram> mData;

    QString mPath;

    QString mHeader;
    QString mContent;
    QString mFooter;

};

}

#endif // BASELUAPARSER_H
