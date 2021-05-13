#include "alignmentmodel.h"

AlignmentModel::AlignmentModel(const QList<Alignment>& alignments, QObject* parent): QAbstractItemModel(parent), alignments_(alignments){

}

AlignmentModel::AlignmentModel(QObject* parent) : QAbstractItemModel(parent){

}

int AlignmentModel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid())
        return 0;
    return alignments_.size();
}

int AlignmentModel::columnCount(const QModelIndex &parent) const {
    return 1;
}

QVariant AlignmentModel::data(const QModelIndex &index, int role ) const {
    if(!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:{
        return QString("Alignment %1").arg(index.row());
    }
    }

    return QVariant();
}

void AlignmentModel::addAlignment(const Alignment& alignment){
    alignments_.append(alignment);

    emit dataChanged(index(rowCount()-1,0),index(rowCount()-1,0), QVector<int>{Qt::DisplayRole});
}

QModelIndex AlignmentModel::index(int row,int column, const QModelIndex& parent) const{
    if(!parent.isValid()){
        return createIndex(row,column,(void*)&alignments_[row]);
    }

    return QModelIndex();
}

QModelIndex AlignmentModel::parent(const QModelIndex& index) const {
    if(index.isValid()){
        return QModelIndex();
    }

    return index.parent();
}
