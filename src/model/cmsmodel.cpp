#include "cmsmodel.h"

#include "abstractvalidator.h"
#include "numericutills.h"

using namespace model;

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

    const auto& item = mItems.at(index.row());

    switch(role){
        case Qt::DisplayRole:{
            QString result = QString("chaff: %1\tflare: %2\t interval: %3s\tcycles: %4")
                             .arg(item.chaff.burstQuantity)
                             .arg(item.flare.burstQuantity)
                             .arg(item.flare.sequenceInterval)
                             .arg(item.flare.sequenceQuantity);
            return result;
        }
        case CmsRoles::ChaffRole:
            return QStringLiteral("%1").arg(item.chaff.burstQuantity, 3, 10, QLatin1Char(' '));
        case CmsRoles::FlareBQRole:
            return QStringLiteral("%1").arg(item.flare.burstQuantity, 3, 10, QLatin1Char(' '));
        case CmsRoles::IntrvRole:
            return NumericUtills::intervalToString(item.flare.sequenceInterval);
        case CmsRoles::CycleRole:
            return QStringLiteral("%1").arg(item.flare.sequenceQuantity, 3, 10, QLatin1Char(' '));
        case CmsRoles::CommentRole:
            return item.comment;
        case CmsRoles::NameRole:
            return QChar::fromLatin1(item.name);
        default:
            break;
    }

    return QVariant();
}

QVariant CMSModel::headerData(int /*section*/, Qt::Orientation /*orientation*/, int /*role*/) const
{
    return QVariant();
}

int CMSModel::rowCount(const QModelIndex& parent) const
{
    return parent.isValid() ?
                0 :
                mItems.size();
}

QHash<int, QByteArray> CMSModel::roleNames() const
{
    return {
        {ChaffRole, "chaff"},
        {FlareBQRole, "flare"},
        {IntrvRole, "intv"},
        {CycleRole, "cycle"},
        {CommentRole, "comment"},
        {NameRole, "name"},
        {ChaffIncRole, "chaffinc"},
        {FlareIncRole, "flareinc"},
        {InrtvIncRole, "intvinc"},
        {CycleIncRole, "cycleinc"},
        {ChaffDecRole, "chaffdec"},
        {FlareDecRole, "flaredec"},
        {IntrvDecRole, "intvdec"},
        {CycleDecRole, "cycledec"}
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
        case ChaffRole:{
            quint8 chaff = NumericUtills::parseUint8(value, &ok);
            if (ok)
                item.chaff.burstQuantity = chaff;
            break;
        }
        case FlareBQRole:{
            quint8 flare = NumericUtills::parseUint8(value, &ok);
            if (ok)
                item.flare.burstQuantity = flare;
            break;
        }
        case IntrvRole:{
            quint8 intv = NumericUtills::parseInterval(value, &ok);
            if (ok)
                item.flare.sequenceInterval = intv;
            break;
        }
        case CycleRole:{
            quint8 cycle = NumericUtills::parseUint8(value, &ok);
            if (ok)
                item.flare.sequenceQuantity = cycle;
            break;
        }
        case CommentRole:
            item.comment = value.toString();
            break;
        case NameRole:
            item.name = value.toString().at(0).toLatin1();
            break;

        //increment/decrement actions
        case ChaffIncRole: pValidator->incChaff(item.chaff.burstQuantity); break;
        case FlareIncRole: pValidator->incFlare(item.flare.burstQuantity); break;
        case InrtvIncRole: pValidator->incIntrv(item.flare.sequenceInterval); break;
        case CycleIncRole: pValidator->incCycle(item.flare.sequenceQuantity); break;
        case ChaffDecRole:pValidator->decChaff(item.chaff.burstQuantity); break;
        case FlareDecRole:pValidator->decFlare(item.flare.burstQuantity); break;
        case IntrvDecRole:pValidator->decIntrv(item.flare.sequenceInterval); break;
        case CycleDecRole:pValidator->decCycle(item.flare.sequenceQuantity); break;

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
