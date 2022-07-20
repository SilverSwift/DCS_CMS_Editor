#include "a10cparser.h"
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


A10CParser::A10CParser(QObject* parent)
    : BaseLuaParser(parent)
{

}

/*
 * Based on a DCS script syntax:
 *
 * -- Old generation radar SAM
 * programs['A'] = {}
 * programs['A']["chaff"] = 2
 * programs['A']["flare"] = 0
 * programs['A']["intv"]  = 1.0
 * programs['A']["cycle"] = 10
 *
 * NOTE: no need to check numeric
 * conversion results if regex matched
 *
 */
bool A10CParser::parseData()
{
    static QRegularExpression re("--\\s+(.*)\n"
                                 "programs\\['(.+)'\\]\\s+=\\s+\\{\\}\n"
                                 "programs\\['\\w'\\]\\[\"chaff\"\\]\\s+=\\s+(\\d+)\n"
                                 "programs\\['\\w'\\]\\[\"flare\"\\]\\s+=\\s+(\\d+)\n"
                                 "programs\\['\\w'\\]\\[\"intv\"\\]\\s+=\\s+([\\d\\.]+)\n"
                                 "programs\\['\\w'\\]\\[\"cycle\"\\]\\s+=\\s+(\\d+)\n");

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
        else
            return ok;
    }

    for (char name = mData.last().name.at(0).toLatin1() + 1; name <= 'Z'; ++name){
        CMSProgram program;
        program.name = QString(QLatin1Char(name));
        program.comment = QString("User defined program %1").arg(QChar::fromLatin1(name));

        program.chaff.brstItrv = 2;
        program.flare.brstItrv = 2;
        program.flare.seqQty = 10;
        program.flare.seqItrvPrecision = 0.01;
        program.flare.seqItrv = 100;

        program.flare.brstQtyLbl = QStringLiteral("FLARE");
        program.flare.seqQtyLbl = QStringLiteral("CYCLE");
        program.flare.seqItrvLbl = QStringLiteral("INTRV");
        program.chaff.brstQtyLbl = QStringLiteral("CHAFF");

        program.chaff.isBrstQtySet = true;
        program.flare.isBrstQtySet = true;
        program.flare.isSeqQtySet = true;
        program.flare.isSeqItrvSet = true;

        mData.append(program);
    }


    return ok;
}

void A10CParser::saveContent(QTextStream& stream)
{
    stream<<QStringLiteral("programs = {}\n\n");
    for (const auto& item : mData){
        auto interval =
                NumericUtills::intervalToString(item.flare.seqItrv,
                                                item.flare.seqItrvPrecision);
        QString programStr =
        QString("-- %6\n"
                "programs['%1'] = {}\n"
                "programs['%1'][\"chaff\"] = %2\n"
                "programs['%1'][\"flare\"] = %3\n"
                "programs['%1'][\"intv\"]  = %4\n"
                "programs['%1'][\"cycle\"] = %5\n\n")
                    .arg(item.name)
                    .arg(item.chaff.brstQty)
                    .arg(item.flare.brstQty)
                    .arg(interval)
                    .arg(item.flare.seqQty)
                    .arg(item.comment);
        stream<<programStr;
    }

}

QString A10CParser::programmsStart() const
{
    return QStringLiteral("programs = {}");

}

QString A10CParser::programmsEnd() const
{
    return QStringLiteral("ContainerChaffCapacity");
}


