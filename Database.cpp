#include "Database.h"

bool compareString(const std::string &string1, const std::string &string2) {
    char *ptr;
    long i1 = strtol(string1.c_str(), &ptr, 10);
    long i2 = strtol(string2.c_str(), &ptr, 10);
    return i1 < i2;
}

/**
 * 数据支持率
 */
Database::Database(const double &supportRatio) : supportRatio(supportRatio), maxLength(), minSupport() {
}

/**
 * bide后向闭合判断
 */
bool Database::bideBackwardCloseCheck(const IntSequence &intSequence, const std::unordered_set<int> &supports) {
    if (intSequence.empty() || supports.empty()) {
        return true;
    }
    const std::vector<int> &vector1 = intSequence.getVector();
    for (int i = 0; i < vector1.size(); ++i) {
        std::unordered_set<int> set1;
        for (int support : supports) {
            int begin = seekFirstInstance(intSequence, i - 1, intSequences[support]);
            int end = seekLastInLast(intSequence, i, intSequences[support]);
            if (set1.empty()) {
                Utility::addIntSequenceBeginEndToSet(intSequences[support], begin + 1, end, set1);
            } else {
                Utility::intersectIntSequenceBeginEndToSet(intSequences[support], begin + 1, end, set1);
            }
            if (set1.empty()) {
                break;
            }
        }
        if (!set1.empty()) {
            return false;
        }
    }
    return true;
}

/**
 * bide闭合判断，返回true表示闭合
 */
bool Database::bideCloseCheck(const IntSequence &intSequence, const std::unordered_set<int> &supports) {
    return intSequence.empty() || supports.empty() ||
           (bideForwardCloseCheck(intSequence, supports) && bideBackwardCloseCheck(intSequence, supports));
}

/**
 * bide前向闭合判断
 */
bool Database::bideForwardCloseCheck(const IntSequence &intSequence, const std::unordered_set<int> &supports) {
    if (intSequence.empty() || supports.empty()) {
        return true;
    }
    std::unordered_set<int> set1;
    for (int support : supports) {
        int begin = Database::seekFirstInstance(intSequence, intSequence.size() - 1, intSequences[support]);
        int end = intSequences[support].size();
        if (set1.empty()) {
            Utility::addIntSequenceBeginEndToSet(intSequences[support], begin + 1, end, set1);
        } else {
            Utility::intersectIntSequenceBeginEndToSet(intSequences[support], begin + 1, end, set1);
        }
        if (set1.empty()) {
            return true;
        }
    }
    return false;
}

/**
 * 将Sequence转化为IntSequence
 */
std::vector<IntSequence> Database::convertSequenceToInt(std::vector<Sequence> &sequences) {
    std::unordered_map<std::string, int> map1;
    std::vector<IntSequence> vector1;
    for (auto &item : frequentItemsAndSupport) {
        printMap.push_back(item.first);
    }
    std::sort(printMap.begin(), printMap.end(), compareString);
    for (int i = 0; i < printMap.size(); ++i) {
        map1[printMap[i]] = i;
    }
    for (auto &sequence : sequences) {
        IntSequence intSequence;
        std::vector<std::string> &vector2 = sequence.getVector();
        for (const auto &item : vector2) {
            intSequence.pushBackItem(map1[item]);
        }
        vector1.push_back(intSequence);
    }
    return vector1;
}

/**
 * 获得频繁1项
 */
std::unordered_map<std::string, int> Database::countOneFrequent(std::vector<Sequence> &sequences) const {
    std::unordered_map<std::string, std::unordered_set<int> > map1;
    int i = 0;
    for (auto &sequence : sequences) {
        std::vector<std::string> &sequence1 = sequence.getVector();
        for (auto &item : sequence1) {
            if (map1.find(item) == map1.end()) {
                map1[item] = std::unordered_set<int>();
                map1[item].insert(i);
            } else {
                map1[item].insert(i);
            }
        }
        ++i;
    }
    std::unordered_map<std::string, int> map2;
    auto begin = map1.begin();
    while (begin != map1.end()) {
        if (begin->second.size() >= minSupport) {
            map2[begin->first] = begin->second.size();
            ++begin;
        } else {
            ++begin;
        }
    }
    return map2;
}

/**
 * 频繁1项个数
 */
size_t Database::frequentOneCount() {
    return frequentItemsAndSupport.size();
}

/**
 * 去掉非频繁项后的序列最大长度
 */
int Database::getMaxLength() const {
    return maxLength;
}

/**
 * 最小支持度
 */
int Database::getMinSupport() const {
    return minSupport;
}

void Database::initDataSet(const std::string &filename) {
    std::vector<Sequence> vector1 = readFile(filename);
    minSupport = static_cast<int>(ceil(vector1.size() * supportRatio));
    frequentItemsAndSupport = this->countOneFrequent(vector1);
    this->removeNotFrequent(vector1);
    intSequences = this->convertSequenceToInt(vector1);
}

/**
 * 输入序列获得支持度序列
 */
std::unordered_set<int> Database::intSequenceSupport(const IntSequence &intSequence) {
    std::unordered_set<int> set1;
    int i = 0;
    for (auto &sequence : intSequences) {
        if (intSequence.isSubSequenceOf(sequence)) {
            set1.insert(i);
        }
        ++i;
    }
    return set1;
}

/**
 * 某个序列能100%回插一个item，则该序列被削减
 */
