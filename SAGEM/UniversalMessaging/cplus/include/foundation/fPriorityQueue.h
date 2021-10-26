/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"
#include "fPrioritized.h"
#include <Poco/AtomicCounter.h>
#include <stdio.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
namespace collections {

template<typename T>
class fPriorityQueue : public NotifyableCountableObject {
  public:
    fPriorityQueue(const int priorityLevels) {
        this->priorityLevels = priorityLevels;
        this->mySize = 0;

        myHeads = new fLinkedNode*[priorityLevels];
        myTails = new fLinkedNode*[priorityLevels];

        myPreviousTop = NULL;

        myHeadLocks = new Poco::Mutex*[priorityLevels];
        myTailLocks = new Poco::Mutex*[priorityLevels];

        for(int i = 0; i < priorityLevels; i++) {
            myHeads[i] = new fLinkedNode();
            myTails[i] = myHeads[i];

            myHeadLocks[i] = new Poco::Mutex();
            myTailLocks[i] = new Poco::Mutex();
        }
    }

    virtual ~fPriorityQueue() {
        myPreviousTop = NULL;
        while (size() != 0) pop();
        for(int i = 0; i < priorityLevels; i++) {
            if(myHeads[i])delete myHeads[i];
            delete myHeadLocks[i];
            delete myTailLocks[i];
        }
        delete[] myHeads;
        delete[] myTails;

        delete[] myHeadLocks;
        delete[] myTailLocks;
    }

    virtual int size() {
        return mySize.value();
    }

    virtual T* pop() {
        if(myPreviousTop != NULL) {
            T* rVal = myPreviousTop->val;
            int priorityLevel = rVal->getPriority();
            if(priorityLevel >= this->priorityLevels || priorityLevel < 0) {
                priorityLevel = fPrioritized::sMinPriority;
            }
            Poco::ScopedLock<Poco::Mutex> lock(*myHeadLocks[priorityLevel]);
            fLinkedNode* oldHead = myHeads[priorityLevel];
            myHeads[priorityLevel] = myPreviousTop;
            myPreviousTop = NULL;
            delete oldHead;
            mySize--;
            return rVal;
        }

        for(int i = priorityLevels - 1; i >= 0; i--) {
            T* val = pop(i);
            if(val != NULL) {
                return val;
            }
        }

        return NULL;
    }

    virtual T* pop(int priorityLevel) {
        if(priorityLevel >= this->priorityLevels || priorityLevel < 0) {
            priorityLevel = fPrioritized::sMinPriority;
        }
        Poco::ScopedLock<Poco::Mutex> lock(*myHeadLocks[priorityLevel]);
        fLinkedNode* node = myHeads[priorityLevel];
        fLinkedNode* newHead = node->next;

        if(newHead == NULL) {
            return NULL;
        }

        T* rVal = newHead->val;
        myHeads[priorityLevel] = newHead;
        mySize--;
        delete node;
        return rVal;
    }

    virtual T* top() {
        for(int i = priorityLevels - 1; i >= 0; i--) {
            int priorityLevel = i;
            Poco::ScopedLock<Poco::Mutex> lock(*myHeadLocks[priorityLevel]);
            fLinkedNode* node = myHeads[priorityLevel];
            fLinkedNode* newHead = node->next;

            if(newHead == NULL) {
                continue;
            }
            myPreviousTop = newHead;
            T* rVal = newHead->val;
            return rVal;
        }
        return NULL;
    }

    virtual void put(T* priorityObject) {
        if(priorityObject == NULL) {
            return;
        }

        int priorityLevel = priorityObject->getPriority();
        if(priorityLevel >= this->priorityLevels || priorityLevel < 0) {
            priorityLevel = fPrioritized::sMinPriority;
        }
        fLinkedNode* newNode = new fLinkedNode();
        newNode->val = priorityObject;
        newNode->next = NULL;

        Poco::ScopedLock<Poco::Mutex> lock(*myTailLocks[priorityLevel]);
        myTails[priorityLevel]->next = newNode;
        myTails[priorityLevel] = newNode;
        mySize++;
    }

    struct fLinkedNode {
        T* val;
        fLinkedNode* next;
    };

  private:
    int priorityLevels;
    Poco::AtomicCounter mySize;

    fLinkedNode** myHeads;
    fLinkedNode** myTails;

    fLinkedNode* myPreviousTop;

    Poco::Mutex** myHeadLocks;
    Poco::Mutex** myTailLocks;
};

}
}
}
}
}
