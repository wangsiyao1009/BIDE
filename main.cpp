#include <iostream>
#include <ctime>
#include <sstream>
#include "Database.h"
#include "BIDE.h"

int main(int argc, char **argv) {
    clock_t start = clock();
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " filename supportRatio" << std::endl;
        return 0;
    }
    std::string filename = argv[1];
    double supportRatio = strtod(argv[2], nullptr);

    std::stringstream stringStream;
    stringStream << "BIDE-" << filename << "-" << supportRatio << ".txt";
    freopen(stringStream.str().c_str(), "w", stdout);

    time_t time1;
    time(&time1);
    char string1[64];
    strftime(string1, sizeof(string1), "%Y-%m-%d %H:%M:%S", localtime(&time1));
    std::cout << "Start time: " << string1 << std::endl;

    std::cout << "filename: " << filename << "\n"
              << "supportRatio: " << supportRatio << "\n" << std::endl;

    clock_t clock1 = clock();
    Database database(supportRatio);
    database.initDataSet(filename);
    std::cout << "initDataTime: " << ((double) (clock() - clock1) / CLOCKS_PER_SEC) << std::endl;

    clock_t clock2 = clock();
    BIDE mining(database);
    std::unordered_map<Sequence, size_t, size_t(*)(const Sequence &)> &map1 = mining.run();
    std::cout << "miningTime: " << ((double) (clock() - clock2) / CLOCKS_PER_SEC) << std::endl;
    double end = clock();
    std::cout << "Running Time: " << ((end - start) / CLOCKS_PER_SEC) << " seconds." << std::endl;
    std::cout << "resultSize:" << map1.size() << std::endl;
    std::cout << "result:" << std::endl;

    for (const auto &item : map1) {
        std::cout << item.first << "#SUP: " << item.second << "\n";
    }
    return 0;
}
