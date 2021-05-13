#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "alignment.h"

class DP_Table;
class AlignmentModel;
class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();

    Controller(AlignmentModel* alignmentModel);

    void setDPTable(DP_Table* table);
    void iter();
signals:
    void tracebackDone(const QString& string1, const QString& string2);

    void stepFinished(const QString& text);

public slots:
    void setGapScore(int value);

    void setMatchScore(int newValue);

    void setMismatchScore(int newValue);
private:

    void firstCase();

    void secondCase();

    void regularCase();

    void tracebackCase();

    void tracebackHelper(int row, int column, Alignment& alignment);

    int scoringFunction(int row,int column);
private:
    static QString regulardCaselogTemplate;
private:
    enum class State{first, second, regular,finished,traceback};

    State state_;
    DP_Table* table_;

    AlignmentModel* alignmentModel_;

    int currentRow_;
    int currentColumn_;

    int gapScore_;

    int matchScore_;

    int mismatchScore_;
};

#endif // CONTROLLER_H
