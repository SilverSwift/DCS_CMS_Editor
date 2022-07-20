#include "fa18cparcer.h"
#include "numericutills.h"

#include <QDebug>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

namespace {
    enum Parameters{
        Comment =1,
        Name,
        Chaff,
        Flare,
        Intv,
        Cycle
    };
};

FA18CParcer::FA18CParcer(QObject *parent)
    : BaseLuaParser{parent}
{

}

/*
 * Based on a DCS script syntax:
 *
 * -- MAN 1
 * programs[ProgramNames.MAN_1] = {}
 * programs[ProgramNames.MAN_1]["chaff"] = 1
 * programs[ProgramNames.MAN_1]["flare"] = 1
 * programs[ProgramNames.MAN_1]["intv"]  = 1.0
 * programs[ProgramNames.MAN_1]["cycle"] = 10
 *
 * NOTE: no need to check numeric
 * conversion results if regex matched
 *
 */
bool FA18CParcer::parseData()
{
    mData.clear();
    static QRegularExpression re("--\\s+(.*)\n"
                                 "programs\\[.*(\\d)\\]\\s+=\\s+\\{\\}\n"
                                 "programs\\[.*\\]\\[\"chaff\"\\]\\s+=\\s+(\\d+)\n"
                                 "programs\\[.*\\]\\[\"flare\"\\]\\s+=\\s+(\\d+)\n"
                                 "programs\\[.*\\]\\[\"intv\"\\]\\s+=\\s+([\\d\\.]+)\n"
                                 "programs\\[.*\\]\\[\"cycle\"\\]\\s+=\\s+(\\d+)\n");

    QRegularExpressionMatchIterator i = re.globalMatch(mContent);

    bool ok = true;
    while(i.hasNext() && ok){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.name = match.captured(Name);
        program.comment = match.captured(Comment);

        ok = ok && parseInt16(program.chaff.brstQty, Chaff, match, ok);
        ok = ok && parseInt16(program.flare.brstQty, Flare, match, ok);

        program.flare.seqItrvPrecision = 0.01;
        ok = ok && parseInterval(program.flare.seqItrv, Intv,
                                 program.flare.seqItrvPrecision,
                                 match, ok);

        ok = ok && parseInt16(program.flare.seqQty, Cycle, match, ok);

        program.flare.brstQtyLbl = QStringLiteral("FLARE");
        program.flare.seqQtyLbl = QStringLiteral("CYCLE");
        program.flare.seqItrvLbl = QStringLiteral("INTRV");
        program.chaff.brstQtyLbl = QStringLiteral("CHAFF");

        program.chaff.isBrstQtySet = true;
        program.flare.isBrstQtySet = true;
        program.flare.isSeqQtySet = true;
        program.flare.isSeqItrvSet = true;

        if( ok )
            mData.append(program);
    }

    return ok;
}

void FA18CParcer::saveContent(QTextStream& stream)
{
    stream<<programmsStart()<<"\n";
    for (const auto& item : mData){
        auto interval =
                NumericUtills::intervalToString(item.flare.seqItrv,
                                                item.flare.seqItrvPrecision);
        QString programStr =
        QString("-- %6\n"
                "programs[ProgramNames.MAN_%1] = {}\n"
                "programs[ProgramNames.MAN_%1][\"chaff\"] = %2\n"
                "programs[ProgramNames.MAN_%1][\"flare\"] = %3\n"
                "programs[ProgramNames.MAN_%1][\"intv\"]  = %4\n"
                "programs[ProgramNames.MAN_%1][\"cycle\"] = %5\n\n")
                    .arg(item.name)
                    .arg(item.chaff.brstQty)
                    .arg(item.flare.brstQty)
                    .arg(interval)
                    .arg(item.flare.seqQty).arg(item.comment);
        stream<<programStr;
    }
}

QString FA18CParcer::programmsStart() const
{
    return QStringLiteral("-- Default manual presets");

}

QString FA18CParcer::programmsEnd() const
{
    return QStringLiteral("-- MAN 6 - Wall Dispense button, Panic");
}
