#ifndef PARSING_TYPES_H
#define PARSING_TYPES_H
#include <QString>

namespace parsing{

/*
 * Describes an expandable counter measures resource
 * It may seem like lables and isSet flags must be set
 * for the entire vector of CMSProgramms.
 * But it is not valid at least for the AV-8B...
 *
 */
struct Expendable{
    QString brstQtyLbl;
    QString brstItrvLbl;
    QString seqQtyLbl;
    QString seqItrvLbl;

    qint16 brstQty;
    qint16 brstItrv;
    float brstItrvPrecision;
    qint16 seqQty;
    qint16 seqItrv;
    float seqItrvPrecision;

    bool isBrstQtySet = false;
    bool isBrstItrvSet = false;
    bool isSeqQtySet = false;
    bool isSeqItrvSet = false;
};
/*
 * Describes a CMS programm
 */
struct CMSProgram {
    QString comment;
    QString name;
    Expendable flare;
    Expendable chaff;
    //unused for now, but need to keep in mind
//        Expendable other1;
//        Expendable other2;
};

struct Error {
    QString errorMsg;
};

}
#endif // PARSING_TYPES_H
