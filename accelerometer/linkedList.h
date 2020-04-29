#ifndef VEC3_Linked_List_h
#define VEC3_Linked_List_h
#include "vec3.h"
#include <Arduino.h>
#include <PubSubClient.h>

class vec3LinkedListItem{
    private:
        vec3 data;
        vec3LinkedListItem* next;
        unsigned long time;
    public:
        vec3LinkedListItem(vec3 _data, long time);
        vec3LinkedListItem* getNext();
        void setNext(vec3LinkedListItem* _next);
        vec3 getData();
        void setData(vec3 _data);
        long getTime();
};

class vec3LinkedList{
    private: 
        vec3LinkedListItem* start;
        vec3LinkedListItem* current;
        long count = 0;
        long startTime;
    public:
        void setTime(long time);
        vec3LinkedList();
        void pushBack(vec3 v);
        vec3 getNth(long i);
        ~vec3LinkedList();
        void printToSerial();
        long getCount();
        //vec3 vec3LinkedList::getNth(long i);
        void uploadToMQTT(PubSubClient client, String deviceName);
};

#endif