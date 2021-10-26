/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fExternalable.h"
#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;

class nBaseDataStream : public fExternalable, public CountableObject {
  public:
    nBaseDataStream();
    nBaseDataStream(const std::string& name, const std::string& subject);
    virtual ~nBaseDataStream(void);

    virtual const std::string& getName ();
    virtual const std::string& getSubject ();
    virtual void close();
    const std::string& getRealmName();
    void setRealmName(const std::string& name);
    virtual void incrementUsage();
    virtual void decrementUsage();
    virtual longlong getLastMsg();
    virtual void setLastMsg(longlong lastMsg);
    virtual Object* getUserObject();
    virtual void setUserObject(Object *pUserObject);
    virtual longlong getDisconnectTime();
    virtual void setDisconnectTime(longlong disconnectTime);
    virtual void writeExternal(fEventOutputStream *pEos);
    virtual void readExternal(fEventInputStream *pEis);
    virtual int getType();

    bool isSnoop();
    void setSnoop(bool _snoop);

    DLL void setAdmin(bool admin);
    DLL bool isAdmin();

  protected:
    std::string m_name;
    std::string m_subject;
    std::string m_realmName;

  private:
    int m_usage;
    longlong m_lastMsg;
    longlong m_disconnectTime;
    bool snoop;
    bool _isAdmin;

    Object* m_pUserObject;
};

}
}
}
}
