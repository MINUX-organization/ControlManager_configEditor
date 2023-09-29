#include "configitemmodel.h"

#include "configsLib/configworker.h"

#include "treemodelhandler.h"

#include <QDebug>

using namespace ConfigItemModel;

struct ConfigItemTreeModel::Impl
{
    TreeModelHandler m_handler;
    ConfigsLib::ConfigWorker m_configWorker;

    ConfigItemTreeModel * m_mainClass {nullptr};

    Impl(ConfigItemTreeModel * parent) : m_mainClass(parent), m_handler(parent->createIndex(0, 0, (quintptr)0))
    {
        if (!m_mainClass)
        {
            throw std::runtime_error("[ConfigItemTreeModel] Class init error!");
        }
    }

    QModelIndex findIndex(int row, int column, const QModelIndex & parent)
    {
        Q_UNUSED(column) // TODO: Add fields and use?

        TreeItem * pParent = m_handler.findItem(parent);

        if (pParent)
        {
            if (row < pParent->childrenVect.size())
            {
                return pParent->childrenVect[row]->index;
            }
        }
        return m_handler.getHeadIndex();
    }

    int rowCount(const QModelIndex &parent)
    {
        TreeItem * pParent = m_handler.findItem(parent);
        if (pParent)
        {
            return pParent->childrenVect.size();
        }
        return 0;
    }

    QModelIndex parent(const QModelIndex &index)
    {
        TreeItem * pItem = m_handler.findItem(index);
        if (pItem->parent)
        {
            return pItem->parent->index;
        }
        return QModelIndex();
    }

    QVariant data(const QModelIndex &index)
    {
        TreeItem *  pParent = m_handler.findItem(index);

        if (pParent)
        {
            return pParent->data;
        }
        return QVariant();
    }

    void update()
    {
        // TODO: Test data, replace correctly

        TreeItem & head = m_handler.getHead();

        head.data = "Aboba head";

        quintptr currentId = 1;

        TreeItem * pBufferItem;
        for (int i = 0; i < 10; i++)
        {
            pBufferItem = new TreeItem;

            pBufferItem->index = m_mainClass->createIndex(i, 0, currentId++);

            pBufferItem->data = QString("AbobaChildMain_[") + QString::number(i) + "]";

            head.childrenVect.push_back( pBufferItem );

            for (int j = 0; j < 3; j++)
            {
                pBufferItem = new TreeItem;

                pBufferItem->index = m_mainClass->createIndex(i, 0, currentId++);

                pBufferItem->data = QString("AbobaChildChild_[") + QString::number(i) + " - " + QString::number(j) + "]";

                head.childrenVect[i]->childrenVect.push_back( pBufferItem );
            }
        }
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

    Q_UNUSED(section)
    Q_UNUSED(orientation)

    return QVariant("Config name");
}

QModelIndex ConfigItemTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    qDebug() << "[INDEX] Called";
    return m_pImpl->findIndex(row, column, parent);
}

QModelIndex ConfigItemTreeModel::parent(const QModelIndex &index) const
{
    qDebug() << "[PARENT] Called";
    return m_pImpl->parent(index);
}

int ConfigItemTreeModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "[Row count] Called";
    if (!parent.isValid())
        return 0;

    qDebug() << "[Row count] Returning row count";
    return m_pImpl->rowCount(parent);
}

int ConfigItemTreeModel::columnCount(const QModelIndex &parent) const
{
    qDebug() << "[Column count] Called";
    if (!parent.isValid())
        return 0;

    qDebug() << "[Column count] Returning 1";
    return 1;
}

QVariant ConfigItemTreeModel::data(const QModelIndex &index, int role) const
{
    qDebug() << "[DATA] Called";
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    qDebug() << "[UPDATE] Returning data from index";
    return m_pImpl->data(index);
}

void ConfigItemTreeModel::update()
{
    qDebug() << "[UPDATE] Called";
    return m_pImpl->update();
}
