#include "linkedList.h"


vec3LinkedListItem::vec3LinkedListItem(vec3 _data, long _time){
    time = _time;
    data = _data;
    next = NULL;
};
vec3LinkedListItem* vec3LinkedListItem::getNext(){
    return next;
}
void vec3LinkedListItem::setNext(vec3LinkedListItem* _next){
    next = _next;
}
vec3 vec3LinkedListItem::getData(){
    return data;
}
void vec3LinkedListItem::setData(vec3 _data){
    data = _data;
}
long vec3LinkedListItem::getTime(){
    return time;
}

vec3LinkedList::vec3LinkedList(){
    start = NULL;
    current = NULL;
}

void vec3LinkedList::pushBack(vec3 v){
    vec3LinkedListItem* item = new vec3LinkedListItem(v, micros());
    if(start == NULL){
        start = item;
        current = item;
    }else{
        current->setNext(item);
        current = item;
    }
    count++;
}

/*
vec3 vec3LinkedList::getNth(long i){
    if(i>=count)
        TODO throw "INDEX TOO BIG";
    else{
        vec3LinkedListItem* curr = start;
        long currIndex = 0;
        while(currIndex < i)
            curr = curr->getNext();
        return curr->getData();
    }
}
*/
vec3LinkedList::~vec3LinkedList(){
    vec3LinkedListItem* curr = start;
    vec3LinkedListItem* next;
    if(curr != NULL)
        next = curr->getNext();
    while(curr != NULL){
        delete curr;
        curr = NULL;
        if(next != NULL){
            curr = next;
            next = next->getNext();
        }
        yield();
    }
}

void vec3LinkedList::printToSerial(){
    vec3LinkedListItem* curr = start;
    while(curr != NULL){
        Serial.print(curr->getTime(), DEC);
        Serial.print(',');
        curr->getData().printToSerial();
        curr = curr->getNext();
        yield();
    }
}
