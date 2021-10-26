/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fLoggerListener.h"
#include "Poco/Mutex.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nLogListener;

using namespace foundation::fbase;

class nPkgLogListener :
    public fLoggerListener {
  public:
    nPkgLogListener(void);
    virtual ~nPkgLogListener(void);

    virtual void report(const std::string& msg);
    void addListener(nLogListener *pList);
    void delListener(nLogListener *pList);
    int size();

  private:
    std::list<std::string> m_history;
    std::list<nLogListener*> m_listeners;
    Poco::Mutex m_listenerMutex;
};

}
}
}
}
