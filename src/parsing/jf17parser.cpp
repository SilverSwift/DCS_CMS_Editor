#include "jf17parser.h"
#include "jf17intervals.h"
#include "numericutills.h"

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

JF17Parser::JF17Parser(QObject *parent)
    : AbstractParser{parent}
{

}

QVector<CMSProgram> JF17Parser::data() const
{
    return mData;
}

void JF17Parser::setData(const QVector<CMSProgram> dataArg)
{
    mData = std::move(dataArg);
}

bool JF17Parser::readFromFile(QString path)
{

    mPath = path;

    bool ok = this->readData() &&
              this->parseData();

    emit dataUpdated();

    return ok;
}

void JF17Parser::writeToFile(QString path)
{
    Error error;
    if (path.isEmpty())
        path = mPath;

    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)){
        error.errorMsg = tr("Failed to write file: %1\nDetails: %2")
                         .arg(mPath, file.errorString());
        emit errorOccured(error);
        return;
    }

    QTextStream stream (&file);
    stream<<mHeader;

    for (const auto& item : mData){
        auto chaffBrstItrv = chaffBurstIntervals.key(item.chaff.brstItrv);
        auto chaffSeqItrv = sequenceIntervals.key(item.chaff.seqItrv);
        auto flareBrstItrv = flareBurstIntervals.key(item.flare.brstItrv);
        auto flareSeqItrv = sequenceIntervals.key(item.flare.seqItrv);

        ProgramType type = ChaffFlare;
        if (!item.chaff.brstQty || !item.chaff.seqQty)
            type = FlareOnly;
        else if (!item.flare.brstQty || !item.flare.seqQty)
            type = ChaffOnly;

        if (!item.comment.isEmpty())
            stream<<"\t\t\t--"<<item.comment<<"\n";

        QString programStr = QStringLiteral(
            "\t\t\t[\"PROG0%1CHBI\"] = %2,\n"
            "\t\t\t[\"PROG0%1CHI\"] = %3,\n"
            "\t\t\t[\"PROG0%1CHN\"] = %4,\n"
            "\t\t\t[\"PROG0%1CHR\"] = %5,\n"
            "\t\t\t[\"PROG0%1FLBI\"] = %6,\n"
            "\t\t\t[\"PROG0%1FLI\"] = %7,\n"
            "\t\t\t[\"PROG0%1FLN\"] = %8,\n"
            "\t\t\t[\"PROG0%1FLR\"] = %9,\n"
            "\t\t\t[\"PROG0%1TYPE\"] = %10,\n"
            )   .arg(item.name)
                .arg(chaffBrstItrv)
                .arg(chaffSeqItrv)
                .arg(item.chaff.brstQty)
                .arg(item.chaff.seqQty)
                .arg(flareBrstItrv)
                .arg(flareSeqItrv)
                .arg(item.flare.brstQty)
                .arg(item.flare.seqQty)

                .arg(int(type));

        stream<<programStr;
    }

    stream<<mFooter;

    file.close();
}

#ifdef QT_DEBUG
void JF17Parser::serialize(QString outputFile)
{
    QFile backup(outputFile);
    backup.open( QFile::Truncate | QFile::WriteOnly );

    QDataStream stream(&backup);
    stream.setVersion(QDataStream::Qt_6_0);

    for (auto& item : mData)
        stream  <<item.comment << item.name

            <<item.chaff.brstQtyLbl
            <<item.chaff.brstItrvLbl
            <<item.chaff.seqQtyLbl
            <<item.chaff.seqItrvLbl
            <<item.chaff.brstQty
            <<item.chaff.brstItrv
            <<item.chaff.brstItrvPrecision
            <<item.chaff.seqQty
            <<item.chaff.seqItrv
            <<item.chaff.seqItrvPrecision
            <<item.chaff.isBrstQtySet
            <<item.chaff.isBrstItrvSet
            <<item.chaff.isSeqQtySet
            <<item.chaff.isSeqItrvSet

            <<item.flare.brstQtyLbl
            <<item.flare.brstItrvLbl
            <<item.flare.seqQtyLbl
            <<item.flare.seqItrvLbl
            <<item.flare.brstQty
            <<item.flare.brstItrv
            <<item.flare.brstItrvPrecision
            <<item.flare.seqQty
            <<item.flare.seqItrv
            <<item.flare.seqItrvPrecision
            <<item.flare.isBrstQtySet
            <<item.flare.isBrstItrvSet
            <<item.flare.isSeqQtySet
            <<item.flare.isSeqItrvSet
          ;
    backup.close();
}
#endif

