#ifndef A10CPARSER_H
#define A10CPARSER_H

#include "AbstractParser.h"

namespace parsing{

    class A10CParser : public AbstractParser
    {
        Q_OBJECT
    public:
        explicit A10CParser(QObject* parent = nullptr);
        virtual ~A10CParser() override;

        virtual QVector <CMSProgram> data() const override;
        virtual void setData(const QVector<CMSProgram> dataArg) override;
        virtual void readFromFile(QString path) override;
        virtual void writeToFile(QString path = {}) override;
    };

}

#endif // A10CPARSER_H
