#include "LFUCache.hpp"
#include <stdexcept>
#include <iostream>

LFUCache::LFUCache(int capacite) : LRUCache(capacite)
{ 
    temps = 0;
}

LFUCache::~LFUCache(){

    if(head != nullptr){
        Node* actuel = head;
        for(int i = 0; i < this->size(); i++){
            delete freq_dict[actuel->key];
            actuel = actuel->next;
        }
    }
    
}

double LFUCache::get(int key){
/*
* Paramètre : la clé key supposé être présente dans le cache
* 
* Retourne la valeur de l'élément de clé key stocké dans le cache
* | ! | Throw une exception "cach miss" si la clé key n'est pas dans le cache
*/
    temps++;
    if(cache.contains(key)){
        freq_dict[key]->compte++;
        return cache[key]->value;
    }else{
        throw std::out_of_range("cach miss");   
    }

}

void LFUCache::put(int key, double value)
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
    }else{ // Cas n°2 : La clé n'existe pas
        Node* noeud = new Node{key, value, nullptr, nullptr};
        this->appendToTail(noeud);
        cache[noeud->key] = noeud; //Ajout au cache
        freq_dict[noeud->key] = new freq_var{temps, 0};
        temps++; //Permet d'éviter des divisions par 0 par la suite
        if(cache.size() > (long long unsigned)capacity){ //Si il y a trop d'élément on supprime
            
            //On trouve l'élément le moins utilisé

            double min_freq = 1.01; //La fréquence maximale possible est 1, d'où l'initialisation à cette valeur
            Node* actuel = head;
            Node* min = head;
            for(int j = 0; j < capacity; j++){
                if(((double)freq_dict[actuel->key]->compte/(double)(temps-freq_dict[actuel->key]->temps_arr)) < min_freq){
                    min_freq = ((double)freq_dict[actuel->key]->compte/(double)(temps-freq_dict[actuel->key]->temps_arr));
                    min = actuel;
                }
                actuel = actuel->next;
            }

            //On le supprime

            this->removeNode(min);
            cache.erase(min->key);
            delete freq_dict[min->key];
            freq_dict.erase(min->key);
            delete min;
        }
    }
}

void LFUCache::printCache() const
{
/*
* Affiche le cache
* 
* Remarque : Pour afficher le cache, on parcours la liste de la tête à la queue, ce qui permet d'obtenir l'ordre du cache en plus, contrairement à ce que si on avait juste parcouru la table de correspondance 
*/
    Node* courant = head;
    std::cout << "Cache | ";
    while (courant != nullptr) {
        std::cout << courant->key << " | ";
        courant = courant->next;  
    }
    std::cout << std::endl;
}