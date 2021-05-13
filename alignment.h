#ifndef ALIGNMENT_H
#define ALIGNMENT_H
#include <QString>

class Alignment{
public:
    explicit Alignment(const QString& st1, const QString& st2);
    Alignment();

    Alignment(const Alignment& other);
    Alignment& operator=(const Alignment& other);

    Alignment& operator=(Alignment&& other) = default;
    Alignment(Alignment&& other) = default;

    void addSymbols(const QChar& ch1, const QChar& ch2);

    QString st1() const;

    QString st2() const;

    int score() const;
private:
    QString st1_;

    QString st2_;

    int score_;
};

#endif // ALIGNMENT_H
