#include "Sequence.h"

/**
 * 获得内部表示vector
 */
std::vector<std::string> &Sequence::getVector() {
    return sequence;
}

std::ostream &operator<<(std::ostream &os, const Sequence &sequence) {
    for (const auto &item : sequence.sequence) {
        os << item << " -1 ";
    }
    return os;
}

bool Sequence::operator==(const Sequence &rhs) const {
    return sequence == rhs.sequence;
}

/**
 * sequence末尾加入一个item
 */
void Sequence::pushBackItem(const std::string &item) {
    this->sequence.push_back(item);
}

/**
 * 获得sequence长度
 */
int Sequence::size() const {
    return sequence.size();
}