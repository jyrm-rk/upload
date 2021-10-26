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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nChannelAttributes;
class nChannel;
class nQueue;
class nBaseClientException;

/**
 * This class represents the results of the nSession.find(nChannelAttributes[]) call.
 *
 * This call returns an array of nFindResult objects, each one represents the result of the call. The result will either be
 * an nChannel, nQueue or an Exception obhect
 *
 * @since 6.0
 */
class nFindResult {
  public:
    virtual ~nFindResult(void);
    /**
     * Determine whether the find was successful for the specific nChannelAttributes object
     *
     * @return true if successful
     */
    virtual bool wasSuccessful();
    /**
     * If !wasSuccessful(), this will return an Exception
     *
     * @return exception if the find was not successful
     */
    virtual nBaseClientException* getException();
    /**
     * Was the result of the find an nQueue
     *
     * @return true if an nQueue was found
     */
    virtual bool isQueue();
    /**
     * Was the result of the find an nChannel
     *
     * @return true if an nChannel was found
     */
    virtual bool isChannel();
    /**
     * If isChannel(), or !isQueue() this method will return the nChannel object found
     *
     * @return the nChannel object
     */
    virtual nChannel* getChannel();
    /**
     * If isQueue(), or !isChannel() this method will return the nQueue object found
     *
     * @return the nQueue object
     */
    virtual nQueue* getQueue();
    /**
      * Get the nChannelAttributes that was used in the find call
      *
      * @return the nChannelAttributes object
      */
    virtual nChannelAttributes* getAttributes();

  protected:
    nFindResult(nChannelAttributes *pAttr, nChannel *pChannel);
    nFindResult(nChannelAttributes *pAttr, nQueue *pQueue);
    nFindResult(nChannelAttributes *pAttr, nBaseClientException *pException);

  private:
    nChannelAttributes *m_pAttributes;
    nChannel *m_pChannel;
    nQueue *m_pQueue;
    nBaseClientException *m_pException;

    friend class nSession;
};

}
}
}
}
