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
#include "nPublished.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {

class nBatchPublish : public nSynchronous {
  public:
    nBatchPublish(void);

    nBatchPublish(nPublished* evt, longlong destination);

    nBatchPublish(nPublished** evt, int nevts, longlong* destinations, int ndestinations);

    nBatchPublish(nPublished** evt, int nevts, longlong* destinations, int ndestinations, bool pubToAll);

    virtual ~nBatchPublish(void);

    virtual nPublished** getEvents();

    virtual longlong* getDestinations();

    virtual void setEvents(nPublished** events);

    virtual bool isRegistered();

    virtual void setRegistered(bool reg);

    virtual bool publishToAll();

    nEvent* createInstance();

    virtual void performWrite(fEventOutputStream* oos);

    virtual void performRead(fEventInputStream* ois);

    virtual const std::string getTypeString();
    virtual int getType();

  private:
    nPublished** myEvents;
    int myEventsLength;
    longlong* myDestinations;
    int  myDestinationsLength;
    bool _isPubToAll;
    bool _isRegistered;

  protected:
};
}
}
}
}
}