bool Database::isBackPatching(const IntSequence &intSequence, const std::unordered_set<int> &supports) {
    if (intSequence.empty() || supports.empty()) {
        return true;
    }
    const std::vector<int> &vector1 = intSequence.getVector();
    for (int i = 0; i < vector1.size(); ++i) {
        std::unordered_set<int> set1;
        for (int support : supports) {
            int begin = seekFirstInstance(intSequence, i - 1, intSequences[support]);
            int end = seekLastInFirst(intSequence, i, intSequences[support]);
            if (set1.empty()) {
                Utility::addIntSequenceBeginEndToSet(intSequences[support], begin + 1, end, set1);
            } else {
                Utility::intersectIntSequenceBeginEndToSet(intSequences[support], begin + 1, end, set1);
            }
            if (set1.empty()) {
                break;
            }
        }
        if (!set1.empty()) {
            return true;
        }
    }
    return false;
}

/**
 * 当前序列右侧能插入哪些item，使得插入后的支持度不小于minSupport
 */
std::unordered_map<int, std::unordered_set<int> >
Database::nextInsertItems(const IntSequence &intSequence, const std::unordered_set<int> &supports) {
    std::unordered_map<int, std::unordered_set<int> > map1;
    for (int support : supports) {
        int begin = seekFirstInstance(intSequence, intSequence.size() - 1, intSequences[support]);
        int end = seekLastInLast(intSequence, intSequence.size(), intSequences[support]);
        Utility::addIntSequenceBeginEndToMap(intSequences[support], support, begin + 1, end, map1);
    }
    auto begin = map1.begin();
    std::unordered_map<int, std::unordered_set<int> > map2;
    while (begin != map1.end()) {
        if (begin->second.size() < minSupport) {
            begin++;
        } else {
            map2[begin->first] = begin->second;
            begin++;
        }
    }
    return map2;
}

/**
 * 读取以-1和-2分割的文件。返回vector表示
 */
std::vector<Sequence> Database::readFile(const std::string &filename) {
    std::ifstream infile(filename.c_str());
    std::vector<Sequence> vector1;
    std::string line;

    while (getline(infile, line) && !line.empty()) {
        std::istringstream inString(line);
        std::string item;
        Sequence sequence;
        while (inString >> item) {
            if (item != "-1" && item != "-2") {
                sequence.pushBackItem(item);
            }
        }
        vector1.push_back(sequence);
    }
    return vector1;
}

/**
 * 移除非频繁项
 */
void Database::removeNotFrequent(std::vector<Sequence> &sequences) {
    maxLength = 0;
    for (auto &sequence : sequences) {
        std::vector<std::string> &vector1 = sequence.getVector();
        auto begin = vector1.begin();
        while (begin != vector1.end()) {
            if (frequentItemsAndSupport.find(*begin) == frequentItemsAndSupport.end()) {
                begin = vector1.erase(begin);
            } else {
                ++begin;
            }
        }
        if (maxLength < sequence.size()) {
            maxLength = sequence.size();
        }
    }
}

/**
 * 寻找intSequence中index位置的元素第一次在intSequence1中出现的位置
 */
int Database::seekFirstInstance(const IntSequence &intSequence, const int &index, const IntSequence &intSequence1) {
    if (index < 0 || index >= intSequence.size()) {
        return -1;
    }
    int start = 0;
    for (int i = 0; i <= index; ++i) {
        int j;
        for (j = start; j < intSequence1.size(); ++j) {
            if (intSequence1.getVector()[j] == intSequence.getVector()[i]) {
                start = j + 1;
                break;
            }
        }
        if (j == intSequence1.size()) {
            return -1;
        }
    }
    return start - 1;
}

/**
 * 寻找intSequence中index位置的元素最后在intSequence1中出现的位置
 */
int Database::seekLastInLast(const IntSequence &intSequence, const int &index, const IntSequence &intSequence1) {
    if (index < 0) {
        return -1;
    }
    if (index >= intSequence.size()) {
        return intSequence1.size();
    }
    int start = intSequence1.size() - 1;
    for (int i = intSequence.size() - 1; i >= index; --i) {
        int j;
        for (j = start; j > -1; --j) {
            if (intSequence1.getVector()[j] == intSequence.getVector()[i]) {
                start = j - 1;
                break;
            }
        }
        if (j == -1) {
            return -1;
        }
    }
    return start + 1;
}

/**
 * intSequence转sequence
 */
Sequence Database::stringSequence(IntSequence &sequence) {
    Sequence sequence1;
    const std::vector<int> &vector1 = sequence.getVector();
    for (int item : vector1) {
        sequence1.pushBackItem(this->printMap[item]);
    }
    return sequence1;
}

int Database::seekLastInFirst(const IntSequence &intSequence, const int &index, const IntSequence &intSequence1) {
    if (index < 0) {
        return -1;
    }
    if (index >= intSequence.size()) {
        return intSequence1.size();
    }
    int start = seekFirstInstance(intSequence, intSequence.size() - 1, intSequence1);
    for (int i = intSequence.size() - 1; i >= index; --i) {
        int j;
        for (j = start; j > -1; --j) {
            if (intSequence1.getVector()[j] == intSequence.getVector()[i]) {
                start = j - 1;
                break;
            }
        }
        if (j == -1) {
            return -1;
        }
    }
    return start + 1;
}