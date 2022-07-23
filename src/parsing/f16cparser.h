#ifndef F16CPARSER_H
#define F16CPARSER_H

#include "baseluaparser.h"

namespace parsing{
/*
 * F16CParser class works with CMDS_ALE47.lua
 * F-16C CMSP has the following values in DCS
 * burst quantity 0-99 step 1
 * burst interval 0.020-10.000 step 0.001
 * salvo quantity 0-99 step 1
 * salvo interval 0.50-150.00 step 0.01
 *
 * chaff and flares are configured separately
 * on release there must be programms for decoys
 *
 * voice assistant options aren't configurable
 * via CMDS_ALE47.lua
 */
class F16CParser : public BaseLuaParser
{
public:
    explicit F16CParser(QObject *parent = nullptr);

protected:
    virtual bool parseData() override;
    virtual void saveContent(QTextStream& stream) override;
    virtual QString programmsStart() const override;
    virtual QString programmsEnd() const override;
};

}
#endif // F16CPARSER_H
