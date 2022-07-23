#ifndef A10CPARSER_H
#define A10CPARSER_H

#include "baseluaparser.h"

namespace parsing{

/*
 * A10CParser class works with AN_ALE40V_params.lua
 * A-10C & A-10CII CMSP has the following values in DCS
 * cycles 1-99 step 1
 * chaff/flare 1-999 step 1
 * intervall 0.25-5.00 step 0.25
 * program 'C' seems like typo, yet works
 */

class A10CParser : public BaseLuaParser
{
    Q_OBJECT
public:
    explicit A10CParser(QObject* parent = nullptr);

private:
    virtual bool parseData() override;
    virtual void saveContent(QTextStream& stream) override;
    virtual QString programmsStart() const override;
    virtual QString programmsEnd() const override;
};

}

#endif // A10CPARSER_H
