#ifndef BIDE_BIDE_H
#define BIDE_BIDE_H

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include "Database.h"
#include "IntSequence.h"

class BIDE {

public:
    explicit BIDE(Database &database);

    std::unordered_map<Sequence, size_t, size_t (*)(const Sequence &)> &run();

private:
    /**
     * 当前遍历序列
     */
    IntSequence currentSequence;
    /**
     * 使用该类所提供的功能求序列的支持度等
     */
    Database &database;
    /**
     * 频繁1项个数
     */
    const size_t frequentOneItemsCount;
    /**
     * 如果当前序列到达该长度则返回
     */
    const int maxLength;
    /**
     * 最小支持度
     */
    const int minSupport;
    /**
     * 闭序列结果
     */
    std::unordered_map<Sequence, size_t, size_t (*)(const Sequence &)> result;

    void dfs(IntSequence &currentSequence, const std::unordered_set<int> &supports);

};

#endif // BIDE_BIDE_H
