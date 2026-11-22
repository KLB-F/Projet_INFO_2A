# Projet LRU - Squelette libre

# Cache LRU et comparaison de politiques de remplacement

## Contexte

Un système embarqué (un robot, par exemple) dispose d'une mémoire rapide mais
petite, de K blocs, et d'une mémoire lente mais grande. Charger un bloc depuis
la mémoire lente coûte cher : on garde donc en mémoire rapide les blocs jugés
les plus utiles. Quand le cache est plein, une **politique de remplacement**
choisit le bloc à évincer.

Ce projet implémente une politique **LRU** (Least Recently Used) efficace,
puis la compare à **FIFO** et à une variante de **LFU** sur des séquences
d'accès réelles.

## Compilation et exécution

Le code utilise `unordered_map::contains`, qui nécessite C++20.

```bash
g++ -std=c++20 -Wall -Wextra -O2 main.cpp LRUCache.cpp FIFO.cpp LFUCache.cpp Parser.cpp -o program.exe
```

```bash
./program.exe <K> <fichier_d_accès> [FIFO|LFU]
```

| Argument | Rôle |
|---|---|
| `<K>` | capacité du cache, en nombre de blocs |
| `<fichier_d_accès>` | fichier texte, un identifiant de bloc par ligne |
| `FIFO` / `LFU` | politique utilisée ; LRU par défaut si absent ou non reconnu |

Exemples :

```bash
./program.exe 4 large.txt           # LRU, K = 4
./program.exe 4 large.txt FIFO      # FIFO, K = 4
./program.exe 2 fifo_vs_lru.txt LFU # LFU, K = 2
```

Le programme affiche l'état du cache après chaque accès, puis le nombre de
hits, de misses et le taux de hit (hits / nombre total d'accès).

## Structure de données

Un cache LRU doit faire deux opérations rapidement :

1. retrouver un bloc à partir de son identifiant ;
2. connaître le bloc le moins récemment utilisé, et faire passer un bloc
   en « plus récent » quand il est utilisé.

Aucune structure seule ne fait les deux en O(1) :

- une **liste doublement chaînée** maintient un ordre et déplace un nœud en
  O(1), mais chercher une clé coûte O(N) ;
- une **table de hachage** (`std::unordered_map`) trouve une clé en O(1) en
  moyenne, mais n'a pas d'ordre.

On combine donc les deux. La table associe chaque clé à son nœud
(`unordered_map<int, Node*>`), sans copier les données. Dans la liste,
`head` est le bloc le plus ancien (LRU) et `tail` le plus récent (MRU).

Les opérations élémentaires sur la liste (`removeNode`, `appendToTail`,
`moveToMostRecent`) sont en O(1). Elles traitent explicitement les cas
particuliers : liste vide, nœud en tête, nœud en queue, nœud seul.

## Les trois politiques

Les trois politiques partagent la liste et la table. Elles ne diffèrent que
sur deux points : **quand un nœud est déplacé** et **quel bloc est évincé**.
`FIFO` et `LFUCache` héritent de `LRUCache` et redéfinissent les méthodes
virtuelles `get`, `put` et `printCache`.

| | LRU | FIFO | LFU (variante) |
|---|---|---|---|
| Sur un hit | le nœud passe en MRU | rien ne change | le compteur d'accès est incrémenté |
| Ordre de la liste | ordre d'utilisation | ordre d'arrivée | ordre d'arrivée |
| Bloc évincé | `head` | `head` | taux d'utilisation minimal |
| Données supplémentaires | aucune | aucune | `freq_dict`, horloge `temps` |
| Coût de l'éviction | O(1) | O(1) | O(K) |

### LRU
- `get(key)` : retrouve le nœud via la table, le déplace en MRU et retourne
  sa valeur. Si la clé est absente, une exception est levée.
- `put(key, value)` : si la clé existe, met à jour la valeur et déplace le
  nœud en MRU. Sinon, crée un nœud en MRU ; si la capacité est dépassée,
  retire `head` de la liste **et** de la table, puis libère sa mémoire.

### FIFO
Même structure, mais un accès à une clé existante ne déplace pas le nœud.
La liste reste dans l'ordre d'arrivée et l'éviction retire toujours le bloc
entré le plus tôt.

### LFU pondéré par le temps
Il ne s'agit pas du LFU classique, qui compte simplement les accès. Ici, on
évince le bloc dont le **taux d'utilisation** est le plus faible :

```
taux = compte / (temps − temps_arr)
```

- `compte` : nombre d'accès au bloc depuis son arrivée ;
- `temps_arr` : instant d'arrivée du bloc dans le cache ;
- `temps` : horloge globale, incrémentée à chaque accès.

Diviser par l'âge du bloc évite qu'un bloc très utilisé autrefois reste
indéfiniment dans le cache. À taux égal, le bloc le plus ancien est évincé
(comparaison stricte). Le bloc que l'on vient d'insérer n'est jamais
candidat. Trouver le minimum demande de parcourir le cache : O(K).

## Boucle principale

Pour chaque identifiant lu, `main` teste `contains` :
- **hit** : appel de `get` ;
- **miss** : appel de `put`, qui représente le chargement depuis la mémoire
  lente.

## Complexités

| Opération | LRU | FIFO | LFU |
|---|---|---|---|
| `get` | O(1) moyen | O(1) moyen | O(1) moyen |
| `put` sans éviction | O(1) moyen | O(1) moyen | O(1) moyen |
| `put` avec éviction | O(1) moyen | O(1) moyen | O(K) |

« Moyen » parce que la table de hachage peut subir des collisions
(O(N) dans le pire cas).

## Résultats (K = 4)

| Fichier | Accès | Blocs distincts | LRU | FIFO | LFU |
|---|---|---|---|---|---|
| Séquence 1 | 24 | [à compléter] | 66,7 % | 66,7 % | 25,0 % |
| `large.txt` | 260 | [à compléter] | 75,8 % | 81,9 % | 34,6 % |
| `fifo_vs_lru.txt` | 13 | [à compléter] | 38,5 % | 23,1 % | 38,5 % |

Aucune politique ne domine partout : le résultat dépend de la séquence.
LRU l'emporte sur `fifo_vs_lru.txt`, construite pour favoriser la réutilisation
récente. FIFO l'emporte sur `large.txt` [expliquer : motif cyclique ? blocs
réutilisés à intervalle régulier ?].

