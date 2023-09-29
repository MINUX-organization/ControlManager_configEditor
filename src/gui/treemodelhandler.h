#ifndef TREEMODELHANDLER_H
#define TREEMODELHANDLER_H

#include <QModelIndex>
#include <memory>

namespace ConfigItemModel
{

struct TreeItem
{
    QVariant data;
    TreeItem * parent {nullptr};
    QVector<TreeItem *> childrenVect;
    QModelIndex index;
};

class TreeModelHandler
{
public:
    TreeModelHandler();
    ~TreeModelHandler();

    TreeItem * findItem(const QModelIndex & index);

    TreeItem & getHead();
    QModelIndex getHeadIndex();
private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

}

#endif // TREEMODELHANDLER_H
