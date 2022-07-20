#include "cmsmodel.h"

#include "abstractvalidator.h"
#include "numericutills.h"

using namespace model;

namespace {
    static const QString value = QStringLiteral("value");
    static const QString label = QStringLiteral("label");
    static const QString isUsed = QStringLiteral("isUsed");
}

CMSModel::CMSModel(parsing::AbstractParser* parser,
                   AbstractValidator* validator,
                   QObject *parent) :
      QAbstractListModel{parent}
    , pParser(parser)
    , pValidator(validator)
{

}

QVariant CMSModel::data(const QModelIndex& index, int role) const
{
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return QVariant();

    const auto item = mItems.at(index.row());

    switch(role){
        case CmsRoles::ChaffBrstQtyRole:{
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsIntLiteral(item.chaff.brstQty)},
                {::label, item.chaff.brstQtyLbl},
                {::isUsed, item.chaff.isBrstQtySet}
            };
        }

        case CmsRoles::ChaffBrstInrvRole:
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsDoubleLiteral(item.chaff.brstItrv, item.chaff.brstItrvPrecision)},
                {::label, item.chaff.brstItrvLbl},
                {::isUsed, item.chaff.isBrstItrvSet}
            };

        case CmsRoles::ChaffSeqQtyRole:
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsIntLiteral(item.chaff.seqQty)},
                {::label, item.chaff.seqQtyLbl},
                {::isUsed, item.chaff.isSeqQtySet}
            };
        case CmsRoles::ChaffSeqInrvRole:
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsDoubleLiteral(item.chaff.seqItrv, item.chaff.seqItrvPrecision)},
                {::label, item.chaff.seqItrvLbl},
                {::isUsed, item.chaff.isSeqItrvSet}
            };

        case CmsRoles::FlareBrstQtyRole:
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsIntLiteral(item.flare.brstQty)},
                {::label, item.flare.brstQtyLbl},
                {::isUsed, item.flare.isBrstQtySet}
            };

        case CmsRoles::FlareBrstInrvRole:
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsDoubleLiteral(item.flare.brstItrv, item.flare.brstItrvPrecision)},
                {::label, item.flare.brstItrvLbl},
                {::isUsed, item.flare.isBrstItrvSet}
            };

        case CmsRoles::FlareSeqQtyRole:
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsIntLiteral(item.flare.seqQty)},
                {::label, item.flare.seqQtyLbl},
                {::isUsed, item.flare.isSeqQtySet}
            };
        case CmsRoles::FlareSeqInrvRole:
            return QVariantMap{
                {::value, NumericUtills::fiveDigitsDoubleLiteral(item.flare.seqItrv, item.flare.seqItrvPrecision)},
                {::label, item.flare.seqItrvLbl},
                {::isUsed, item.flare.isSeqItrvSet}
            };

        case CmsRoles::ChaffIsSlave:
            return  item.chaff.isBrstQtySet &&
                    !item.chaff.isBrstItrvSet &&
                    !item.chaff.isSeqItrvSet &&
                    !item.chaff.isSeqQtySet;

        case CmsRoles::CommentRole:
            return item.comment;
        case CmsRoles::NameRole:
            return item.name;
        default:
            break;
    }

    return QVariant();
}

int CMSModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ? 0 : mItems.size();
}

QHash<int, QByteArray> CMSModel::roleNames() const
{
    return {
        {ChaffBrstQtyRole,  "chaffBrstQty"},
        {ChaffBrstInrvRole, "chaffBrstInrv"},
        {ChaffSeqQtyRole,   "chaffSeqQty"},
        {ChaffSeqInrvRole,  "chaffSeqInrv"},

        {FlareBrstQtyRole,  "flareBrstQty"},
        {FlareBrstInrvRole, "flareBrstInrv"},
        {FlareSeqQtyRole,   "flareSeqQty"},
        {FlareSeqInrvRole,  "flareSeqInrv"},

        {ChaffIsSlave, "chaffIsSlave"},

        {CommentRole, "comment"},
        {NameRole, "name"}
    };
}

bool CMSModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return false;

    auto& item = mItems[index.row()];
    bool ok = true;
    switch (role)
    {
        case ChaffBrstQtyRole:
            value == 1 ?
                        pValidator->incChaffBrstQty(item.chaff.brstQty) :
                        pValidator->decChaffBrstQty(item.chaff.brstQty) ;
            break;

        case ChaffBrstInrvRole:
            value == 1 ?
                        pValidator->incChaffBrstItrv(item.chaff.brstItrv) :
                        pValidator->decChaffBrstItrv(item.chaff.brstItrv) ;
            break;

        case ChaffSeqQtyRole:
            value == 1 ?
                        pValidator->incChaffSeqQty(item.chaff.seqQty) :
                        pValidator->decChaffSeqQty(item.chaff.seqQty) ;
            break;
        case ChaffSeqInrvRole:
            value == 1 ?
                        pValidator->incChaffSeqItrv(item.chaff.seqItrv) :
                        pValidator->decChaffSeqItrv(item.chaff.seqItrv) ;
            break;

        case FlareBrstQtyRole:
            value == 1 ?
                        pValidator->incFlareBrstQty(item.flare.brstQty) :
                        pValidator->decFlareBrstQty(item.flare.brstQty) ;
            break;

        case FlareBrstInrvRole:
            value == 1 ?
                        pValidator->incFlareBrstItrv(item.flare.brstItrv) :
                        pValidator->decFlareBrstItrv(item.flare.brstItrv) ;

            break;

        case FlareSeqQtyRole:
            value == 1 ?
                        pValidator->incFlareSeqQty(item.flare.seqQty) :
                        pValidator->decFlareSeqQty(item.flare.seqQty) ;
            break;

        case FlareSeqInrvRole:{
            value == 1 ?
                        pValidator->incFlareSeqItrv(item.flare.seqItrv) :
                        pValidator->decFlareSeqItrv(item.flare.seqItrv) ;
            break;
        }

        case CommentRole:
            item.comment = value.toString();
            break;
        case NameRole:
            item.name = value.toString().at(0).toLatin1();
            break;
        default:
            ok = false;
            break;
    }

    if (ok)
        emit dataChanged(index, index);

    return ok;
}

void CMSModel::onDataChanged()
{
    mItems.clear();
    for (const auto& item : pParser->data())
        mItems.append(item);

    emit layoutChanged();
}

void CMSModel::save()
{
    pParser->setData(mItems);
    pParser->writeToFile();
}
