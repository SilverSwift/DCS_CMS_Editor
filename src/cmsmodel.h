#ifndef CMSMODEL_H
#define CMSMODEL_H

#include <QAbstractListModel>
#include <QObject>
#include <AbstractParser.h>



class CMSModel : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(CmsRoles)
public:

    enum CmsRoles{
        ChaffRole = Qt::UserRole + 1,
        FlareRole,
        IntvRole,
        CycleRole,
        CommentRole,
        NameRole
    };

    explicit CMSModel(parsing::AbstractParser* parser,
                      QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const override;

    virtual QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    virtual QHash<int,QByteArray> roleNames() const override;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void onDataChanged();

private:
    QVector<parsing::CMSProgram> mItems;
    parsing::AbstractParser* pParser;
};


#endif // CMSMODEL_H
