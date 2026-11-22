# Projet LRU – Cache mémoire pour système embarqué

Implémentation d'un cache **LRU** (liste doublement chaînée + `unordered_map`),
comparé à **FIFO** et à une variante de **LFU** sur des séquences d'accès.

## Compilation (C++20, pour `unordered_map::contains`)

```bash
g++ -std=c++20 -Wall -Wextra -O2 main.cpp LRUCache.cpp FIFO.cpp LFUCache.cpp Parser.cpp -o program.exe
```

## Utilisation

```bash
./program.exe <K> <fichier> [FIFO|LFU]   # LRU par défaut
./program.exe 4 large.txt FIFO
```

- `K` : capacité du cache (en blocs)
- `fichier` : un identifiant de bloc par ligne

Le programme affiche le cache après chaque accès, puis hits, misses et taux de hit.

## Principe

- La table `unordered_map<int, Node*>` retrouve un nœud en O(1) en moyenne.
- La liste doublement chaînée maintient l'ordre : `head` = LRU, `tail` = MRU.
  Elle retire ou déplace un nœud en O(1).
- `FIFO` et `LFUCache` héritent de `LRUCache` et redéfinissent `get`, `put` et `printCache`.

| | LRU | FIFO | LFU pondéré |
|---|---|---|---|
| Sur un hit | nœud → MRU | rien | compteur +1 |
| Bloc évincé | `head` | `head` (1er arrivé) | taux `compte/(temps − temps_arr)` minimal |
| `get` / `put` | O(1) moyen | O(1) moyen | O(1) moyen, éviction O(K) |

Pour le LFU, le bloc qui vient d'être inséré n'est jamais candidat. À taux égal,
c'est le plus ancien qui est évincé.

## Résultats (taux de hit, K = 4)

| Fichier | Accès | Blocs distincts | LRU | FIFO | LFU |
|---|---|---|---|---|---|
| Séquence 1 | 24 | … | 66,7 % | 66,7 % | 25,0 % |
| `large.txt` | 260 | … | 75,8 % | 81,9 % | 34,6 % |
| `fifo_vs_lru.txt` | 13 | … | 38,5 % | 23,1 % | 38,5 % |

Aucune politique ne domine partout. La variante LFU est pénalisée : un bloc
neuf a un taux nul et il est évincé au miss suivant s'il n'a pas été réutilisé.

## Fichiers

`LRUCache.*` (structure, LRU) · `FIFO.*` · `LFUCache.*` · `Parser.*` (fourni) · `main.cpp` (rejoue la séquence)
