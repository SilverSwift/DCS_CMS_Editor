#include "m2000cparser.h"
#include "numericutills.h"

#include <QDebug>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

namespace {
    enum Parameters{
        Comment = 2,
        Name,
        Chaff,
        Flare,
        Intv,
        Cycle,
        C_intv
    };
};

M2000CParser::M2000CParser(QObject *parent)
    : BaseLuaParser{parent}
{

}

/*
 * Based on DCS script syntax:
 *--optional comment
 * programs[ 1] = { chaff = 6, flare = 0, intv = 50, cycle = 1, c_intv = 200}
 *
 */
bool M2000CParser::parseData()
{
    mData.clear();
    static QRegularExpression re(
        "(--(.*)\n)?"
        "programs\\[\\s?(\\d+)\\]\\s*=\\s*\\{"
        "\\s*chaff\\s*=\\s*(\\d+)\\s*,"
        "\\s*flare\\s*=\\s*(\\d+)\\s*,"
        "\\s*intv\\s*=\\s*(\\d+)\\s*,"
        "\\s*cycle\\s*=\\s*(\\d+)\\s*,"
        "\\s*c_intv\\s*=\\s*(\\d+)\\s*\\}");

    QRegularExpressionMatchIterator i = re.globalMatch(mContent);

    bool ok = true;
    while(i.hasNext() && ok){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.comment = match.captured(Comment);
        program.name = match.captured(Name);

        ok = ok && parseInt16(program.chaff.brstQty, Chaff, match, ok);
        ok = ok && parseInt16(program.flare.brstQty, Flare, match, ok);
        ok = ok && parseInt16(program.flare.seqQty, Cycle, match, ok);

        //got to juggle with interval precision because
        //inegral number of miliseconds saved in a file...
        program.flare.seqItrvPrecision = 0.01;
        ok = ok && parseInterval(program.flare.seqItrv, C_intv,
                                 1, match, ok);
        program.flare.brstItrvPrecision = 0.01;
        ok = ok && parseInterval(program.flare.brstItrv, Intv,
                                 1, match, ok);

        program.flare.brstQtyLbl = QStringLiteral("FLARE");
        program.chaff.brstQtyLbl = QStringLiteral("CHAFF");
        program.flare.seqQtyLbl = QStringLiteral("CYCLE");
        program.flare.seqItrvLbl = QStringLiteral("CYCL INTRV");
        program.flare.brstItrvLbl = QStringLiteral("BRST INTRV");

        program.chaff.isBrstQtySet = true;
        program.flare.isBrstQtySet = true;
        program.flare.isSeqQtySet = true;
        program.flare.isSeqItrvSet = true;
        program.flare.isBrstItrvSet = true;

        if (ok)
            mData.append(program);
    }



    return ok;
}

void M2000CParser::saveContent(QTextStream& stream)
{
    stream<<programmsStart()<<"\n";
    for (const auto& item : mData){
        if (!item.comment.isEmpty())
            stream<<"--"<<item.comment<<"\n";

        stream<<QString(
                "programs[%1] = {\t"
                    "chaff = %2,\t"
                    "flare = %3,\t"
                    "intv = %4,\t"
                    "cycle = %5,\t"
                    "c_intv = %6\t}\n")
                    .arg(item.name, 2)
                    .arg(item.chaff.brstQty)
                    .arg(item.flare.brstQty)
                    .arg(item.flare.brstItrv)
                    .arg(item.flare.seqQty)
                    .arg(item.flare.seqItrv);
    }
}

QString M2000CParser::programmsStart() const
{
    return QStringLiteral("programs = {}");
}

QString M2000CParser::programmsEnd() const
{
    return QStringLiteral("");
}
