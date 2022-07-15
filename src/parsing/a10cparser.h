#ifndef A10CPARSER_H
#define A10CPARSER_H

#include "AbstractParser.h"

namespace parsing{

/*
 * A10CParser class works with AN_ALE40V_params.lua
 * A-10C & A-10CII CMSP has the following values in DCS
 * cycles 1-99 step 1
 * chaff/flare 1-999 step 1
 * intervall 0.25-5.00 step 0.25
 * program 'C' seems like typo, yet works
 */

    class A10CParser : public AbstractParser
    {
        Q_OBJECT
    public:
        explicit A10CParser(QObject* parent = nullptr);
        virtual ~A10CParser() override;

        virtual QVector<CMSProgram> data() const override;
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

#endif // A10CPARSER_H
