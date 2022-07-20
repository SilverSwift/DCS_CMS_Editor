#include "f16cparser.h"
#include "numericutills.h"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

namespace {
    static QString programmsStart = QStringLiteral("-- Default manual presets");
    static QString programmsEnd = QStringLiteral("-- Auto presets");

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
    : AbstractParser{parent}
{

}

QVector<CMSProgram> F16CParser::data() const
{
    return mData;
}

void F16CParser::setData(const QVector<CMSProgram> dataArg)
{
    mData = std::move(dataArg);
}

void F16CParser::readFromFile(QString path)
{
    mPath = path;

    if (this->readData() &&
        this->parseData())
        emit dataUpdated();
}

void F16CParser::writeToFile(QString path)
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
    stream<<mFooter;

    file.close();
}

bool F16CParser::readData()
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
    mContent = content.mid(progsStartAt, progsEndAt - progsStartAt);
    mFooter = content.right(content.size() - progsEndAt);

//    qDebug().noquote()<<"header:\n"<<mHeader;
//    qDebug().noquote()<<"body:\n"<<mContent;
//    qDebug().noquote()<<"footer:\n"<<mFooter;

    return true;
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
    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.name = match.captured(Name).at(0).toLatin1();
        program.comment = match.captured(Comment);

        program.chaff.brstQty = NumericUtills::parseInt16( match.captured(ChaffBrstQty));
        program.chaff.brstItrvPrecision = 0.001;
        program.chaff.brstItrv = NumericUtills::parseInterval( match.captured(ChaffBrstItrv), program.chaff.brstItrvPrecision);
        program.chaff.seqQty = NumericUtills::parseInt16( match.captured(ChaffSeqQty));
        program.chaff.seqItrvPrecision = 0.01;
        program.chaff.seqItrv = NumericUtills::parseInterval( match.captured(ChaffSeqItrv), program.chaff.seqItrvPrecision);

        program.flare.brstQty = NumericUtills::parseInt16( match.captured(FlareBrstQty));
        program.flare.brstItrvPrecision = 0.001;
        program.flare.brstItrv = NumericUtills::parseInterval( match.captured(FlareBrstItrv), program.flare.brstItrvPrecision);
        program.flare.seqQty = NumericUtills::parseInt16( match.captured(FlareSeqQty));
        program.flare.seqItrvPrecision = 0.01;
        program.flare.seqItrv = NumericUtills::parseInterval( match.captured(FlareSeqItrv), program.flare.seqItrvPrecision);

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

        mData.append(program);
    }

    if ( !ok )
        emit errorOccured(Error{});

    return ok;
}
