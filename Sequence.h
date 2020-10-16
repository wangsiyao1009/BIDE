#ifndef BIDE_SEQUENCE_H
#define BIDE_SEQUENCE_H

#include <string>
#include <list>
#include <ostream>
#include <vector>

/**
 * string表示的sequence
 */
class Sequence {

public:

    friend std::ostream &operator<<(std::ostream &os, const Sequence &sequence);

    friend size_t hashCode(const Sequence &sequence);

    std::vector<std::string> &getVector();

    bool operator==(const Sequence &rhs) const;

    void pushBackItem(const std::string &item);

    int size() const;

    /**
     * string表示的sequence
     */
    std::vector<std::string> sequence;

};

#endif // BIDE_SEQUENCE_H
