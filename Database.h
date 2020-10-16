#ifndef BIDE_DATABASE_H
#define BIDE_DATABASE_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <map>
#include "Sequence.h"
#include "IntSequence.h"
#include "Utility.h"

/**
 * 读取数据集，获取频繁1项，给定序列得到支持度，闭合判断，削减判断
 */
class Database {

public:

    explicit Database(const double &supportRatio);

    bool bideCloseCheck(const IntSequence &intSequence, const std::unordered_set<int> &supports);

    size_t frequentOneCount();

    int getMaxLength() const;

    int getMinSupport() const;

    void initDataSet(const std::string &filename);

    std::unordered_set<int> intSequenceSupport(const IntSequence &intSequence);

    bool isBackPatching(const IntSequence &intSequence, const std::unordered_set<int> &supports);

    std::unordered_map<int, std::unordered_set<int> >
    nextInsertItems(const IntSequence &intSequence, const std::unordered_set<int> &supports);

    Sequence stringSequence(IntSequence &sequence);

private:
    /**
     * 频繁1项及其支持度
     */
    std::unordered_map<std::string, int> frequentItemsAndSupport{};
    /**
     * 将输入的数据集转换为intSequence后的结果
     */
    std::vector<IntSequence> intSequences{};
    /**
     * 去掉非频繁项后序列的最大长度
     */
    int maxLength;
    /**
     * 最小支持度
     */
    int minSupport;
    /**
     * 输出结果时，把intSequence变回Sequence
     */
    std::vector<std::string> printMap{};
    /**
     * 支持率
     */
    const double supportRatio;

    bool bideBackwardCloseCheck(const IntSequence &intSequence, const std::unordered_set<int> &supports);

    bool bideForwardCloseCheck(const IntSequence &intSequence, const std::unordered_set<int> &supports);

    std::vector<IntSequence> convertSequenceToInt(std::vector<Sequence> &sequences);

    std::unordered_map<std::string, int> countOneFrequent(std::vector<Sequence> &sequences) const;

    static std::vector<Sequence> readFile(const std::string &filename);

    void removeNotFrequent(std::vector<Sequence> &sequences);

    int seekFirstInstance(const IntSequence &intSequence, const int &index, const IntSequence &intSequence1);

    int seekLastInLast(const IntSequence &intSequence, const int &index, const IntSequence &intSequence1);

    int seekLastInFirst(const IntSequence &intSequence, const int &index, const IntSequence &intSequence1);
};

#endif // BIDE_DATABASE_H
