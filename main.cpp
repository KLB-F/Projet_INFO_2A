#include <iostream>
#include <string>
#include <vector>

#include "LRUCache.hpp"
#include "Parser.hpp"

using namespace std;

/*int main(int argc, char* argv[])
{
    if (argc < 3) {
        std::cout << "Usage: " << argv[0]
                  << " <capacity> <access_file>\n";
        return 0;
    }

    const int capacity = std::stoi(argv[1]);
    const std::string filename = argv[2];

    std::vector<int> accesses;

    try {
        accesses = parseAccessSequence(filename);
    }
    catch (const std::exception& e) {
        std::cerr << "Parser error: " << e.what() << '\n';
        return 1;
    }

    LRUCache cache(capacity);

    int hits = 0;
    int misses = 0;

    for (int key : accesses) {

        std::cout << "\nAccess to block " << key << '\n';

        
         * TODO
         *
         * - if key is already in the cache:
         *      count a hit;
         *      access it using get(key);
         *
         * - otherwise:
         *      count a miss;
         *      simulate loading using put(key, value).
         *
         * The value can simply be:
         *
         *      double value = static_cast<double>(key);
         

        cache.printCache();
    }

    std::cout << "\n--- Results ---\n";
    std::cout << "Hits   : " << hits << '\n';
    std::cout << "Misses : " << misses << '\n';

    if (!accesses.empty()) {
        double hitRate =
            static_cast<double>(hits) / accesses.size();

        std::cout << "Hit rate: " << hitRate << '\n';
    }

    return 0;
}*/

int main(){

    LRUCache* cache = new LRUCache(1);

    Node noeud = {1, 0, nullptr, nullptr};

    delete cache;

}