#ifndef FA18CPARCER_H
#define FA18CPARCER_H

#include "abstractparser.h"

namespace parsing {

/*
 * FA18CParser class works with CMDS_ALE47.lua
 * F/A-18C CMSP has the following values in DCS
 * cycles 1-24 step 1
 * chaff/flare 0-100 step 1
 * intervall 0.25-5.00 step 0.25
 */
    class FA18CParcer : public AbstractParser
    {
        Q_OBJECT
    public:
        explicit FA18CParcer(QObject *parent = nullptr);
        ~FA18CParcer() override = default;

        virtual QVector <CMSProgram> data() const override;
        virtual void setData(const QVector<CMSProgram> dataArg) override;
        virtual void readFromFile(QString path) override;
        virtual void writeToFile(QString path = {}) override;

    private:
        bool readData();
        bool parseData();

        QVector<CMSProgram> mData;

        QString mPath;
        QString mHeader;
        QString mContent;
        QString mFooter;
    };

}
#endif // FA18CPARCER_H
