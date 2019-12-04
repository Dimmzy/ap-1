//
// Created by dima on 04/12/2019.
//

#ifndef EX2__EX2_H_
#define EX2__EX2_H_
#include <string>
#include <unordered_map>
#include <fstream>
#include <functional>

using namespace std;

// LRU Implementation loosely based on 'http://bhrigu.me/blog/2017/01/22/lru-cache-c-plus-plus-implementation/'
/* Nodes in our linked list that contain the generics and their keys */
template<typename T>
class Object {
 public:
  string key;
  T obj;
  Object *previous, *next;
  Object(string key, T obj);
};

/* Object Constructor */
template<typename T>
Object<T>::Object(string key, T obj) {
  this->key = key;
  this->obj = obj;
  this->previous = NULL;
  this->next = NULL;
}

/* Linked list that contains the objects */
template<typename T>
class LinkedList{
 private:
  Object<T> *front, *back;
 public:
  LinkedList(): front(NULL), back(NULL) {};

  Object<T>* addFront(string key, T obj) {
    auto* newPage = new Object<T>(key, obj);
    if (this->front == NULL && this->back == NULL)
      front = back = newPage;
    else {
      newPage->next = front;
      front->previous = newPage;
      front = newPage;
    }
    return newPage;
  }

  /* Moves the current object/page to the front of the list */
  void movetoFront(Object<T>* page) {
    if (page == this->front)
      return;
    if (page == this->back) {
      back = back->previous;
      back->next = NULL;
    }
    else {
      page->previous->next = page->next;
      page->next->previous = page->previous;
    }
    page->next = front;
    page->previous = NULL;
    front->previous = page;
    front = page;
  }

  /* Removes the last index used */
  void removeBack() {
    if(back == NULL)
      return;
    if(front == back) {
      delete back;
      front = back = NULL;
    }
    else {
      Object<T>* temp = back;
      back = back->previous;
      back->next = NULL;
      delete temp;
    }
  }

  /* Getter functions for both ends of the list */
  Object<T>* getBack() {
    return this->back;
  }

  Object<T>* getFront() {
    return this->front;
  }

};

/* Cache manager class, using the above LRU implementation */
template<typename T>
class CacheManager{
 public:
  explicit CacheManager(int capacity);
  void insert(string key, T obj);
  T get(string key);
  void foreach(std::function<void(T&)> func);
  ~CacheManager();
 private:
  // Using a map for O(1) access to the cache
  unordered_map<string,Object<T>*> cacheMap;
  int maxCapacity{};
  int currentSize{};
  LinkedList<T> *pageList;
  string className;

};

/* Cache Manager Constructor */
template<typename T>
CacheManager<T>::CacheManager(int capacity) {
  this->maxCapacity = capacity;
  this->currentSize = 0;
  this->cacheMap = unordered_map<string, Object<T>*>();
  this->pageList = new LinkedList<T>();
}

/* Inserts a file into the cache &
 * writes a file corresponding to the class_name field  + the key for identification */
template<typename T>
void CacheManager<T>::insert(string key, T obj) {
  this->className = obj.class_name;
  fstream file;
  file.open(obj.class_name+key,ios::out|ios::binary);
  if (!file)
    throw "Can't write to file";
  file.write((char*)&obj, sizeof(obj));
  file.close();
  if(cacheMap.find(key) != cacheMap.end()) {
    cacheMap[key]->obj = obj;
    pageList->movetoFront(cacheMap[key]);
    return;
  }
  // If the cache is full we'll kick the last used index out using removeBack() function of the list
  if (currentSize == maxCapacity) {
    string tempKey = pageList->getBack()->key;
    cacheMap.erase(tempKey);
    pageList->removeBack();
    currentSize--;
  }
  Object<T> *page = pageList->addFront(key, obj);
  currentSize++;
  cacheMap[key] = page;
}
/* Attempts to get an object from the cache, if it fails loads it from a file */
template<typename T>
T CacheManager<T>::get(string key) {
  if (cacheMap.find(key) == cacheMap.end()) {
    fstream file;
    file.open(this->className+key,ios::out|ios::binary|fstream::in);
    if (!file)
      throw "Unable to find object";
    T getObj;
    file.read((char*)&getObj,sizeof(getObj));
    pageList->addFront(key,getObj);
    return getObj;
  }
  T getObj = cacheMap[key]->obj;
  pageList->movetoFront(cacheMap[key]);
  return getObj;
}

/* Iterates over the cache, calling the print function for each object in cache */
template<typename T>
void CacheManager<T>::foreach(const function<void(T &)> func)  {
  Object<T>* node = pageList->getFront();
  for(int i = 1; i <= this->currentSize; i++) {
    func(node->obj);
    node = node->next;
  }
}

/* Destructor for CacheManager */
template<typename T>
CacheManager<T>::~CacheManager() {
  for(auto obj : this->cacheMap)
    delete(obj.second);
  delete pageList;
}


#endif //EX2__EX2_H_
