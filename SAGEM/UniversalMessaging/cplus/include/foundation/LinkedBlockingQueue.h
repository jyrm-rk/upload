/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fDriver.h"
#include "BlockingQueue.h"
#include <list>
#include "Poco/Mutex.h"
#include "Poco/Event.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {
template<class T>
class LinkedBlockingQueue : public BlockingQueue<T> {
  public:
    LinkedBlockingQueue() {
    };

    virtual ~LinkedBlockingQueue() {
        m_list.clear();
    };

    void add(T driver) {
        Poco::Mutex::ScopedLock lock(m_lock);
        m_list.push_back(driver);
        m_event.set();
    };

    T poll(int waitTime) {        
        if(m_list.size()==0) {            
            m_event.tryWait(waitTime);            
        }
        if(m_list.size()==0) {            
            return NULL;
        }
		Poco::Mutex::ScopedLock lock(m_lock);
        T tmp = m_list.front();
        m_list.pop_front();        
        return tmp;
    };

	int size(){
		return m_list.size();
	}

  private:
    std::list<T> m_list;
    Poco::Mutex m_lock;
    Poco::Event m_event;

};
}
}
}
}


