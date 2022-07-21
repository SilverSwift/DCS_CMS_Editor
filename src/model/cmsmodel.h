#ifndef CMSMODEL_H
#define CMSMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <abstractparser.h>

namespace model {

class AbstractValidator;
class CMSModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(CmsRoles)
public:

    enum CmsRoles{
        NameRole= Qt::UserRole + 1,
        CommentRole,

        ChaffBrstQtyRole,
        ChaffBrstInrvRole,
        ChaffSeqQtyRole,
        ChaffSeqInrvRole,

        FlareBrstQtyRole,
        FlareBrstInrvRole,
        FlareSeqQtyRole,
        FlareSeqInrvRole,

        ChaffIsSlave
    };

    explicit CMSModel(parsing::AbstractParser* parser,
                      AbstractValidator* validator,
                      QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QHash<int,QByteArray> roleNames() const override;

    virtual bool setData(const QModelIndex &index, const QVariant &value,
                         int role = Qt::EditRole) override;

    void onDataChanged();

    void save();

signals:
    void info(QString msg);

private:
    QVector<parsing::CMSProgram> mItems;
    parsing::AbstractParser* pParser = nullptr;
    AbstractValidator* pValidator = nullptr;
};

}

#endif // CMSMODEL_H
