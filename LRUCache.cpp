#include "LRUCache.hpp"

#include <stdexcept>
#include <unordered_map>
#include <iostream>

LRUCache::LRUCache(int capacity)
{
    this->capacity = capacity;
    head = nullptr; tail = nullptr;

}

LRUCache::~LRUCache()
{
 
    //Destruction du cache par parcours de la liste chaîné
    Node* courant = head;
    while (courant != nullptr) {
        Node* suivant = courant->next;
        delete courant;
        courant = suivant;
    }

}

bool LRUCache::contains(int key) const
{
/*
* Retourne : si la clé key est contenue dans le cache
*/
    return (cache.contains(key));
}

double LRUCache::get(int key)
{
/*
* Paramètre : la clé key supposé être présente dans le cache
* 
* Retourne la valeur de l'élément de clé key stocké dans le cache
* | ! | Throw une exception "cach miss" si la clé key n'est pas dans le cache
*/
    if(cache.contains(key)){
        this->moveToMostRecent(cache[key]);
        return cache[key]->value;
    }else{
        throw std::out_of_range("cach miss");   
    }
}

void LRUCache::put(int key, double value)
{
/*
* Permet d'ajouter ou de mettre à jour une valeur (value) dans le cache
* 
* Paramètres :
* value - La valeur à ajouter / mettre à jour
* key - La clé correspondante 
*/

    if(cache.contains(key)){ //Cas n°1 : la clé existe déjà
        cache[key]->value = value;
        this->moveToMostRecent(cache[key]);
    }else{ // Cas n°2 : La clé n'existe pas
        Node* noeud = new Node{key, value, nullptr, nullptr};
        this->appendToTail(noeud);
        cache[noeud->key] = noeud; //Ajout au cache
        if(cache.size() > (long long unsigned)capacity){ //Si il y a trop d'élément on supprime
            Node* h = head;
            this->removeNode(head);
            cache.erase(h->key);
            delete h;
        }
    }
}

int LRUCache::size() const{
/*
Retourne la taille du cache
*/
    return cache.size();
}

int LRUCache::getCapacity() const{
/*
Retourne la capacité maximale du cache
*/

    return capacity;
}

void LRUCache::printCache() const
{
/*
* Affiche le cache
* 
* Remarque : Pour afficher le cache, on parcours la liste de la tête à la queue, ce qui permet d'obtenir l'ordre du cache en plus, contrairement à ce que si on avait juste parcouru la table de correspondance 
*/
    Node* courant = head;
    std::cout << "Cache (LRU --> MRU) | ";
    while (courant != nullptr) {
        std::cout << courant->key << " | ";
        courant = courant->next;  
    }
    std::cout << std::endl;
}

void LRUCache::removeNode(Node* node){
/* Permet de retirer une node de la liste

Paramètre : 
- node (Node) : le noeud à retirer
 */

    //4 cas à traiter : le cas ou l'élément est au début de la liste, à la fin ou au milieu et ou c'est le seul élement
    if(node == head && node == tail){
        head = nullptr;
        tail = nullptr;
    }else if(node == head){
        head = node->next;
        head->previous = nullptr;
    }else if(node == tail){
        tail = node->previous;
        tail->next = nullptr;
    }else{
        Node* predecesseur = node->previous;
        Node* sucesseur = node->next;
        predecesseur->next = sucesseur;
        sucesseur->previous = predecesseur;
    }

}

void LRUCache::appendToTail(Node* node){
/* Permet d'ajouter un nouveau noeud en fin de liste 

Paramètre :
- node (Node) : le noeud à ajouter
*/

    if(tail == nullptr){
        head = node;
        tail = node;
        node->previous = nullptr;
        node->next = nullptr;
    }else{
        node->previous = tail;
        tail->next = node;
        tail = node;
        tail->next = nullptr; //On evite tous probleme en resettant le next de la queue
    }

}

void LRUCache::moveToMostRecent(Node* node){
/* Permet de move une node déjà dans la liste à la fin de celle-ci

Paramètre :
- node (Node) : la node à bouger
*/

this->removeNode(node);
this->appendToTail(node);

}