/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NCREATERESULT_H
#define NCREATERESULT_H

#include "nResult.h"
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

/**
 * This class represents the results of the nSession.create(nChannelAttributes[]) call.
 *
 * This call returns an array of nCreateResult objects, each one represents the result of the call. The result will either be
 * an nChannel, nQueue or an Exception object
 *
 */
class nCreateResult : nResult {
    friend class nSession;

  public:
    /**
      *   Determine whether the create was successful for the specific nChannelAttributes object
      
      *   @return true if successful
      */
    DLL bool wasSuccessful();

    /**
     *   If !wasSuccessful(), this will return an Exception
     *   
     *   @return exception if the create was not successful
     */
    DLL nBaseClientException* getException();

    /**
     *   Was the result of the create an nQueue
     *   
     *   @return true if an nQueue was created 
     */
    DLL bool isQueue();

    /**
     *   Was the result of the create an nChannel
     *   
     *   @return true if an nChannel was created
     */
    DLL bool isChannel();

    /**
     *   If isChannel(), or !isQueue() this method will return the nChannel object created
     *   
     *   @return the nChannel object 
     */
    DLL nChannel* getChannel();

    /**
     *   If isQueue(), or !isChannel() this method will return the nQueue object created
     *   
     *   @return the nQueue object 
     */
    DLL nQueue* getQueue();

    /**
     *   Get the nChannelAttributes that was used in the create call
     *   
     *   @return the nChannelAttributes object 
     */
    DLL nChannelAttributes* getAttributes();

  protected:
    nCreateResult(nChannelAttributes* attr, nChannel* channel);

    nCreateResult(nChannelAttributes* attr, nQueue* queue);

    nCreateResult(nChannelAttributes* attr, nBaseClientException* exception);
};
}
}
}
}

#endif
