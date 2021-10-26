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

namespace Poco {
class Thread;
}

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
namespace events {
class nEvent;
class nSynchronous;
}
}
namespace client {

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::nirvana::nbase::events;

/**
 * This class is the container for the request responses
 *
 */
class nRequestResponseContainer : public Countable {
  public:

    /**
     * Constructs an nRequestResponseContainer object
     *
     * @param *pEvent the synchronous request associated with this
     *            request-response container
     */
    nRequestResponseContainer(nSynchronous *pEvent);
    virtual ~nRequestResponseContainer(void);

    void clear ();

    /**
     * Gets the response associated with this request-response container
     *
     * @return an nEvent object specifying the response, if that has been
     *         received, null otherwise
     */
    nEvent* getResponse();

    /**
     * Gets the request associated with this request-response container
     *
     * @return an nSynchronous object specifying the request
     */
    nSynchronous* getRequest();

    /**
     * Sets the response associated with this request-response container
     *
     * @param *pEvent an nEvent object specifying the response
     */
    void setResponse(nEvent *pEvent);

    bool m_bClearIt;

  private:
    nSynchronous *m_pReq;
    int m_id;
    Poco::Thread *m_pThread;
    nEvent *m_pRes;

    friend class nSession;
};

}
}
}
}