void JF17Parser::initFromDefaults(QString name)
{
    QFile backup(":/defaults/" + name);

    if (!backup.open(QFile::ReadOnly)){
        emit errorOccured(Error{tr("Failed to read defaults file for %1").arg(name)});
        return;
    }

    mData.clear();

    QDataStream stream (&backup);
    stream.setVersion(QDataStream::Qt_6_0);

    while(!stream.atEnd()){
        CMSProgram item;
        stream  >>item.comment >> item.name

                >>item.chaff.brstQtyLbl
                >>item.chaff.brstItrvLbl
                >>item.chaff.seqQtyLbl
                >>item.chaff.seqItrvLbl
                >>item.chaff.brstQty
                >>item.chaff.brstItrv
                >>item.chaff.brstItrvPrecision
                >>item.chaff.seqQty
                >>item.chaff.seqItrv
                >>item.chaff.seqItrvPrecision
                >>item.chaff.isBrstQtySet
                >>item.chaff.isBrstItrvSet
                >>item.chaff.isSeqQtySet
                >>item.chaff.isSeqItrvSet

                >>item.flare.brstQtyLbl
                >>item.flare.brstItrvLbl
                >>item.flare.seqQtyLbl
                >>item.flare.seqItrvLbl
                >>item.flare.brstQty
                >>item.flare.brstItrv
                >>item.flare.brstItrvPrecision
                >>item.flare.seqQty
                >>item.flare.seqItrv
                >>item.flare.seqItrvPrecision
                >>item.flare.isBrstQtySet
                >>item.flare.isBrstItrvSet
                >>item.flare.isSeqQtySet
                >>item.flare.isSeqItrvSet
        ;

        mData.append(item);
    }
}

bool JF17Parser::readData()
{
    mData.clear();
    Error error;
    QFile file(mPath);

    if (!file.open(QFile::ReadOnly | QFile::Text)){
        error.errorMsg = tr("Failed to read file: %1\nDetails: %2")
                         .arg(mPath, file.errorString());
        emit errorOccured(error);
        return false;
    }

    QTextStream stream (&file);
    QString content = stream.readAll();

    int progsStartAt = content.indexOf("[\"JF-17\"] = {");
    progsStartAt = content.indexOf("\t\t\t[\"PROG01CHBI\"]", progsStartAt);

    if (progsStartAt == -1){
        error.errorMsg = tr("Failed to parse file: %1").arg(mPath);
        emit errorOccured(error);
        return false;
    }

    int progsEndAt = content.indexOf("\t\t\t[\"RDR_ELEV\"]", progsStartAt);
    if (progsEndAt == -1){
        error.errorMsg = tr("Failed to parse file: %1").arg(mPath);
        emit errorOccured(error);
        return false;
    }
    mHeader = content.left(progsStartAt);
    mContent = content.mid(progsStartAt, progsEndAt - progsStartAt);
    mFooter = content.right(content.size() - progsEndAt);

//    qDebug().noquote()<<"header:\n"<<mHeader;
//    qDebug().noquote()<<"body:\n"<<mContent;
//    qDebug().noquote()<<"footer:\n"<<mFooter;
    return true;
}

