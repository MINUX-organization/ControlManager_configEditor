#include "configitemmodel.h"

#include "configsLib/configworker.h"

#include "treemodelhandler.h"

using namespace ConfigItemModel;

struct ConfigItemTreeModel::Impl
{
    TreeModelHandler m_handler;
    ConfigsLib::ConfigWorker m_configWorker;

    ConfigItemTreeModel * m_mainClass {nullptr};

    Impl(ConfigItemTreeModel * parent) : m_mainClass{ parent }
    {
        if (!m_mainClass)
        {
            throw std::runtime_error("[ConfigItemTreeModel] Class init error!");
        }
    }

    QModelIndex findIndex(int row, int column, const QModelIndex & parent)
    {

    }
};

ConfigItemTreeModel::ConfigItemTreeModel(QObject *parent)
    : QAbstractItemModel(parent),
    m_pImpl{ new Impl(this) }
{

}

ConfigItemTreeModel::~ConfigItemTreeModel()
{

}


#define DECLARE_CALL(func)                                                      ConfigItemTreeModel::func()                                                 { return m_pImpl->func(); }
#define DECLARE_CALL_CONST(func)                                                ConfigItemTreeModel::func()                                         const   { return m_pImpl->func(); }
#define DECLARE_CALL_1ARG(func, type1, arg1)                                    ConfigItemTreeModel::func(type1 arg1)                                       { return m_pImpl->func(arg1); }
#define DECLARE_CALL_2ARG(func, type1, arg1, type2, arg2)                       ConfigItemTreeModel::func(type1 arg1, type2 arg2)                           { return m_pImpl->func(arg1, arg2); }
#define DECLARE_CALL_3ARG(func, type1, arg1, type2, arg2, type3, arg4)          ConfigItemTreeModel::func(type1 arg1, type2 arg2, type3 arg3)               { return m_pImpl->func(arg1, arg2, arg3); }

QVariant ConfigItemTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    return QVariant("Config name");
}

QModelIndex ConfigItemTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    return m_pImpl->findIndex(row, column, parent);
}

QModelIndex ConfigItemTreeModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int ConfigItemTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int ConfigItemTreeModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ConfigItemTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