La variante LFU obtient les moins bons résultats. Explication probable : un
bloc qui vient d'arriver a `compte = 0`, donc un taux nul. Il est presque
toujours évincé au miss suivant s'il n'a pas été réutilisé entre-temps, ce
qui pénalise les séquences où un bloc est réutilisé peu après son chargement.

## Limites et pistes d'amélioration

- **Évaluation** : les séquences sont courtes, et sur 13 ou 24 accès les
  premiers chargements (misses obligatoires) pèsent lourd. Il serait plus
  parlant de tracer le taux de hit en fonction de K, et de comparer à
  l'algorithme optimal de Belady (OPT), qui donne une borne supérieure.
- **LFU** : initialiser `compte` à 1 à l'insertion, ou comparer au LFU
  classique. Il existe aussi un LFU en O(1) (Shah, Mitra & Matani, 2010).
- **Conception** : FIFO et LFU héritent de `LRUCache` par commodité. Une
  classe abstraite `Cache` commune serait plus juste, car un FIFO n'est pas
  un LRU.
- **Cache miss** : il est signalé par une exception, alors que c'est un cas
  normal. Un retour `std::optional<int>` éviterait aussi la double recherche
  `contains` puis `get`.
- **Mémoire** : les nœuds sont gérés avec `new`/`delete`. `std::list` avec
  `splice` donnerait les mêmes complexités sans gestion manuelle.

## Organisation des fichiers

| Fichier | Contenu |
|---|---|
| `LRUCache.hpp/.cpp` | liste + table, `get`, `put`, opérations sur la liste |
| `FIFO.hpp/.cpp` | politique FIFO |
| `LFUCache.hpp/.cpp` | politique LFU pondérée par le temps |
| `Parser.hpp/.cpp` | lecture du fichier d'accès (fourni) |
| `main.cpp` | rejoue la séquence et calcule le taux de hit |
