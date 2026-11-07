#include <iostream>
#include <string>
#include <vector>

#include "LRUCache.hpp"
#include "FIFO.hpp"
#include "LFUCache.hpp"
#include "Parser.hpp"

using namespace std;

int main(int argc, char* argv[])
{

    bool utiliseFIFO = false;
    bool utiliseLFU = false;

    if (argc < 3) {
        std::cout << "Usage: " << argv[0]
                  << " <capacity> <access_file>\n";
        return 0;
    }

    if(argc > 3){ //Choix du type de cache
        if(std::string(argv[3]) =="FIFO"){ utiliseFIFO = true; }
        else if(std::string(argv[3]) =="LFU"){ utiliseLFU = true; }
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
    FIFO cacheFIFO(capacity);
    LFUCache cacheLFU(capacity);

    int hits = 0;
    int misses = 0;

    for (int key : accesses) {

        std::cout << "\nAccess to block " << key << '\n';

        double value = static_cast<double>(key);


        if(utiliseFIFO){

            if(cacheFIFO.contains(key)){
                hits++;
                cacheFIFO.get(key);
                
            }else{
                misses++;
                cacheFIFO.put(key, value);
            }

            cacheFIFO.printCache();
           

        }else if(utiliseLFU){
        
            if(cacheLFU.contains(key)){
                hits++;
                cacheLFU.get(key);
                
            }else{
                misses++;
                cacheLFU.put(key, value);
            }

            cacheLFU.printCache();

        }else{

             if(cache.contains(key)){
                hits++;
                cache.get(key);
            }else{
                misses++;
                cache.put(key, value);
            }

            cache.printCache();

        }

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
}