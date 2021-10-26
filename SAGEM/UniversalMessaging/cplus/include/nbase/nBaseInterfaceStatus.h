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
namespace foundation {
namespace fbase {
class fEventDictionary;
}
}
namespace nirvana {
namespace nbase {

using namespace foundation::fbase;

class nBaseInterfaceStatus :
    public fExternalable, public CountableObject {

    friend class nMulticastStatus;

  public:
    nBaseInterfaceStatus(void);
    virtual ~nBaseInterfaceStatus(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);

    virtual std::string getName();
    virtual longlong getByteTX();
    virtual longlong getByteRX();
    virtual longlong getTotalConnections();
    virtual longlong getFailedConnections();
    virtual longlong getExhaustedTime();
    virtual int getIdleThreads();
    virtual int getExhaustedCount();
    virtual longlong getAuthTime();
    virtual int getReadBW();
    virtual int getWriteBW();
    virtual int getReadTotal();
    virtual int getWriteTotal();

  protected:
    fEventDictionary *m_pData;

  private:

    static const std::string sName;
    static const std::string sStatus;
    static const std::string sRx;
    static const std::string sTx;
    static const std::string sTotCon;
    static const std::string sAuthTime;
    static const std::string sFailed;
    static const std::string sExhTime;
    static const std::string sIdleCount;
    static const std::string sExhCount;
    static const std::string sReadBW;
    static const std::string sWriteBW;
    static const std::string sReadTotal;
    static const std::string sWriteTotal;
};

}
}
}
}
