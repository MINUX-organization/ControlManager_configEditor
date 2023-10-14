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

        if (!pItem)
        {
            return QModelIndex();
        }

        if (pItem->parent)
        {
            return pItem->parent->index;
        }

        return QModelIndex(); // m_handler.getHeadIndex();
    }

    QVariant data(const QModelIndex &index)
    {
        TreeItem * pParent = m_handler.findItem(index);

        if (pParent)
        {
            return pParent->data;
        }
        return QVariant();
    }

    void addElement(TreeItem * parent, const QString & itemData)
    {
        TreeItem * pBufferItem;

        pBufferItem = new TreeItem;
        pBufferItem->parent = parent;
        pBufferItem->index = m_mainClass->createIndex(parent->childrenVect.size(), 0, m_handler.getNextId());
        pBufferItem->data = itemData;
        parent->childrenVect.push_back( pBufferItem );
    }

    void update()
    {
        // TODO: Test data, replace correctly

        TreeItem & head = m_handler.getHead();

        addElement(&head, "Miner config");

        addElement(head.childrenVect[0], "GPUs");
        addElement(head.childrenVect[0]->childrenVect[0], "GPU 1 (AMD Radeon 580)");
        addElement(head.childrenVect[0]->childrenVect[0], "GPU 2 (NVIDIA Unknown)");

        addElement(head.childrenVect[0], "CPUs");
        addElement(head.childrenVect[0]->childrenVect[1], "CPU 1 (AMD Ryzen 5300U)");
        addElement(head.childrenVect[0]->childrenVect[1], "CPU 2 (Intel i3-240M)");

        addElement(head.childrenVect[0], "Hard drives");
        addElement(head.childrenVect[0]->childrenVect[2], "Unknown 1");
        addElement(head.childrenVect[0]->childrenVect[2], "Asus 17926-MSH");

        addElement(&head, "Commission config");

        addElement(head.childrenVect[1], "Mining configs");
        addElement(head.childrenVect[1]->childrenVect[0], "GPUs");
        addElement(head.childrenVect[1]->childrenVect[0], "CPUs");

        addElement(head.childrenVect[1], "Time configs");

        addElement(&head, "UWA config");

        addElement(head.childrenVect[2], "Connection");
        addElement(head.childrenVect[2], "Other");
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
    return m_pImpl->findIndex(row, column, parent);
}

QModelIndex ConfigItemTreeModel::parent(const QModelIndex &index) const
{
    return m_pImpl->parent(index);
}

int ConfigItemTreeModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return m_pImpl->m_handler.getHead().childrenVect.size();

    return m_pImpl->rowCount(parent);
}

int ConfigItemTreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}

QVariant ConfigItemTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    return m_pImpl->data(index);
}

void ConfigItemTreeModel::update()
{
    return m_pImpl->update();
}
