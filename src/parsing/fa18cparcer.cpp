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

        //hack for 2.9.16.10973.1
        if (program.name == "0")
            continue;
        //end

        if( ok )
            mData.append(program);
    }

    return ok;
}



void FA18CParcer::saveContent(QTextStream& stream)
{
    stream<<programmsStart()<<"\n";
    for (const auto& item : mData){
        serializeProgram(item, stream);

        //hack for 2.9.16.10973.1
        if (item.name == "5"){
            CMSProgram hack {item};
            hack.name = "0";
            hack.comment = "hack for CMS FWD switch";
            serializeProgram(hack, stream);
        }
        //end

    }
}

QString FA18CParcer::programmsStart() const
{
    return QStringLiteral("-- Default manual presets");

}

QString FA18CParcer::programmsEnd() const
{
    //was ok before 2.9.16.10973.1 but then ED broken cms/dtc stuff for f/a-18c
    //once fixed by ed should be bring back again
    //return QStringLiteral("-- MAN 6 - Wall Dispense button, Panic");

    return QStringLiteral("-- Auto presets");
}

void FA18CParcer::serializeProgram(const CMSProgram& program, QTextStream& stream)
{
    auto interval =
        NumericUtills::intervalToString(program.flare.seqItrv,
                                        program.flare.seqItrvPrecision);
    QString programStr =
        QString("-- %6\n"
                "programs[ProgramNames.MAN_%1] = {}\n"
                "programs[ProgramNames.MAN_%1][\"chaff\"] = %2\n"
                "programs[ProgramNames.MAN_%1][\"flare\"] = %3\n"
                "programs[ProgramNames.MAN_%1][\"intv\"]  = %4\n"
                "programs[ProgramNames.MAN_%1][\"cycle\"] = %5\n\n")
            .arg(program.name)
            .arg(program.chaff.brstQty)
            .arg(program.flare.brstQty)
            .arg(interval)
            .arg(program.flare.seqQty).arg(program.comment);
    stream<<programStr;
}