bool JF17Parser::parseData()
{
    mData.clear();

    static QRegularExpression re(
        "(\\s*--(.*)\n)?"
        "\\s*\\[\"PROG0(\\d)CHBI\"\\] = (\\d+),\n"
        "\\s*\\[\"PROG0\\dCHI\"\\] = (\\d+),\n"
        "\\s*\\[\"PROG0\\dCHN\"\\] = (\\d+),\n"
        "\\s*\\[\"PROG0\\dCHR\"\\] = (\\d+),\n"
        "\\s*\\[\"PROG0\\dFLBI\"\\] = (\\d+),\n"
        "\\s*\\[\"PROG0\\dFLI\"\\] = (\\d+),\n"
        "\\s*\\[\"PROG0\\dFLN\"\\] = (\\d+),\n"
        "\\s*\\[\"PROG0\\dFLR\"\\] = (\\d+),\n");

    QRegularExpressionMatchIterator i = re.globalMatch(mContent);

    bool ok = true;
    while(i.hasNext() && ok){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.comment = match.captured(Comment);
        program.name = match.captured(Name);

        ok = ok && parseInt16(program.chaff.brstQty, ChaffBrstQty, match, ok);
        /* HACK: there is no value 3 for chaff burst interval
        * in dcs settings window it shows value 0.0s
        * if 3 was defined in config, still it might present
        * in config by default, so we have to hack it
        */

        if (match.captured(ChaffBrstItrv) == QStringLiteral("3")){
            qDebug()<<"HACK";
            program.chaff.brstItrv = 0;
        }
        else
            ok = ok && parseInterval(program.chaff.brstItrv, ChaffBrstItrv, chaffBurstIntervals, match, ok);

        ok = ok && parseInt16(program.chaff.seqQty, ChaffSeqQty, match, ok);
        ok = ok && parseInterval(program.chaff.seqItrv, ChaffSeqItrv, sequenceIntervals, match, ok);

        ok = ok && parseInt16(program.flare.brstQty, FlareBrstQty, match, ok);
        ok = ok && parseInterval(program.flare.brstItrv, FlareBrstItrv, flareBurstIntervals, match, ok);
        ok = ok && parseInt16(program.flare.seqQty, FlareSeqQty, match, ok);
        ok = ok && parseInterval(program.flare.seqItrv, FlareSeqItrv, sequenceIntervals, match, ok);

        program.chaff.brstItrvPrecision = precision;
        program.chaff.seqItrvPrecision = precision;
        program.flare.brstItrvPrecision = precision;
        program.flare.seqItrvPrecision = precision;

        program.chaff.brstQtyLbl = QStringLiteral("CHAFF");
        program.chaff.brstItrvLbl = QStringLiteral("BURST INTRV");
        program.chaff.seqQtyLbl = QStringLiteral("SERIES");
        program.chaff.seqItrvLbl = QStringLiteral("INTERVAL");

        program.flare.brstQtyLbl = QStringLiteral("FLARE");
        program.flare.brstItrvLbl = QStringLiteral("BURST INTRV");
        program.flare.seqQtyLbl = QStringLiteral("SERIES");
        program.flare.seqItrvLbl = QStringLiteral("INTERVAL");

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
    if (!ok)
        emit errorOccured(Error{QStringLiteral("Failed to parse settings for JF-17")});

    return ok;

}

qint16 JF17Parser::parseInt16(qint16& value, Parameters param, QRegularExpressionMatch match, bool& ok)
{
    value = NumericUtills::parseInt16( match.captured(param), &ok);
    if (!ok){
        QString details =
            tr("Parsing faield due to unexpected value: %1")
            .arg(match.captured(param));
        emit errorOccured(Error{details});
    }
    return ok;
}

qint16 JF17Parser::parseInterval(qint16& value, Parameters param, QMap<qint16, qint16> params, QRegularExpressionMatch match, bool& ok)
{
    value = NumericUtills::parseInt16(match.captured(param), &ok);
    if (!ok){
        QString details =
                tr("Parsing interval faield due to unexpected value: %1")
                .arg(match.captured(param));
        emit this->errorOccured(Error{details});
        return ok;
    }

    ok = params.contains(value);
    value = params.value(value);
    return ok;
}
