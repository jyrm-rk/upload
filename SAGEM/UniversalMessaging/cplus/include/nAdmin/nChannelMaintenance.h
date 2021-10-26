/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nEvent.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace nbase::events;

class nChannelMaintenance :
    public nEvent {
  public:
    nChannelMaintenance();
    nChannelMaintenance(const std::string& channelName);
    nChannelMaintenance(bool rollAudit);
    virtual ~nChannelMaintenance(void);

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

  private:
    std::string m_channelName;
    bool m_bAuditMaint;
};

}
}
}
}
}
