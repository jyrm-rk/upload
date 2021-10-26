/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSynchronous.h"
#include "fBase.h"

#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
class fEventOutputStream;
}
}
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace nbase::events;
using namespace foundation::io;
using namespace foundation::fbase;

class nSchedulerRequest :
    public nSynchronous {
  public:
    nSchedulerRequest(void);
    virtual ~nSchedulerRequest(void);

    virtual void readExternal(fEventInputStream *pOis);
    virtual void writeExternal(fEventOutputStream *pOos);
    virtual const std::string getTypeString();
    virtual nEvent* createInstance();
    virtual int getType();

    virtual int getCommand();
    virtual const std::string& getScheduler();

    static const int sAdd = 10;
    static const int sDel = 20;
    static const int sGet = 30;

  private:
    typedef std::map<std::string, std::string> LEVEL1MAP;
    typedef std::map<std::string, LEVEL1MAP*> LEVEL2MAP;
    typedef std::map<std::string, std::list<std::string>*> LEVEL3MAP;

    int m_command;
    std::string m_scheduler;
    std::string m_subject;
    std::list<std::string> m_tasks;
    std::list<std::string> m_triggers;
    LEVEL2MAP m_help;
    LEVEL3MAP m_currentConfig;
    bool m_bClusterWide;
};

}
}
}
}
}
