#include "Utility.h"

/**
 * 将IntSequence的[begin,end)位置的元素加入到map中
 */
void Utility::addIntSequenceBeginEndToMap(const IntSequence &intSequence, const int &sequenceId, const int &begin,
                                          const int &end, std::unordered_map<int, std::unordered_set<int> > &map) {
    if (begin >= end) {
        return;
    }
    const std::vector<int> &vector = intSequence.getVector();
    for (int i = begin; i < intSequence.size() && i < end; ++i) {
        if (map.find(vector[i]) == map.end()) {
            map[vector[i]] = std::unordered_set<int>();
            map[vector[i]].insert(sequenceId);
        } else {
            map[vector[i]].insert(sequenceId);
        }
    }
}

/**
 * 将IntSequence的[begin,end)位置的元素加入到set中
 */
void Utility::addIntSequenceBeginEndToSet(const IntSequence &intSequence, const int &begin, const int &end,
                                          std::unordered_set<int> &set) {
    if (begin >= end) {
        return;
    }
    const std::vector<int> &vector = intSequence.getVector();
    for (int i = begin; i < intSequence.size() && i < end; ++i) {
        set.insert(vector[i]);
    }
}

/**
 * 将IntSequence的[begin,end)位置的元素与set中已有的元素做交集
 */
void Utility::intersectIntSequenceBeginEndToSet(const IntSequence &intSequence, const int &begin, const int &end,
                                                std::unordered_set<int> &set1) {
    if (begin >= end) {
        set1.erase(set1.begin(), set1.end());
        return;
    }
    const std::vector<int> &vector = intSequence.getVector();
    std::set<int> set2;
    for (int i = begin; i < intSequence.size() && i < end; ++i) {
        set2.insert(vector[i]);
    }
    size_t size = set2.size() < set1.size() ? set2.size() : set1.size();
    std::vector<int> vector2(size);
    std::set<int> set(set1.begin(), set1.end());

    auto iterator = set_intersection(set.begin(), set.end(), set2.begin(), set2.end(),
                                     vector2.begin());
    set1.clear();
    if (iterator == vector2.begin()) {
        return;
    }
    set1.insert(vector2.begin(), iterator);
}