#include "scoringfunction.h"

ScoringFunction ScoringFunction::instance_;

ScoringFunction::ScoringFunction() : gapScore_(-2), matchScore_(1) , mismatchScore_(-1)
{

}

void ScoringFunction::setGapScore(int gapScore){
    gapScore_ = gapScore;
}

void ScoringFunction::setMatchScore(int matchScore){
    matchScore_ = matchScore;
}

void  ScoringFunction::setMisMatchScore(int mismatchScore){
    mismatchScore_ = mismatchScore;
}

int ScoringFunction::score(const QChar& first, const QChar& second) const{
    if(first == '-' || second == '-'){
        return gapScore_;
    }
    else if(first == second){
        return matchScore_;
    }
    else{
        return mismatchScore_;
    }
}

ScoringFunction* ScoringFunction::instance(){
    return &instance_;
}
