# Projet LRU - Squelette libre

# Compilation et exécution

g++ -std=c++20 -Wall -Wextra -O2 LRUCache.cpp main.cpp Parser.cpp LFUCache.cpp FIFO.cpp -o program.exe && program.exe [capacité] [fichier] (optionnel)[méthode]

##Remarque

Remarque sur le LFU : l’implémentation LFUCache n’est pas un LFU « classique » (compteur d’accès brut). Elle évince l’élément dont le taux d’utilisation est le plus faible, c’est-à-dire nombre d'accès / (temps actuel − temps d'arrivée dans le cache).
