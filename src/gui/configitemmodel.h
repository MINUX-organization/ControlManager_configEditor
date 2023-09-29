#ifndef CONFIGITEMMODEL_H
#define CONFIGITEMMODEL_H

#include <QAbstractItemModel>
#include <memory>

class ConfigItemModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit ConfigItemModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Sets head data and parses in case of it
    void setConfigType(const QString & data);

    // Parses data from config file
    void update();

private:
    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

#endif // CONFIGITEMMODEL_H
