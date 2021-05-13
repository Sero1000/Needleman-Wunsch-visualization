#include "controller.h"
#include "alignmentmodel.h"
#include "dp_table.h"

QString Controller::regulardCaselogTemplate = "Third Case:\nThe entry for A[%1 %2] is equal to max{%3 + gapScore ; %4 + gapScore ; %5 + scoringFunction(A[i-1,j-1])} \nWhich equals to %7";

Controller::Controller() {

}

Controller::Controller(AlignmentModel* alignmentModel) : QObject(), state_(State::first), currentRow_(0), currentColumn_(1) , alignmentModel_(alignmentModel),gapScore_(-2), mismatchScore_(-1), matchScore_(1){
    state_ = State::first;
}

void Controller::iter() {
    switch(state_){
        case State::first :     firstCase(); break;
        case State::second:     secondCase();break;
        case State::regular:    regularCase(); break;
        case State::traceback:  tracebackCase(); break;
        case State::finished:   return;
    }
}

void Controller::firstCase(){

    table_->setEntry(currentRow_, currentColumn_,gapScore_*currentColumn_);

    emit stepFinished(QString("First Part ot the algorithm. Fill the first row with the value i*GapScore."));

    ++currentColumn_;

    if(currentColumn_ == table_->columnCount()){
        currentRow_ = 1;
        currentColumn_ = 0;

        state_ = State::second;
    }
}

void Controller::secondCase(){

    table_->setEntry(currentRow_,currentColumn_,gapScore_*currentRow_);

    emit stepFinished(QString("Second Part of the algorithm. Fill the first column with the value i * GapScore."));

    ++currentRow_;

    if(currentRow_ == table_->rowCount()){
        currentColumn_ = 1;
        currentRow_ = 1;

        state_ = State::regular;
    }
}

void Controller::regularCase(){

    int upper = table_->getEntry(currentRow_ - 1,currentColumn_);
    int left = table_->getEntry(currentRow_,currentColumn_ - 1);
    int diag = table_->getEntry(currentRow_ - 1,currentColumn_ - 1);

    int max = std::max({upper + gapScore_,left + gapScore_, diag + scoringFunction(currentRow_,currentColumn_)});


    emit stepFinished(QString("Third Case:\nThe entry for A[%1 %2] is equal to max{%3 + gapScore ; %4 + gapScore ; %5 + scoringFunction(A[i-1,j-1])} \nWhich equals to %7").arg(currentRow_).arg(currentColumn_).arg(upper).arg(left).arg(diag).arg(max));
    table_->setEntry(currentRow_,currentColumn_,max);

    ++currentColumn_;
    if(currentColumn_ == table_->columnCount())
    {
        ++currentRow_;
        if(currentRow_ == table_->rowCount()) {
            state_ = State::traceback;

            currentRow_ = table_->rowCount(QModelIndex()) - 1;
            currentColumn_ = table_->columnCount(QModelIndex()) - 1;
        }
        else{
            currentColumn_ = 1;
        }
    }
}

int Controller::scoringFunction(int row,int column){
    QChar char1 = table_->getFirstSeqEntry(row);
    QChar char2 = table_->getSecondSeqEntry(column);

    if(char1 == char2)
        return matchScore_;
    else
        return mismatchScore_;
}

void Controller::tracebackCase(){
    Alignment alignment;
    tracebackHelper(currentRow_,currentColumn_, alignment);

    state_ = State::finished;
}

void Controller::tracebackHelper(int row, int column, Alignment& alignment){
    if(row == 0 && column == 0){
        alignmentModel_->addAlignment(alignment);
        return;
    }

    int upper = table_->getEntry(row - 1,column);
    int left = table_->getEntry(row,column - 1);
    int diag = table_->getEntry(row - 1, column - 1);
    int current = table_->getEntry(row,column);

    QChar firstSeqEntry = table_->getFirstSeqEntry(row);
    QChar secondSeqEntry = table_->getSecondSeqEntry(column);

    if(upper + gapScore_ == current){
        Alignment tmpAlignment(alignment);
        tmpAlignment.addSymbols(firstSeqEntry,'-');

        tracebackHelper(row - 1,column,tmpAlignment);
    }

    if(left + gapScore_ == current){
        Alignment tmpAlignment(alignment);
        tmpAlignment.addSymbols('-',secondSeqEntry);

        tracebackHelper(row,column - 1,tmpAlignment);
    }

    if(diag + scoringFunction(row,column) == current){
        Alignment tmpAlignment(alignment);
        tmpAlignment.addSymbols(firstSeqEntry,secondSeqEntry);

        tracebackHelper(row - 1,column - 1,tmpAlignment);
    }

}

void Controller::setGapScore(int newValue)
{
    gapScore_ = newValue;
}

void Controller::setMatchScore(int newValue){
    matchScore_ = newValue;
}

void Controller::setMismatchScore(int newValue){
    mismatchScore_ = newValue;
}

void Controller::setDPTable(DP_Table* table)
{
    table_ = table;
}
