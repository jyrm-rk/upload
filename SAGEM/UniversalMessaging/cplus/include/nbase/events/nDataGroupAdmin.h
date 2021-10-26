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

#include <vector>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fEventDictionary;
}
namespace io {
class fEventOutputStream;
class fEventInputStream;
}
}
namespace nirvana {
namespace nbase {

class nBaseDataGroup;

namespace events {

using namespace foundation::io;
using namespace foundation::fbase;
using namespace nbase;

class nDataGroupAdmin :
    public nSynchronous {
  public:
    nDataGroupAdmin(void);
    nDataGroupAdmin(int cmd, bool listener);
    nDataGroupAdmin(int cmd);
    nDataGroupAdmin(int cmd, const std::string& name);
    nDataGroupAdmin(int cmd, std::string *pNames, int nName);
    nDataGroupAdmin(int cmd, const std::string& group, const std::string& add);
    nDataGroupAdmin(int cmd, const std::string& group, std::string *pAdd, int nAdd);
    virtual ~nDataGroupAdmin(void);

    virtual int getCommand();
    virtual const std::string& getName();
    virtual void setGroups(std::vector<nBaseDataGroup*>& global);
    virtual void setGroup(nBaseDataGroup *pGroup);
    virtual nBaseDataGroup* getGroup();
    virtual std::vector<nBaseDataGroup*>& getGroups();
    virtual const std::string& getGroupName();
    virtual bool hasRegisterListener();
    virtual void setRegisterListener(bool flag);
    std::string* getStreams(int& nStream);

    virtual void performWrite(fEventOutputStream *pOos);
    virtual void performRead(fEventInputStream *pOis);
    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    bool hasConflation();
    void setConflationInterval(longlong interval);
    longlong getConflationInterval();
    void setConflationMerge(bool performMerge);
    bool getConflationMerge();
    bool isSnoopStream();
    void setSnoopStream(bool flag);
    void resetStreams();
    bool hasGroupRegistration();
    void setGroupRegistration(bool hasGroupRegistration);

    void setEnableMulticast(bool enableMulticast);
    bool isEnableMulticast();

    void setName(std::string name);

    void setPriority(int newPriority);
    virtual unsigned int getPriority();

    static const int sAddGroup = 0;
    static const int sGetGroups = 1;
    static const int sDelGroup = 2;
    static const int sGetDefault = 3;
    static const int sAddGroups = 4;
    static const int sGetAll = 5;
    static const int sDelGroups = 6;
    static const int sRecoverClient = 7;

    static const int sAddStream = 10;
    static const int sDelStream = 11;

    static const int sAddPublishers = 21;
    static const int sGetPublishers = 22;
    static const int sDelPublishers = 23;

  private:
    int m_command;

    std::string m_name;
    std::string m_group;
    std::string *m_pStreams;
    int m_nStream;

    nBaseDataGroup *m_pDataGroup;
    std::vector<nBaseDataGroup*> m_groups;
    bool m_bRegisterListener;
    bool _hasGroupRegistration;
    bool _isSnoop;
    bool enableMulticast;

    fEventDictionary *m_pConflationConfig;

    static const std::string c_Interval;
    static const std::string c_Merge;

    int priority;
};

}
}
}
}
}
