#include "FIFO.hpp"
#include <stdexcept>
#include <iostream>

FIFO::FIFO(int capacite) : LRUCache(capacite)
{ 

    
}

double FIFO::get(int key)
{
/*
* Paramètre : la clé key supposé être présente dans le cache
* 
* Retourne la valeur de l'élément de clé key stocké dans le cache
* | ! | Throw une exception "cach miss" si la clé key n'est pas dans le cache
*/

    if(cache.contains(key)){
        return cache[key]->value; //Seul différence avec LRUCache, on ne remet pas la variable retourner en première position
    }else{
        throw std::out_of_range("cach miss");   
    }
}

void FIFO::put(int key, double value)
{
    if (cache.contains(key)) {
        cache[key]->value = value;          // mise à jour, SANS déplacer le nœud
    } else {
        Node* noeud = new Node{key, value, nullptr, nullptr};
        appendToTail(noeud);
        cache[key] = noeud;
        if (cache.size() > (long long unsigned)capacity) {
            Node* h = head;                 // le plus ancien
            removeNode(h);
            cache.erase(h->key);
            delete h;
        }
    }
}

void FIFO::printCache() const
{
/*
* Affiche le cache
* 
* Remarque : Pour afficher le cache, on parcours la liste de la tête à la queue, ce qui permet d'obtenir l'ordre du cache en plus, contrairement à ce que si on avait juste parcouru la table de correspondance 
*/
    Node* courant = head;
    std::cout << "Cache (Least Recent -> More Recent) | ";
    while (courant != nullptr) {
        std::cout << courant->key << " | ";
        courant = courant->next;  
    }
    std::cout << std::endl;
}