#include "baseluaparser.h"
#include <QFile>
#include <QTextStream>


using namespace parsing;

BaseLuaParser::BaseLuaParser(QObject *parent)
    : AbstractParser{parent}
{

}

QVector<CMSProgram> BaseLuaParser::data() const
{
    return mData;
}

void BaseLuaParser::setData(const QVector<CMSProgram> dataArg)
{
    mData = std::move(dataArg);
}

void BaseLuaParser::readFromFile(QString path)
{
    mPath = path;

    if (this->readData() &&
        this->parseData())
        emit dataUpdated();
}

void BaseLuaParser::writeToFile(QString path)
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

    saveContent(stream);

    stream<<mFooter;

    file.close();
}

bool BaseLuaParser::readData()
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

    int progsStartAt = content.indexOf(programmsStart());
    if (progsStartAt == -1){
        error.errorMsg = tr("Failed to parse file: %1").arg(mPath);
        emit errorOccured(error);
        return false;
    }

    int progsEndAt = content.indexOf(programmsEnd());
    if (progsEndAt == -1){
        error.errorMsg = tr("Failed to parse file: %1").arg(mPath);
        emit errorOccured(error);
        return false;
    }

    mHeader = content.left(progsStartAt);
    mContent = content.mid(progsStartAt, progsEndAt - progsStartAt);
    mFooter = content.right(content.size() - progsEndAt);

    qDebug().noquote()<<"header:\n"<<mHeader;
    qDebug().noquote()<<"body:\n"<<mContent;
    qDebug().noquote()<<"footer:\n"<<mFooter;

    return true;
}

