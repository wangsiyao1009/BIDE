#ifndef BIDE_UTILITY_H
#define BIDE_UTILITY_H

#include <map>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include "IntSequence.h"

class Utility {
public:

    static void
    addIntSequenceBeginEndToMap(const IntSequence &intSequence, const int &sequenceId, const int &begin, const int &end,
                                std::unordered_map<int, std::unordered_set<int> > &map);

    static void addIntSequenceBeginEndToSet(const IntSequence &intSequence, const int &begin, const int &end,
                                            std::unordered_set<int> &set);

    static void intersectIntSequenceBeginEndToSet(const IntSequence &intSequence, const int &begin, const int &end,
                                                  std::unordered_set<int> &set);
};

#endif // BIDE_UTILITY_H
