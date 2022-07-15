#include "cmsmodel.h"
#include "numericutills.h"

CMSModel::CMSModel(parsing::AbstractParser* parser, QObject *parent) :
      QAbstractListModel{parent}
    , pParser(parser)
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
                             .arg(item.chaff)
                             .arg(item.flare)
                             .arg(item.intv)
                             .arg(item.cycle);
            return result;
        }
        case CmsRoles::ChaffRole:
            return item.chaff;
        case CmsRoles::FlareRole:
            return item.flare;
        case CmsRoles::IntvRole:
            return item.intv;
        case CmsRoles::CycleRole:
            return item.cycle;
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
        {FlareRole, "flare"},
        {IntvRole, "intv"},
        {CycleRole, "cycle"}
    };
}

bool CMSModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!hasIndex(index.row(), index.column(), index.parent()))
        return false;

    auto& item = mItems[index.row()];
    bool ok = false;
    switch (role)
    {

        case ChaffRole:{
            quint8 chaff = NumericUtills::parseUint8(value, &ok);
            if (ok)
                item.chaff = chaff;
            break;
        }
        case FlareRole:{
            quint8 flare = NumericUtills::parseUint8(value, &ok);
            if (ok)
                item.flare = flare;
            break;
        }
        case IntvRole:{
            quint8 intv = NumericUtills::parseUint8(value, &ok);
            if (ok)
                item.intv = intv;
            break;
        }
        case CycleRole:{
            quint8 cycle = NumericUtills::parseUint8(value, &ok);
            if (ok)
                item.cycle = cycle;
            break;
        }
        default:
            break;
    }

    if (ok)
        emit layoutChanged();

    return ok;
}

void CMSModel::onDataChanged()
{
    for (const auto& item : pParser->data())
        mItems.append(item);

    emit layoutChanged();
}
