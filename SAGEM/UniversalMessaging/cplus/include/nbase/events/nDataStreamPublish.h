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
namespace events {

using namespace foundation::io;

class nPublished;

class nDataStreamPublish :
    public nSynchronous {
  public:
    nDataStreamPublish(void);
    nDataStreamPublish(nPublished *pEvt, const std::string& streams);
    nDataStreamPublish(nPublished *pEvt, std::string *pStreams, int nStream);
    nDataStreamPublish(nPublished **pEvt, int nEvt, const std::string& streams);
    nDataStreamPublish(nPublished **pEvt, int nEvt, std::string *pStreams, int nStream, bool bPubToAll = true);
    nDataStreamPublish(nPublished *pEvt, longlong dataGroup);
    nDataStreamPublish(nPublished *pEvt, longlong *pDataGroup, int nDataGroup);
    nDataStreamPublish(nPublished **pEvt, int nEvt, longlong dataGroup);
    nDataStreamPublish(nPublished **pEvt, int nEvt, longlong *pDataGroup, int nDataGroup, bool pubToAll = true);
    virtual ~nDataStreamPublish(void);

    virtual nPublished** getEvents(int &nEvent);
    virtual nPublished* getEvent();
    virtual std::string* getStreams(int &nStream);
    virtual longlong* getGroups(int& nDataGroup);
    virtual void setEvents(nPublished **ppEvents, int nEvent);
    virtual void setStreams(std::string* pStreams, int& nStream);
    virtual bool isStreams();
    bool isRegistered();
    const std::string& getRegisteredKey();
    void setRegistered(bool bRegistered);
    bool publishToAllGroups();

    virtual nEvent* createInstance();
    virtual const std::string getTypeString();
    virtual int getType();
    virtual void performWrite(fEventOutputStream *pOos);
    virtual void performRead(fEventInputStream *pOis);

  private:
    nPublished **m_ppEvents;
    int m_nEvent;
    nPublished* myEvent;
    std::string *m_pStreams;
    int m_nStream;
    bool m_bRegisteredEvent;
    longlong *m_pDataGroups;
    int m_nDataGroup;
    bool m_bStreams;
    bool m_bPubToAllGroups;
};

}
}
}
}
}
