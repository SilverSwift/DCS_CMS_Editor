#include "mockparser.h"
#include <QDebug>

using namespace parsing;

MockParser::MockParser(QObject *parent)
    : AbstractParser(parent)
{

}
MockParser::~MockParser()
{

}

QVector<CMSProgram> MockParser::data() const
{
    return mProgramms;
}

void MockParser::setData(const QVector<CMSProgram> dataArg)
{
    mProgramms = std::move(dataArg);
}

void MockParser::readFromFile(QString path)
{
    qDebug()<<Q_FUNC_INFO<<"path:"<<path;

    for (quint8 i = 0; i < 5; i++)
        mProgramms.append({QStringLiteral("comment"), 'X', i, i, i, i});

    emit dataUpdated();

}

void MockParser::writeToFile(QString path)
{
    qDebug()<<Q_FUNC_INFO<<"path:"<<path;
}

