#include "BIDE.h"

size_t hashCode(const Sequence &sequence) {
    size_t h = 17;
    for (const auto &str : sequence.sequence) {
        for (const auto &c : str) {
            h = 37 * h + c;
        }
    }
    return h;
}

BIDE::BIDE(Database &database)
        : database(database), frequentOneItemsCount(database.frequentOneCount()), maxLength(database.getMaxLength()),
          minSupport(database.getMinSupport()), result(10, hashCode) {
}

/**
 * 从currentSequence开始深度优先搜索
 */
void BIDE::dfs(IntSequence &currentSequence, const std::unordered_set<int> &supports) {
    if (currentSequence.size() == maxLength) {
        if (!database.bideCloseCheck(currentSequence, supports)) {
            return;
        }
        result[database.stringSequence(currentSequence)] = supports.size();
        return;
    }
    std::unordered_map<int, std::unordered_set<int> > map1 = database.nextInsertItems(currentSequence, supports);
    for (auto &item : map1) {
        currentSequence.pushBackItem(item.first);
        if (database.isBackPatching(currentSequence, item.second)) {
            currentSequence.erase(currentSequence.size() - 1);
            continue;
        }
        dfs(currentSequence, item.second);
        currentSequence.erase(currentSequence.size() - 1);
    }
    if (!database.bideCloseCheck(currentSequence, supports)) {
        return;
    }
    result[database.stringSequence(currentSequence)] = supports.size();
}

std::unordered_map<Sequence, size_t, size_t (*)(const Sequence &)> &BIDE::run() {
    for (int i = 0; i < database.frequentOneCount(); ++i) {
        currentSequence.pushBackItem(i);
        std::unordered_set<int> supports = database.intSequenceSupport(currentSequence);
        if (database.isBackPatching(currentSequence, supports)) {
            currentSequence.erase(0);
            continue;
        }
        dfs(currentSequence, supports);
        currentSequence.erase(0);
    }
    return this->result;
}
