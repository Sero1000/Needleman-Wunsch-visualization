#ifndef DP_VISUALISER_H
#define DP_VISUALISER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class DP_Visualiser; }
QT_END_NAMESPACE

class Controller;
class QListView;
class QTextEdit;
class QSpinBox;
class DP_Table;
class QLineEdit;
class Alignment;
class QTableView;

class DP_Visualiser : public QMainWindow
{
    Q_OBJECT

public:
    DP_Visualiser(QWidget *parent = nullptr);
    ~DP_Visualiser();

public slots:
    void start();

    void log(const QString& text);
private:
    void onAlignmentSelected(const QModelIndex& current, const QModelIndex& prev);

    void setupInputWidget();

    void highlightTraceback(const Alignment& alignment);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    Ui::DP_Visualiser *ui;

    QListView* alignmentView_;

    Controller* controller_;

    QTextEdit* textEdit_;

    QSpinBox* gapScoreSpinBox_;

    QSpinBox* matchScoreSpinBox_;

    QSpinBox* mismatchScoreSpinBox_;

    DP_Table* tableModel_;

    QLineEdit* seqOneEdit_;

    QLineEdit* seqTwoEdit_;

    QTableView* tableView_;
};
#endif // DP_VISUALISER_H
