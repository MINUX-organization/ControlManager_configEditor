#include "treemodelhandler.h"

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
        for (auto pItem : parent->childrenVect)
        {
            clearRecursive(pItem);
        }
        delete parent;
    }

    TreeItem * findItem(const QModelIndex & index, TreeItem * parent)
    {
        if (parent->index.internalId() == index.internalId())
        {
            return parent;
        }

        const int childrenVectSize = parent->childrenVect.size();
        TreeItem * pChild;
        for (uint8_t i = 0; i < childrenVectSize; i++)
        {
            pChild = parent->childrenVect[i];
            if ((i + 1) < childrenVectSize) // Check if it's last item
            {
                if (pChild->index.internalId() > index.internalId())
                {
                    findItem(index, pChild - 1);
                }
            }
            else
            {
                findItem(index, pChild);
            }
        }

        return nullptr;
    }
};

TreeModelHandler::TreeModelHandler() :
    m_pImpl { new Impl }
{

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
