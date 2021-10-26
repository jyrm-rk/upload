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
#include "fSortedList.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nConsumeEvent;
}
namespace nbase {

using namespace client;
using namespace foundation::collections;

class nRegisteredEventManager {
  public:
    nRegisteredEventManager(const std::string& key);
    virtual ~nRegisteredEventManager(void);

    nConsumeEvent* update(nConsumeEvent *pEvt);

  private:
    nConsumeEvent* processRegisteredEvent(nConsumeEvent *pEvt);

    fSortedList<Object*, nConsumeEvent*> m_events;
    std::string m_primaryKey;
};

}
}
}
}
