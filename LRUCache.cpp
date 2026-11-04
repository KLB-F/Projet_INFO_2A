#include "LRUCache.hpp"

#include <stdexcept>
#include <unordered_map>

LRUCache::LRUCache(int capacity)
{
    this->capacity = capacity;
    compteur = 0;
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
    return (cache.contains(key));
}

double LRUCache::get(int key)
{
    if(cache.contains(key)){
        this->moveToMostRecent(cache[key]);
        return cache[key]->value;
    }else{
        throw std::out_of_range("cach miss");   
    }
}

void LRUCache::put(int key, double value)
{
    if(cache.contains(key)){ //Cas n°1 : la clé existe déjà
        cache[key]->value = value;
        this->moveToMostRecent(cache[key]);
    }else{ // Cas n°2 : La clé n'existe pas
        Node* noeud = new Node{compteur, value, nullptr, nullptr};
        this->appendToTail(noeud);
        cache[noeud->key] = noeud; //Ajout au cache
        if(cache.size() > capacity){ //Si il y a trop d'élément on supprime
            Node* h = head;
            this->removeNode(head);
            cache.erase(h->key);
            delete h;
        }
    }
}

int LRUCache::size() const
{
    return cache.size();
}

int LRUCache::getCapacity() const
{
    return capacity;
}

void LRUCache::printCache() const
{
    // TODO
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
/* Permet de move une node déjà dans la liste au début

Paramètre :
- node (Node) : la node à bouger
*/

this->removeNode(node);
this->appendToTail(node);

}