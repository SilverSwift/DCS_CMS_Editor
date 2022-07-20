#include "a10cparser.h"
#include "numericutills.h"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

namespace {
    static QString programmsStart = QStringLiteral("programs = {}");
    static QString programmsEnd = QStringLiteral("ContainerChaffCapacity");

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
    : AbstractParser(parent)
{

}

QVector<CMSProgram> A10CParser::data() const
{
    return mData;
}

void A10CParser::setData(const QVector<CMSProgram> dataArg)
{
    mData = std::move(dataArg);
}

void A10CParser::readFromFile(QString path)
{
    mPath = path;

    if (this->readData() &&
        this->parseData())
        emit dataUpdated();

}

void A10CParser::writeToFile(QString path)
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
    stream<<mFooter;

    file.close();

}

bool A10CParser::readData()
{
    mData.clear();
    Error error;
    QFile file(mPath);

    if (!file.open(QFile::ReadOnly | QFile::Text)){
        error.errorMsg = tr("Failed to read file: %1\nDetails: %2")
                         .arg(mPath).arg(file.errorString());
        emit errorOccured(error);
        return false;
    }

    QTextStream stream (&file);
    QString content = stream.readAll();

    int progsStartAt = content.indexOf(::programmsStart);
    if (progsStartAt == -1){
        error.errorMsg = tr("Failed to parse file: %1").arg(mPath);
        emit errorOccured(error);
        return false;
    }

    int progsEndAt = content.indexOf(::programmsEnd);
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
    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.name = match.captured(Name);
        program.comment = match.captured(Comment);

        program.chaff.brstQty = NumericUtills::parseInt16( match.captured(Chaff));
        program.flare.brstQty = NumericUtills::parseInt16(match.captured(Flare));
        program.flare.seqItrvPrecision = 0.01;
        program.flare.seqItrv =
                NumericUtills::parseInterval(match.captured(Intv),
                                             program.flare.seqItrvPrecision);
        program.flare.seqQty= NumericUtills::parseInt16(match.captured(Cycle));

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


    if ( !ok )
        emit errorOccured(Error{});

    return ok;
}


