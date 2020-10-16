#ifndef BIDE_INTSEQUENCE_H
#define BIDE_INTSEQUENCE_H

#include <vector>
#include <ostream>

/**
 * 映射为int的sequence
 */
class IntSequence {

public:
    friend std::ostream &operator<<(std::ostream &os, const IntSequence &intSequence);

    bool empty() const;

    void erase(const int &index);

    const std::vector<int> &getVector() const;

    bool isSubSequenceOf(const IntSequence &sequence) const;

    void pushBackItem(const int &item);

    int size() const;

private:
    /**
     * int表示的sequence
     */
    std::vector<int> sequence;

};

#endif // BIDE_INTSEQUENCE_H
