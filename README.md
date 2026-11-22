# Projet LRU : cache mémoire pour système embarqué

On implémente un cache LRU à partir d'une liste doublement chaînée et d'une
`unordered_map`, puis on le compare à une politique FIFO et à une variante
de LFU sur plusieurs séquences d'accès.

## Compilation

Le code utilise `unordered_map::contains`, il faut donc compiler en C++20 :

```bash
g++ -std=c++20 -Wall -Wextra -O2 main.cpp LRUCache.cpp FIFO.cpp LFUCache.cpp Parser.cpp -o program.exe
```

## Utilisation

```bash
./program.exe <K> <fichier> [FIFO|LFU]
```

`K` est la capacité du cache en nombre de blocs, et le fichier contient un
identifiant de bloc par ligne. Sans troisième argument, c'est LRU qui est
utilisé. Par exemple :

```bash
./program.exe 4 large.txt FIFO
```

Le programme affiche l'état du cache après chaque accès, puis le nombre de
hits, le nombre de misses et le taux de hit.

## Principe

Pour LRU, une `unordered_map<int, Node*>` retrouve un nœud en O(1) en moyenne.
Une liste doublement chaînée garde l'ordre d'utilisation, avec `head` pour le
LRU et `tail` pour le MRU, et permet de déplacer un nœud en O(1). À chaque hit,
le nœud passe en MRU. Quand le cache est plein, on évince `head`.

FIFO utilise la même structure, sauf qu'un hit ne déplace pas le nœud. Le bloc
évincé est donc toujours le premier arrivé.

### LFU pondéré par le temps

Ce n'est pas le LFU classique. Celui-ci évince le bloc le moins souvent accédé,
ce qui pose un problème : un bloc très utilisé au début peut rester dans le
cache indéfiniment. On évince donc plutôt le bloc qui a le plus faible taux
d'utilisation :

```
taux = compte / (temps − temps_arr)
```

`compte` est le nombre de hits sur le bloc depuis son arrivée (0 à
l'insertion), `temps_arr` l'instant où il est entré dans le cache, et `temps`
une horloge globale incrémentée à chaque accès.

Trouver ce minimum oblige à parcourir tout le cache : l'éviction coûte donc
O(K).

## Résultats (taux de hit, K = 4)

| Fichier | Accès | LRU | FIFO | LFU |
|---|---|---|---|---|
| Séquence 1 | 24 | 66,7 % | 66,7 % | 25,0 % |
| `large.txt` | 260 | 75,8 % | 81,9 % | 34,6 % |
| `fifo_vs_lru.txt` | 13 | 38,5 % | 23,1 % | 38,5 % |

Aucune politique n'est meilleure sur toutes les séquences. La variante LFU
s'en sort mal : un bloc qui vient d'arriver a un taux nul. S'il n'est pas
réutilisé rapidement, il est évincé au miss suivant.

## Fichiers

- `LRUCache.*` : structure de données et politique LRU
- `FIFO.*` et `LFUCache.*` : les deux autres politiques
- `Parser.*` : lecture du fichier d'accès (fourni)
- `main.cpp` : rejoue la séquence et calcule le taux de hit
