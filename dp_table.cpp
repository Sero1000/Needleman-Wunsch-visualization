#include "dp_table.h"

#include "alignment.h"

DP_Table::DP_Table(QObject *parent)
    : QAbstractTableModel(parent), s1_('-'), s2_('-'), dp_table_(QVector<QVector<int>>(s1_.size(),QVector<int>(s2_.size())))
{

}

DP_Table::DP_Table(const QString& s1, const QString& s2, QObject* parent) : QAbstractTableModel(parent), s1_('-' + s1), s2_('-' + s2), dp_table_(QVector<QVector<int>>(s1_.size(),QVector<int>(s2_.size())))
{
    for(int row = 0;row < dp_table_.size();++row){
        for(int column = 0;column < dp_table_[row].size();++column)
        {
            dp_table_[row][column] = std::numeric_limits<int>::min();
        }
    }

    dp_table_[0][0] = 0;
}

QVariant DP_Table::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role){
        if(section > s1_.size() || section > s2_.size()){
            return QVariant();
        }
        case Qt::DisplayRole:{
            switch (orientation) {
                case Qt::Horizontal:{
                    return s2_[section];
                }
                case Qt::Vertical:{
                    return s1_[section];
                }
            }
        }

        default:
            return QVariant();
    }
}

int DP_Table::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return s1_.size();
    else
        return 0;
}

int DP_Table::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return s2_.size();
    else
        return 0;
}

QVariant DP_Table::data(const QModelIndex &index, int role) const
{
    switch(role){
        case Qt::DisplayRole:{
            if (index.isValid()){
                if(dp_table_[index.row()][index.column()] == std::numeric_limits<int>::min()){
                    return QVariant();
                }
                    return dp_table_[index.row()][index.column()];
            }
        case Qt::TextAlignmentRole: return Qt::AlignCenter;
        default:
            return QVariant();
        }
    }
}
void DP_Table::setEntry(int row, int column, int entry)
{
    dp_table_[row][column] = entry;

    emit dataChanged(index(row,column),index(row,column),QVector<int>{Qt::DisplayRole});
}

int DP_Table::getEntry(int row, int column)
{
    if(row < 0 || column < 0){
        return std::numeric_limits<int>::min();
    }

    return dp_table_[row][column];
}

QChar DP_Table::getFirstSeqEntry(int index){
    return s1_[index];
}

QChar DP_Table::getSecondSeqEntry(int index) {
    return s2_[index];
}

bool DP_Table::setData(const QModelIndex& index,const QVariant& value, int role) {
    switch(role){
    case Qt::DisplayRole:{
        dp_table_[index.row()][index.column()] = value.toInt();
    }
    }
}

QItemSelection DP_Table::getTraceBackSelection(const Alignment& alignment) const {
    QString st1 = alignment.st2();

    QString st2 = alignment.st1();

    int currentRow = rowCount() - 1;
    int currentColumn = columnCount() - 1;

    QItemSelection tracebackSelection(createIndex(currentRow,currentColumn), createIndex(currentRow, currentColumn));

    for(int i = 0 ;i < st2.size(); ++i){
        QChar el1 = st1[i];

        QChar el2 = st2[i];

        if(el1 == '-'){
            QModelIndex index = createIndex(currentRow-1,currentColumn);

            tracebackSelection.merge(QItemSelection(index,index), QItemSelectionModel::Select);

            --currentRow;
        }

        else if(el2 == '-'){
            QModelIndex index = createIndex(currentRow, currentColumn - 1);

            tracebackSelection.merge(QItemSelection(index,index), QItemSelectionModel::Select);

            --currentColumn;
        }

        else{
            QModelIndex index = createIndex(currentRow - 1,currentColumn - 1);

            tracebackSelection.merge(QItemSelection(index,index), QItemSelectionModel::Select);

            --currentRow;
            --currentColumn;
        }
    }

    return tracebackSelection;
}
