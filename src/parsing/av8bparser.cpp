#include "av8bparser.h"

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

AV8BParser::AV8BParser(QObject *parent)
    : BaseLuaParser{parent}
{

}


/*
 * Based on a DCS script syntax:
 * --All Expendables
 * EW_ALL_CHAFF_BQTY = 1;
 * EW_ALL_CHAFF_BINT = 0.1;
 * EW_ALL_CHAFF_SQTY = 1;
 * EW_ALL_CHAFF_SINT = 1;
 * EW_ALL_FLARES_SQTY = 1;
 * EW_ALL_FLARES_SINT = 1;
 *
 * --Chaff On1y
 * EW_CHAFF_BQTY = 1;
 * EW_CHAFF_BINT = 0.1;
 * EW_CHAFF_SQTY = 1;
 * EW_CHAFF_SINT = 1;
 *
 * --Flares On1y
 * EW_FLARES_SQTY = 1;
 * EW_FLARES_SINT = 1;
 *
 */
bool AV8BParser::parseData()
{
    mData.clear();

    CMSProgram all, chaff, flare;
    static QRegularExpression re("--(.*)\n"
                                 "EW_ALL_CHAFF_BQTY = (\\d);\n"
                                 "EW_ALL_CHAFF_BINT = (\\d\\.\\d);\n"
                                 "EW_ALL_CHAFF_SQTY = (\\d);\n"
                                 "EW_ALL_CHAFF_SINT = (\\d+);\n"
                                 "EW_ALL_FLARES_SQTY = (\\d+);\n"
                                 "EW_ALL_FLARES_SINT = (\\d+);\n"
                                 "\n"
                                 "--(.*)\n"
                                 "EW_CHAFF_BQTY = (\\d+);\n"
                                 "EW_CHAFF_BINT = (\\d\\.\\d);\n"
                                 "EW_CHAFF_SQTY = (\\d+);\n"
                                 "EW_CHAFF_SINT = (\\d+);\n"
                                 "\n"
                                 "--(.*)\n"
                                 "EW_FLARES_SQTY = (\\d+);\n"
                                 "EW_FLARES_SINT = (\\d+);\n"
                                 );

    QRegularExpressionMatch match = re.match(mContent);
    if (!match.hasMatch()){
        emit errorOccured(Error{tr("Failed to parse CMS config, unknown file format")});
        return false;
    }

    all.name = QStringLiteral("ALL");
    all.comment = match.captured(1);

    all.chaff.brstQty =     NumericUtills::parseInt16(match.captured(2));
    all.chaff.brstItrvPrecision = 0.1;
    all.chaff.brstItrv =
            NumericUtills::parseInterval(match.captured(3), all.chaff.brstItrvPrecision);
    all.chaff.seqQty =     NumericUtills::parseInt16(match.captured(4));
    all.chaff.seqItrvPrecision = 1;
    all.chaff.seqItrv =
            NumericUtills::parseInterval(match.captured(5), all.chaff.seqItrvPrecision);
    all.flare.seqQty =      NumericUtills::parseInt16(match.captured(6));
    all.flare.seqItrvPrecision = 1;
    all.flare.seqItrv =
            NumericUtills::parseInterval(match.captured(7), all.flare.seqItrvPrecision);

    all.chaff.isBrstQtySet = true;
    all.chaff.isBrstItrvSet = true;
    all.chaff.isSeqQtySet = true;
    all.chaff.isSeqItrvSet = true;

    all.flare.isSeqQtySet = true;
    all.flare.isSeqItrvSet = true;

    all.chaff.brstQtyLbl = "CHF BQTY";
    all.chaff.brstItrvLbl = "CHF BINT";
    all.chaff.seqQtyLbl = "CHF SQTY";
    all.chaff.seqItrvLbl = "CHF SINT";

    all.flare.seqQtyLbl = "FLR QTY";
    all.flare.seqItrvLbl = "FLR INT";

    chaff.name = QStringLiteral("CHAFF");
    chaff.comment = match.captured(8);
    chaff.chaff.brstQty =     NumericUtills::parseInt16(match.captured(9));
    chaff.chaff.brstItrvPrecision = 0.1;
    chaff.chaff.brstItrv =
            NumericUtills::parseInterval(match.captured(10), chaff.chaff.brstItrvPrecision);
    chaff.chaff.seqQty =     NumericUtills::parseInt16(match.captured(11));
    chaff.chaff.seqItrvPrecision = 1;
    chaff.chaff.seqItrv =
            NumericUtills::parseInterval(match.captured(12), chaff.chaff.seqItrvPrecision);

    chaff.chaff.isBrstQtySet = true;
    chaff.chaff.isBrstItrvSet = true;
    chaff.chaff.isSeqQtySet = true;
    chaff.chaff.isSeqItrvSet = true;

    chaff.chaff.brstQtyLbl = "CHF BQTY";
    chaff.chaff.brstItrvLbl = "CHF BINT";
    chaff.chaff.seqQtyLbl = "CHF SQTY";
    chaff.chaff.seqItrvLbl = "CHF SINT";

    flare.name = QStringLiteral("FLARES");
    flare.comment = match.captured(13);
    flare.flare.seqQty =      NumericUtills::parseInt16(match.captured(14));
    flare.flare.seqItrvPrecision = 1;
    flare.flare.seqItrv =
            NumericUtills::parseInterval(match.captured(15), flare.flare.seqItrvPrecision);

    flare.flare.isSeqQtySet = true;
    flare.flare.isSeqItrvSet = true;

    flare.flare.seqQtyLbl = "FLR QTY";
    flare.flare.seqItrvLbl = "FLR INT";

    mData.append(all);
    mData.append(chaff);
    mData.append(flare);

    return true;
}

