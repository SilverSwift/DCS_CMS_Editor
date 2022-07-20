#ifndef AV8BPARSER_H
#define AV8BPARSER_H

#include "baseluaparser.h"

namespace parsing{
/*
 * AV8BParser class works with EW_Dispensers_init.lua
 * All AV-8B CMSP values is in range 1 - 15 step 1
 * except burst interval for chaff is 0.1 - 1.5 step 0.1
 *
 */
class AV8BParser : public BaseLuaParser
{
public:
    explicit AV8BParser(QObject *parent = nullptr);
    virtual ~AV8BParser() override = default;

protected:
    virtual bool parseData() override;
    virtual void saveContent(QTextStream& stream) override;
    virtual QString programmsStart() const override;
    virtual QString programmsEnd() const override;
};

}
#endif // AV8BPARSER_H
