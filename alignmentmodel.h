#ifndef ALIGNMENTMODEL_H
#define ALIGNMENTMODEL_H

#include <QAbstractListModel>
#include "alignment.h"

class AlignmentModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    AlignmentModel(QObject* parent = nullptr);

    AlignmentModel(const QList<Alignment>& aligbments,QObject* parent = nullptr);

public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row,int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
public:
    void addAlignment(const Alignment& alignment);
private:
    QList<Alignment> alignments_;
};

#endif // ALIGNMENTMODEL_H
