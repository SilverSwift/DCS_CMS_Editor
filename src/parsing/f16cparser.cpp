#include "f16cparser.h"
#include "numericutills.h"

#include <QDebug>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

namespace {
    enum Parameters{
        Comment =1,
        Name,
        ChaffBrstQty,
        ChaffBrstItrv,
        ChaffSeqQty,
        ChaffSeqItrv,
        FlareBrstQty,
        FlareBrstItrv,
        FlareSeqQty,
        FlareSeqItrv
    };
};

F16CParser::F16CParser(QObject *parent)
    : BaseLuaParser{parent}
{

}

bool F16CParser::parseData()
{
    mData.clear();
    static QRegularExpression re("--\\s+(.*)\n"
                                 "programs\\[.*(\\d)\\] = \\{\n"
                                 "\\s+chaff = \\{\n"
                                 "\\s+burstQty\\s*= (\\d+),\n"
                                 "\\s+burstIntv\\s*= (\\d+\\.\\d+),\n"
                                 "\\s+salvoQty\\s*= (\\d+),\n"
                                 "\\s+salvoIntv\\s*= (\\d+\\.\\d+),\n"
                                 "\\s+\\},"
                                 "\\s+flare = \\{\n"
                                 "\\s+burstQty\\s*= (\\d+),\n"
                                 "\\s+burstIntv\\s*= (\\d+\\.\\d+),\n"
                                 "\\s+salvoQty\\s*= (\\d+),\n"
                                 "\\s+salvoIntv\\s*= (\\d+\\.\\d+),\n"
                                 "\\s+\\},\n"
                                 "}"
                                 "");

    QRegularExpressionMatchIterator i = re.globalMatch(mContent);

    bool ok = true;
    while(i.hasNext() && ok){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.name = match.captured(Name).at(0).toLatin1();
        program.comment = match.captured(Comment);


        ok = ok && parseInt16(program.chaff.brstQty, ChaffBrstQty, match, ok);
        program.chaff.brstItrvPrecision = 0.001;
        ok = ok && parseInterval(program.chaff.brstItrv, ChaffBrstItrv,
                                 program.chaff.brstItrvPrecision,
                                 match, ok);
        ok = ok && parseInt16(program.chaff.seqQty, ChaffSeqQty, match, ok);
        program.chaff.seqItrvPrecision = 0.01;
        ok = ok && parseInterval(program.chaff.seqItrv, ChaffSeqItrv,
                                 program.chaff.seqItrvPrecision,
                                 match, ok);

        ok = ok && parseInt16(program.flare.brstQty, FlareBrstQty, match, ok);
        program.flare.brstItrvPrecision = 0.001;
        ok = ok && parseInterval(program.flare.brstItrv, FlareBrstItrv,
                                 program.flare.brstItrvPrecision,
                                 match, ok);
        ok = ok && parseInt16(program.flare.seqQty, FlareSeqQty, match, ok);
        program.flare.seqItrvPrecision = 0.01;
        ok = ok && parseInterval(program.flare.seqItrv, FlareSeqItrv,
                                 program.flare.seqItrvPrecision,
                                 match, ok);

        program.chaff.brstQtyLbl = QStringLiteral("BRST QTY");
        program.chaff.brstItrvLbl = QStringLiteral("BRST INTRV");
        program.chaff.seqQtyLbl = QStringLiteral("SALVO QTY");
        program.chaff.seqItrvLbl = QStringLiteral("SALVO INTRV");

        program.flare.brstQtyLbl = QStringLiteral("BRST QTY");
        program.flare.brstItrvLbl = QStringLiteral("BRST INTRV");
        program.flare.seqQtyLbl = QStringLiteral("SALVO QTY");
        program.flare.seqItrvLbl = QStringLiteral("SALVO INTRV");

        program.chaff.isBrstQtySet = true;
        program.chaff.isBrstItrvSet = true;
        program.chaff.isSeqQtySet = true;
        program.chaff.isSeqItrvSet = true;

        program.flare.isBrstQtySet = true;
        program.flare.isBrstItrvSet = true;
        program.flare.isSeqQtySet = true;
        program.flare.isSeqItrvSet = true;

        if (ok)
            mData.append(program);
    }

    return ok;
}

void F16CParser::saveContent(QTextStream& stream)
{
    stream<<programmsStart()<<"\n";
    for (const auto& item : mData){
        auto chaffBrstItrv =
                NumericUtills::intervalToString(item.chaff.brstItrv,
                                                item.chaff.brstItrvPrecision);
        auto chaffSeqItrv =
                NumericUtills::intervalToString(item.chaff.seqItrv,
                                                item.chaff.seqItrvPrecision);
        auto flareBrstItrv =
                NumericUtills::intervalToString(item.flare.brstItrv,
                                                item.flare.brstItrvPrecision);
        auto flareSeqItrv =
                NumericUtills::intervalToString(item.flare.seqItrv,
                                                item.flare.seqItrvPrecision);
        QString programStr =
        QString("-- %1\n"
                "programs[ProgramNames.MAN_%2] = {\n"
                "\tchaff = {\n"
                "\t\tburstQty\t= %3,\n"
                "\t\tburstIntv\t= %4,\n"
                "\t\tsalvoQty\t= %5,\n"
                "\t\tsalvoIntv\t= %6,\n"
                "\t},\n"
                "\tflare = {\n"
                "\t\tburstQty\t= %7,\n"
                "\t\tburstIntv\t= %8,\n"
                "\t\tsalvoQty\t= %9,\n"
                "\t\tsalvoIntv\t= %10,\n"
                "\t},\n"
                "}\n"
                "\n"
                )
                    .arg(item.comment, item.name)
                    .arg(item.chaff.brstQty)
                    .arg(chaffBrstItrv)
                    .arg(item.chaff.seqQty)
                    .arg(chaffSeqItrv)
                    .arg(item.flare.brstQty)
                    .arg(flareBrstItrv)
                    .arg(item.flare.seqQty)
                    .arg(flareSeqItrv);
        stream<<programStr;
    }
}

QString F16CParser::programmsStart() const
{
    return QStringLiteral("-- Default manual presets");
}

QString F16CParser::programmsEnd() const
{
    return QStringLiteral("-- Auto presets");
}
