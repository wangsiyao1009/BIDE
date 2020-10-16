#include "IntSequence.h"

bool IntSequence::empty() const {
    return sequence.empty();
}

/**
 * 删除index位置的元素
 */
void IntSequence::erase(const int &index) {
    this->sequence.erase(this->sequence.begin() + index);
}

/**
 * 获得vector
 */
const std::vector<int> &IntSequence::getVector() const {
    return sequence;
}

/**
 * 判断当前sequence是否是参数sequence的子序列
 */
bool IntSequence::isSubSequenceOf(const IntSequence &sequence) const {
    int start = 0;
    for (int item : this->sequence) {
        int j;
        for (j = start; j < sequence.size(); ++j) {
            if (item == sequence.sequence[j]) {
                start = j + 1;
                break;
            }
        }
        if (j == sequence.size()) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const IntSequence &intSequence) {
    for (int i : intSequence.sequence)
        os << i << " ";
    return os;
}

/**
 * sequence末尾加入一个item
 */
void IntSequence::pushBackItem(const int &item) {
    this->sequence.push_back(item);
}

/**
 * 获取sequence的大小
 */
int IntSequence::size() const {
    return sequence.size();
}