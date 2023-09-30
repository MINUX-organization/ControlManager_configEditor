#include "treemodelhandler.h"

#include <QDebug>

using namespace ConfigItemModel;

struct TreeModelHandler::Impl
{
    TreeItem head;

    ~Impl()
    {
        clearRecursive(&head);
    }

    void clearRecursive(TreeItem * parent)
    {
        for (TreeItem * pItem : parent->childrenVect)
        {
            clearRecursive(pItem);
        }
        if (parent != &head)
        {
            delete parent;
        }
    }

    TreeItem * findItem(const QModelIndex & index, TreeItem * parent)
    {
        if (parent->index.internalId() == index.internalId())
        {
            qDebug() << "Found item, its data: " << parent->data;
            return parent;
        }

        const int childrenVectSize = parent->childrenVect.size();
        TreeItem * pChild;
        for (uint8_t i = 0; i < childrenVectSize; i++)
        {
            pChild = parent->childrenVect[i];
            pChild = findItem(index, pChild);
            if (pChild != nullptr)
            {
                return pChild;
            }
        }
        return nullptr;
    }
};

TreeModelHandler::TreeModelHandler(const QModelIndex & headIndex) :
    m_pImpl { new Impl }
{
    m_pImpl->head.index = headIndex;
}

TreeModelHandler::~TreeModelHandler()
{

}

TreeItem *TreeModelHandler::findItem(const QModelIndex & index)
{
    return m_pImpl->findItem(index, &m_pImpl->head);
}

TreeItem & TreeModelHandler::getHead()
{
    return m_pImpl->head;
}

QModelIndex TreeModelHandler::getHeadIndex()
{
    return m_pImpl->head.index;
}
