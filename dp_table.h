#ifndef DP_TABLE_H
#define DP_TABLE_H

#include <QAbstractTableModel>

#include <QItemSelection>
class Alignment;

class DP_Table : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DP_Table(QObject *parent = nullptr);
    explicit DP_Table(const QString& s1, const QString& s2, QObject* parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex& index,const QVariant& value, int role = Qt::EditRole) override;

    void setSequnceOne(const QString& seq);

    void setSequnceTwo(const QString& seq);

    void setSequences(const QString& seq1, const QString& seq2);

    QItemSelection getTraceBackSelection(const Alignment& alignment) const;
public:

    int getEntry(int row, int column);

    void setEntry(int row, int column, int entry);

    QChar getFirstSeqEntry(int row);

    QChar getSecondSeqEntry(int column);

private:
    QString s1_;
    QString s2_;

    QVector<QVector<int>> dp_table_;
};

#endif // DP_TABLE_H
