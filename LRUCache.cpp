#include "LRUCache.hpp"

#include <stdexcept>
#include <unordered_map>

LRUCache::LRUCache(int capacity)
{
    

}

LRUCache::~LRUCache()
{
    
}

bool LRUCache::contains(int key) const
{
    // TODO
    return false;
}

double LRUCache::get(int key)
{
    // TODO
    throw std::out_of_range("TODO: get() not implemented");
}

void LRUCache::put(int key, double value)
{
    // TODO
}

int LRUCache::size() const
{
    // TODO
    return 0;
}

int LRUCache::getCapacity() const
{
    // TODO
    return 0;
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
    
    cache[node->key] = node; //Ajout au cache

}

void LRUCache::moveToMostRecent(Node* node){
/* Permet de move une node déjà dans la liste au début

Paramètre :
- node (Node) : la node à bouger
*/

this->removeNode(node);
this->appendToTail(node);

}