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

#include <list>
#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {

class nBaseChannelAttributes;

namespace events {

class nGetChannelList :
    public nSynchronous {
  public:
    nGetChannelList(void);
    nGetChannelList(const std::string& folder);
    virtual ~nGetChannelList(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

    std::list<nBaseChannelAttributes*>& getChannelList();
    void setChannelList (std::list<nBaseChannelAttributes*> channelList);

  protected:
    std::list<nBaseChannelAttributes*> m_channels;

  private:
    std::string m_folder;

};

}
}
}
}
}
