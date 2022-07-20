#include "m2000cparser.h"
#include "numericutills.h"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

namespace {
    static QString programmsStart = QStringLiteral("programs = {}");
    static QString programmsEnd = QStringLiteral("");

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
    : AbstractParser{parent}
{

}

QVector<CMSProgram> M2000CParser::data() const
{
    return mData;
}

void M2000CParser::setData(const QVector<CMSProgram> dataArg)
{
    mData = std::move(dataArg);

}

void M2000CParser::readFromFile(QString path)
{
    mPath = path;

    if (this->readData() &&
        this->parseData())
        emit dataUpdated();
}

void M2000CParser::writeToFile(QString path)
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
    stream<<::programmsStart<<"\n";
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

    file.close();
}

bool M2000CParser::readData()
{
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
    mContent = content.right(content.size() - progsStartAt);
    //mFooter = content.right(content.size() - progsEndAt);

//    qDebug().noquote()<<"header:\n"<<mHeader;
//    qDebug().noquote()<<"body:\n"<<mContent;
//    qDebug().noquote()<<"footer:\n"<<mFooter;

    return true;
}
/*
 * Based on DCS script syntax:
 *
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
    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.comment = match.captured(Comment);
        program.name = match.captured(Name);
        program.chaff.brstQty = NumericUtills::parseInt16( match.captured(Chaff));
        program.flare.brstQty = NumericUtills::parseInt16(match.captured(Flare));
        program.flare.seqQty = NumericUtills::parseInt16(match.captured(Cycle));

        //because inegral number of miliseconds saved in a file
        program.flare.seqItrvPrecision = 0.01;
        program.flare.seqItrv = NumericUtills::parseInterval( match.captured(C_intv), 1);
        program.flare.brstItrvPrecision = 0.01;
        program.flare.brstItrv = NumericUtills::parseInterval(match.captured(Intv), 1);

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

        mData.append(program);
    }

    if ( !ok )
        emit errorOccured(Error{});

    return ok;
}
