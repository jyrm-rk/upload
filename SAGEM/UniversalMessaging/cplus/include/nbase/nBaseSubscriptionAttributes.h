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

#include <string>

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

using namespace foundation::io;
using namespace foundation::fbase;

class nBaseSubscriptionAttributes : public Countable {
  public:
    nBaseSubscriptionAttributes(void);
    nBaseSubscriptionAttributes(const std::string& name, const std::string& selector, longlong eid);
	nBaseSubscriptionAttributes(const std::string& name, const std::string& selector, longlong eid, longlong namedSubscriberID);
    virtual ~nBaseSubscriptionAttributes(void);

    virtual const std::string& getChannelName();
    virtual const std::string& getSelector();
    virtual longlong getEID();
	virtual longlong getNamedSubscriberID();
    virtual void writeExternal(fEventOutputStream *pOos);
    virtual void readExternal(fEventInputStream *pOis);

  private:
    std::string m_channelName;
    std::string m_selector;
    longlong m_eid;
	longlong m_namedSubscriberID;
};

}
}
}
}
