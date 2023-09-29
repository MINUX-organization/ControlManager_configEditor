#include "configitemmodel.h"

#include "configsLib/configworker.h"

struct TreeItem
{
    QVariant data;
    TreeItem * parent {nullptr};
    QVector<TreeItem *> childrenVect;
    QModelIndex index;
};

struct ConfigItemModel::Impl
{
    TreeItem head;
    ConfigsLib::ConfigWorker m_configWorker;
};

ConfigItemModel::ConfigItemModel(QObject *parent)
    : QAbstractItemModel(parent),
    m_pImpl{ new Impl }
{

}

QVariant ConfigItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex ConfigItemModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex ConfigItemModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int ConfigItemModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int ConfigItemModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ConfigItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
