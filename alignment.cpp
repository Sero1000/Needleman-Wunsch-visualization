#include "alignment.h"
#include "scoringfunction.h"

Alignment::Alignment(){

}

Alignment::Alignment(const QString& st1, const QString& st2) : st1_(st1), st2_(st2), score_(0){
    int score = 0;
    for(int i = 0; i < st1_.size(); ++i){
        score += ScoringFunction::instance()->score(st1_[i],st2_[i]);
    }

    score_ = score;
}

Alignment::Alignment(const Alignment& other) : st1_(other.st1_), st2_(other.st2_), score_(other.score_){

}

void Alignment::addSymbols(const QChar& ch1, const QChar& ch2){
    st1_.append(ch1);
    st2_.append(ch2);

    score_ += ScoringFunction::instance()->score(ch1,ch2);
}

int Alignment::score() const{
    return score_;
}

QString Alignment::st1() const {
    return st1_;
}

QString Alignment::st2() const {
    return st2_;
}
