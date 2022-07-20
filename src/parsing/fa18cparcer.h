#ifndef FA18CPARCER_H
#define FA18CPARCER_H

#include "baseluaparser.h"

namespace parsing {

/*
 * FA18CParser class works with CMDS_ALE47.lua
 * F/A-18C CMSP has the following values in DCS
 * cycles 1-24 step 1
 * chaff/flare 0-100 step 1
 * intervall 0.25-5.00 step 0.25
 */

class FA18CParcer : public BaseLuaParser
{
    Q_OBJECT
public:
    explicit FA18CParcer(QObject *parent = nullptr);
    ~FA18CParcer() override = default;

protected:
    virtual bool parseData() override;
    virtual void saveContent(QTextStream& stream) override;
    virtual QString programmsStart() const override;
    virtual QString programmsEnd() const override;

};

}
#endif // FA18CPARCER_H
