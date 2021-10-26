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

namespace com {
namespace pcbsys {
namespace foundation {
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
using namespace nbase;

class nStreamStatusUpdate :
    public nEvent {
  public:
    nStreamStatusUpdate(void);
    nStreamStatusUpdate(int action, longlong groupName, const std::string& streamId, const std::string& subject);
    nStreamStatusUpdate(int action, nBaseDataGroup *pGroupId, const std::string& subject);
    nStreamStatusUpdate(longlong *pIds, int nId, std::string *pNames, int nName);
    virtual ~nStreamStatusUpdate(void);

    virtual const std::string& getStreamId();
    virtual void setStreamId(const std::string& streamId);
    virtual nBaseDataGroup* getGroup();
    virtual void setGroup(nBaseDataGroup *pGroupId);
    virtual const std::string& getSubject();
    virtual void setSubject(const std::string& subject);
    virtual int getAction();
    virtual longlong getGroupID();
    virtual void setAction(int action);
    virtual longlong* getIDs(int& nIds);
    virtual std::string* getNames(int& nName);

    virtual void setAdmin(bool admin);
    virtual bool isAdmin();

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performWrite(fEventOutputStream *pOos);
    virtual void performRead(fEventInputStream *pOis);

    void setServerInduced(bool flag);
    bool wasServerInduced();

    static const int sStreamAdded = 1;
    static const int sStreamDeleted = 2;

    static const int sSnoopStreamAdded = 3;
    static const int sSnoopStreamDeleted = 4;

    static const int sGroupAdded = 11;
    static const int sGroupDeleted = 12;
    static const int sGroupRemoved = 13;
    static const int sGroupInserted = 14;

    static const int sDataGroupMapping = 30;

  private:
    int m_action;
    nBaseDataGroup *m_pGroup;

    longlong m_groupID;
    std::string m_streamId;
    std::string m_subject;

    longlong *m_pIds;
    int m_nId;
    std::string *m_pNames;
    int m_nName;
    bool m_bServerInduced;
    bool _isAdmin;
};

}
}
}
}
}
