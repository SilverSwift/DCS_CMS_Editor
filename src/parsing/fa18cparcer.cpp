#include "fa18cparcer.h"
#include "numericutills.h"

#include <QDebug>
#include <QFile>
#include <QRegularExpression>
#include <QTextStream>

using namespace parsing;

namespace {
    static QString programmsStart = QStringLiteral("-- Default manual presets");
    static QString programmsEnd = QStringLiteral("-- MAN 6 - Wall Dispense button, Panic");

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
    : AbstractParser{parent}
{

}

QVector<CMSProgram> FA18CParcer::data() const
{
    return mData;
}

void FA18CParcer::setData(const QVector<CMSProgram> dataArg)
{
    mData = std::move(dataArg);
}

void FA18CParcer::readFromFile(QString path)
{
    mPath = path;

    if (this->readData() &&
        this->parseData())
        emit dataUpdated();
}

void FA18CParcer::writeToFile(QString path)
{
    Error error;
    if (path.isEmpty())
        path = mPath;

    QFile file(path);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)){
        error.errorMsg = tr("Failed to write file: %1\nDetails: %2")
                         .arg(mPath).arg(file.errorString());
        emit errorOccured(error);
        return;
    }

    QTextStream stream (&file);
    stream<<mHeader;
    stream<<::programmsStart<<"\n";
    for (const auto& item : mData){
        QString programStr =
        QString("-- %6\n"
                "programs[ProgramNames.MAN_%1] = {}\n"
                "programs[ProgramNames.MAN_%1][\"chaff\"] = %2\n"
                "programs[ProgramNames.MAN_%1][\"flare\"] = %3\n"
                "programs[ProgramNames.MAN_%1][\"intv\"]  = %4\n"
                "programs[ProgramNames.MAN_%1][\"cycle\"] = %5\n\n")
                    .arg(QLatin1Char(item.name)).arg(item.chaff)
                    .arg(item.flare).arg(NumericUtills::intervalToString(item.intrv))
                    .arg(item.cycle).arg(item.comment);
        stream<<programStr;
    }
    stream<<mFooter;

    file.close();
}

bool FA18CParcer::readData()
{
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
    while(i.hasNext()){
        QRegularExpressionMatch match = i.next();

        CMSProgram program;
        program.name = match.captured(Name).at(0).toLatin1();
        program.comment = match.captured(Comment);
        program.chaff = NumericUtills::parseUint8( match.captured(Chaff));
        program.flare = NumericUtills::parseUint8(match.captured(Flare));
        program.intrv = NumericUtills::parseInterval(match.captured(Intv));
        program.cycle = NumericUtills::parseUint8(match.captured(Cycle));

        mData.append(program);
    }

    if ( !ok ){
        emit errorOccured(Error{});
    }
    return ok;
}
