#include "a10cparser.h"

using namespace parsing;

A10CParser::A10CParser(QObject* parent) :
    AbstractParser(parent)
{

}

A10CParser::~A10CParser()
{

}

QVector<CMSProgram> A10CParser::data() const
{
    return QVector<CMSProgram>();
}

void A10CParser::setData(const QVector<CMSProgram> dataArg)
{

}

void A10CParser::readFromFile(QString path)
{

}

void A10CParser::writeToFile(QString path)
{

}