void AV8BParser::saveContent(QTextStream& stream)
{
    stream<<"--"<<mData[0].comment<<"\n";
    stream<<"EW_ALL_CHAFF_BQTY = "<<mData[0].chaff.brstQty<<";\n";
    stream<<"EW_ALL_CHAFF_BINT = "
          <<NumericUtills::intervalToString(mData[0].chaff.brstItrv,
                                            mData[0].chaff.brstItrvPrecision )<<";\n";
    stream<<"EW_ALL_CHAFF_SQTY = "<<mData[0].chaff.seqQty<<";\n";
    stream<<"EW_ALL_CHAFF_SINT = "<<mData[0].chaff.seqItrv<<";\n";
    stream<<"EW_ALL_FLARES_SQTY = "<<mData[0].flare.seqQty<<";\n";
    stream<<"EW_ALL_FLARES_SINT = "<<mData[0].flare.seqItrv<<";\n";
    stream<<"\n";
    stream<<"--"<<mData[1].comment<<"\n";
    stream<<"EW_CHAFF_BQTY = "<<mData[1].chaff.brstQty<<";\n";
    stream<<"EW_CHAFF_BINT = "
          <<NumericUtills::intervalToString(mData[1].chaff.brstItrv,
                                            mData[1].chaff.brstItrvPrecision )<<";\n";
    stream<<"EW_CHAFF_SQTY = "<<mData[1].chaff.seqQty<<";\n";
    stream<<"EW_CHAFF_SINT = "<<mData[1].chaff.seqItrv<<";\n";
    stream<<"\n";
    stream<<"--"<<mData[2].comment<<"\n";
    stream<<"EW_FLARES_SQTY = "<<mData[2].flare.seqQty<<";\n";
    stream<<"EW_FLARES_SINT = "<<mData[2].flare.seqItrv<<";\n";
    stream<<"\n";
}

QString AV8BParser::programmsStart() const
{
    return QStringLiteral("--All Expendables");
}

QString AV8BParser::programmsEnd() const
{
    return QStringLiteral("need_to_be_closed = true");
}
