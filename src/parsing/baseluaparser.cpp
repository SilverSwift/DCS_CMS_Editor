#include "baseluaparser.h"
#include <QDataStream>
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

bool BaseLuaParser::readFromFile(QString path)
{
    mPath = path;

    bool ok = this->readData() &&
              this->parseData();

    emit dataUpdated();

    return ok;
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
#ifdef QT_DEBUG
void BaseLuaParser::serialize(QString outputFile)
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

void BaseLuaParser::initFromDefaults(QString name)
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
    //if there is no footer progsEndAt is 0
    if (progsEndAt)
        mFooter = content.right(content.size() - progsEndAt);

//    qDebug().noquote()<<"header:\n"<<mHeader;
//    qDebug().noquote()<<"body:\n"<<mContent;
//    qDebug().noquote()<<"footer:\n"<<mFooter;

    return true;
}

