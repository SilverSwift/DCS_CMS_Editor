#ifndef M2000CPARSER_H
#define M2000CPARSER_H

#include "baseluaparser.h"
namespace parsing{
/*
 * M2000CParser class works with SPIRALE.lua
 * Allowed CMSP values are to be defined
 *
 */
class M2000CParser : public BaseLuaParser
{
public:
    explicit M2000CParser(QObject *parent = nullptr);
    virtual ~M2000CParser() override = default;

protected:
    virtual bool parseData() override;
    virtual void saveContent(QTextStream& stream) override;
    virtual QString programmsStart() const override;
    virtual QString programmsEnd() const override;

};

}
#endif // M2000CPARSER_H
