#ifndef SCORINGFUNCTION_H
#define SCORINGFUNCTION_H

#include <QChar>

class ScoringFunction
{
public:
    ScoringFunction(const ScoringFunction& other) = delete;
    ScoringFunction(ScoringFunction&& other) = delete;

    ScoringFunction& operator=(const ScoringFunction& other) = delete;
    ScoringFunction& operator=(ScoringFunction&& other) = delete;

    static ScoringFunction* instance();

    int score(const QChar& first, const QChar& second) const;

    void setGapScore(int gapScore);

    void setMatchScore(int matchScore);

    void  setMisMatchScore(int mismatchScore);
protected:
    ScoringFunction();
private:
    static ScoringFunction instance_;

    int gapScore_;

    int matchScore_;

    int mismatchScore_;
};

#endif // SCORINGFUNCTION_H
