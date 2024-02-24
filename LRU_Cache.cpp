// Rahul Kumar
#include<bits/stdc++.h>
using namespace std;

#define ll long long

class DoublyLinkedList{
    public:
    string data;
    DoublyLinkedList *next = NULL, *prev = NULL;
    DoublyLinkedList(string key, DoublyLinkedList* next, DoublyLinkedList*prev){
        this->data = key;
        this->next = next;
        this->prev = prev;
    }
    DoublyLinkedList(string key){
        this->data = key;
    }
};

// LRU Cache Policy
class EvictionPolicy{
    private:
    DoublyLinkedList *head = NULL, *tail = NULL;
    map<string, string> storage;
    int size;
    map<string, DoublyLinkedList*> mp;
    void addNode(DoublyLinkedList *node){
        node->next = head->next;
        node->next->prev = node;
        head->next = node;
        node->prev = head;
    }
    void detachNode(DoublyLinkedList *node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    void removeNode(){
        DoublyLinkedList *toDelete = tail->prev;
        mp.erase(toDelete->data);
        tail->prev = toDelete->prev;
        toDelete->prev->next = tail;
        cout<<storage[toDelete->data]<<" Deleted Node"<<endl;
        delete(toDelete);
    }
    public:
    EvictionPolicy(int n){
        this->size = n;
        head = new DoublyLinkedList("1");
        tail = new DoublyLinkedList("1");
        head->next = tail;
        tail->prev = head;
    }
    void add(string key, string value){
        if(storage.find(key) != storage.end()){
            detachNode(mp[key]);
            addNode(mp[key]);
            storage[key] = value;
        }else{
            if(storage.size() >= size){
                removeNode();
            }
            storage[key] = value;
            DoublyLinkedList *node= new DoublyLinkedList(key);
            mp[key] = node;
            addNode(node);
        }
    }
    
    string get(string key){
        if(storage.find(key) != storage.end()){
            detachNode(mp[key]);
            addNode(mp[key]);
            return storage[key];
        }
        return "Invalid Key";
    }
    
};

class Cache{
    private:
    EvictionPolicy *evictionpolicy;
    public:
    Cache(EvictionPolicy *evictionpolicy){
        this->evictionpolicy = evictionpolicy;
    }
    void put(string key, string value){
        evictionpolicy->add(key, value);
    }
    string get(string key){
        return evictionpolicy->get(key);
    }
};

int main(){
    EvictionPolicy *evictionpolicy = new EvictionPolicy(4);
    Cache ch(evictionpolicy);
    ch.put("first", "Rahul");
    ch.put("second", "Vijay");
    cout<<ch.get("first")<<endl;
    ch.put("third", "Bhanu");
    cout<<ch.get("random")<<endl;
    ch.put("fourth", "Pari");
    // Now Vijay must be removed according to LRU
    ch.put("fifth", "Nehnu");
    return 0;
}
