/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fPrioritized.h"
#include "fQueue.h"
#include "fBaseEvent.h"
#include "fPriorityQueue.h"

using namespace com::pcbsys::foundation;
using namespace com::pcbsys::foundation::collections;
using namespace com::pcbsys::foundation::fbase::collections;

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
namespace collections {

class fPriorityQueueFactory {
  public:
    static fPriorityQueue<fPrioritized>* createPriorityQueue();
    static fPriorityQueue<fBaseEvent>* createBaseEventPriorityQueue();
    DLL static fQueue* createAdaptedPriorityQueue();

    static const int sPriorityLevels = 10;
    static bool sPriorityQueuesEnabled;

    class AdaptedPriorityQueue : public fQueue {
      public:
        AdaptedPriorityQueue(fPriorityQueue<fPrioritized>* pAdaptedQueue) {
            pQueue = pAdaptedQueue;
        }
        virtual ~AdaptedPriorityQueue() {
            if(pQueue && pQueue->delRef()) {
                delete pQueue;
            }
        }

        virtual int size();
        virtual CountableObject* pop();
        virtual CountableObject* top();
        virtual void put(CountableObject *pObj);

      private:
        fPriorityQueue<fPrioritized>* pQueue;
    };

  private:
    fPriorityQueueFactory();
};

}
}
}
}
}
