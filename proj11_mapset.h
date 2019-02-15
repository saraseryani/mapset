#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<sstream>
using std::ostringstream;



/////////////////////////////////////////////
// Node
//
template<typename K, typename V>
struct Node {
    K first;
    V second;
    Node *next = nullptr;
    
    Node() = default;
    Node(K,V);
    bool operator<(const Node&) const;
    bool operator==(const Node&) const;
    friend ostream& operator<<(ostream &out, const Node &n){
        out << n.first;
        out << ":";
        out << n.second;
        return out;
    }
};

template<typename K, typename V>
Node<K,V>::Node(K key, V value){
    first = key;
    second = value;
}

template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const{
    
    if(first <= n.first){
        return false;
    }
    else{
        return true;
    }
    
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const{
    if(first == n.first){
        return true;
    }
    else{
        return false;
    }
}


///////////////////////////////////////////////////
// MapSet
//
template<typename K, typename V>
class MapSet{
private:
    Node<K,V>* head_ = nullptr;
    Node<K,V>* tail_ = nullptr;
    size_t sz_ = 0;
    Node<K,V>* find_key(K);
    
public:
    MapSet()=default;
    MapSet(initializer_list< Node<K,V> >);
    MapSet (const MapSet&);
    MapSet operator=(MapSet);
    ~MapSet();
    size_t size();
    bool remove (K);
    bool add(Node<K,V>);
    Node<K,V> get(K);
    bool update(K,V);
    int compare(MapSet&);
    MapSet mapset_union (MapSet&);
    MapSet mapset_intersection(MapSet&);
    
    friend ostream& operator<<(ostream &out, const MapSet &ms){
        ostringstream oss;
        for(auto i = ms.head_; i != nullptr ; i = i-> next){
            oss << *i << ", ";
        }
        string s = oss.str();
        s = s.substr(0,s.length() - 2);
        out << s;
        return out;
    }
};

template<typename K, typename V>
MapSet<K,V>::MapSet(initializer_list< Node<K,V> > il){
    for(auto i: il){
        add(i);
    }
    
}

template<typename K, typename V>
MapSet<K,V>::MapSet(const MapSet &ms){
    if (ms.head_ == nullptr){
        head_ = nullptr;
        tail_ = nullptr;
    }
    
    else{
        head_ = new Node<K,V>(ms.head_-> first, ms.head_-> second);
        tail_ = head_;
        Node<K,V>* ms_ptr = ms.head_->next;
        Node<K,V>* new_node;
        
        while (ms_ptr != nullptr){
            new_node = new Node<K,V>(ms.head_-> first, ms.head_-> second);
            tail_->next = new_node;
            ms_ptr = ms_ptr->next;
            tail_ = new_node;
        }
    }
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet ms){
    swap(head_, ms.head_);
    swap(tail_, ms.tail_);
    return *this;
}

// walk down the list, moving head_ but remember it in to_del
// delete each node in turn, the set head_ and tail_
template<typename K, typename V>
MapSet<K,V>::~MapSet(){
    auto to_del = head_;
    
    while (to_del !=nullptr){
        head_ = head_->next;
        delete to_del;
        to_del = head_;
    }
    head_ = nullptr;
    tail_ = nullptr;
    
}

template<typename K, typename V>
size_t MapSet<K,V>::size(){
    return sz_;
}


template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key){
    
    if(sz_ == 0){
        //if the list is empty
        return nullptr;
    }
    
    for(auto itr = head_; itr != nullptr; itr = itr -> next){ // check if it's greater than
        auto itr2 = itr -> next;

        if((sz_ == 1) ){
            if(key > itr ->first){
                return itr; //returns
            }
            return nullptr; //if theres nothing less than the itr
        }
        
        if(key > itr ->first && key < itr2->first){
            return itr; //return lowest in between
        }
        
        if(key > tail_ ->first){
            return tail_; //at end
        }
        
        if(key < head_->first){
            return nullptr; //at the beginning
        }
        
        return nullptr;
    }
}

template<typename K, typename V>
bool MapSet<K,V>::add(Node<K,V> n){
    Node<K,V> * temp =  new Node<K,V>(n.first, n.second);

    auto finder = find_key(temp -> first);
    
    if((sz_ == 1) && (head_->first == temp->first)){ //checks if keys are the same
        return false;
    }
    
    if(finder != nullptr){ //if the find key returns null ptr
        if((finder->first == n.first)){
            return false; //checks if keys are the same
        }
        
        else{
            temp -> next = finder -> next;
            finder -> next = temp;
            
            if(finder == tail_){
                tail_ = temp;
            }
            
            sz_ ++;
            return true;
        }
        
    }
    
    else{ //not nullptr
        
        if(head_ != nullptr){ //first item in find key is nullptr
            temp-> next = head_;
            head_ = temp;
        }
        
        else{
            head_ = temp;
            tail_ = temp;
        }
        
        sz_++;
        return true;
    }
    
}


template<typename K, typename V>
bool MapSet<K,V>::remove(K key){
    auto i = head_; //lagging
    auto i2 = i -> next; //leading
    
    for(i; i2 != nullptr; i = i2, i2 = i2 -> next){ //increments i2

        if(i2 -> first == key){
            i -> next = i2 -> next;
            sz_ --;
            
            delete i2;
            
            return true;
        }
    }
    return false;  
 
}


template<typename K, typename V>
Node<K,V> MapSet<K,V>::get(K key){

    for(auto itr = head_; itr != nullptr; itr = itr -> next){
        //if the key has a pair, return the is_pair
        if(itr -> first == key){
            return Node<K,V>(key, itr->second) ;
        }
    }
    return Node<K,V>("", 0);
}


template<typename K, typename V>
bool MapSet<K,V>::update(K key, V value){

    for(auto itr = head_; itr != nullptr; itr = itr -> next){
        //if the key has a pair, return the is_pair
        if(itr -> first == key){
            itr -> second = value;
            return true;
        }
    }

    return false;
    
}


template<typename K, typename V>
int MapSet<K,V>::compare(MapSet &ms){
    unsigned int sizecheck = 0;
    
    if(ms.sz_ < sz_){ //size check
        sizecheck = ms.sz_;
    }

    else{
        sizecheck = sz_;
    }
    
    for(auto i = ms.head_, j = head_; i != nullptr && j != nullptr; i = i-> next, j = j -> next){
        if(i ->first < j ->first ){
            //returns -1 if the size is greater
            return 1;
        }
        
        else if(i ->first > j ->first){
            //returns 1 if the size is less than
            return -1;
        }
    }
    
    //checks size second
    if(ms.sz_ < sz_){
        return 1;
    }
    
    else if(ms.sz_ > sz_){
        return -1;
    }
    else{
        return 0;
    }

 return 0;    
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_union(MapSet<K,V> &ms){
    MapSet<K,V> newmapset;
    
   for(auto i = head_; i != nullptr; i = i-> next){
        //cout << *i << endl;
        //adds each element
        newmapset.add(*i);
    }
    
    for(auto j = ms.head_; j != nullptr; j = j-> next){
        //cout << *j << endl;
        if(find_key(j -> first) != nullptr ){
            newmapset.add(*j);
        }
    }
    
    return newmapset;
    
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms){
    MapSet<K,V> newmapset;
    
    for(auto i = ms.head_; i != nullptr ; i = i-> next){
        //the first item
        for(auto j = head_; j != nullptr ; j = j -> next){
            //the second item
            if(i ->first == j ->first){
                //if the keys are the same
                newmapset.add(*j);   
            }
        }
    }
    
    return newmapset;
}

#endif