# Projet LRU - Squelette libre

## Principe

Le squelette fournit uniquement :

- l'interface publique attendue pour `LRUCache`;
- un parser de fichiers d'accès;
- un `main.cpp` minimal;
- plusieurs fichiers de test.

L'implémentation interne du cache est volontairement laissée libre.

## Contraintes d'implémentation

Votre cache doit combiner :

- une liste doublement chaînée pour maintenir l'ordre LRU -> MRU;
- une `std::unordered_map` pour retrouver rapidement un élément à partir de sa clé.

Vous devez choisir vous-même :

- la structure d'un noeud;
- les attributs privés de `LRUCache`;
- les fonctions auxiliaires;
- la manière dont la `unordered_map` référence les éléments de la liste.

## Interface publique imposée

```cpp
class LRUCache {
public:
    explicit LRUCache(int capacity);
    ~LRUCache();

    bool contains(int key) const;
    double get(int key);
    void put(int key, double value);

    int size() const;
    int getCapacity() const;

    void printCache() const;
};
```

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
    main.cpp LRUCache.cpp Parser.cpp \
    -o lru
```

## Exécution

```bash
./lru 3 data/sequence_simple.txt
```

## Fichiers de test

- `sequence_simple.txt` : vérification manuelle.
- `sequence_reuse.txt` : forte localité temporelle.
- `sequence_stream.txt` : presque aucune réutilisation.
- `sequence_loop.txt` : petit ensemble répété.
- `sequence_working_set.txt` : plusieurs phases de travail.
- `sequence_fifo_vs_lru.txt` : différence FIFO/LRU.
- `sequence_bursty.txt` : accès par rafales.
- `sequence_single.txt` : un seul bloc.
- `sequence_capacity_edge.txt` : nombreuses évictions avec petite capacité.
- `sequence_large.txt` : séquence longue pour les statistiques.
