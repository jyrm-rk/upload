/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NRESULT_H
#define NRESULT_H

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nBaseClientException;
class nChannel;
class nQueue;
class nChannelAttributes;

/*
* This class is the base class that represents the results of a batched find, create or delete call for channels or queues.
*/
class nResult {

    friend class nCreateResult;

  public:
    /**
     *   Determine whether the operation was successful for the specific object
     *   @return true if successful
     */
    bool wasSuccessful();

    /**
     *   If !wasSuccessful(), this will return an Exception
     *   @return exception if the operation was not successful 
     */
    nBaseClientException* getException();

    /**
     *   Was the result of the operation successfully performed on an nQueue
     *   @return true if the operation was performed on an nQueue 
     */
    bool isQueue();

    /**
     *   Was the result of the operation successfully performed on an nChannel
     *   @return true if the operation was performed on an nQueue 
     */
    bool isChannel();

    /**
     *   If isChannel(), or !isQueue() this method will return the nChannel object found
     *
     *   @returnthe nChannel object 
     */
    nChannel* getChannel();

    /**
    *   If isQueue(), or !isChannel() this method will return the nQueue object
    *
    *   @return the nQueue object
    */
    nQueue* getQueue();

    /**
    *   Get the nChannelAttributes that was used in the operation
    *   @return the nChannelAttributes object
    */
    nChannelAttributes* getAttributes();

    DLL ~nResult();

  protected:

    nChannelAttributes* myAttributes;
    nChannel* myChannel;
    nQueue* myQueue;
    nBaseClientException* myException;

    nResult(nChannelAttributes* attr);

    nResult(nChannelAttributes* attr, nChannel* channel);

    nResult(nChannelAttributes* attr, nQueue* queue);

    nResult(nChannelAttributes* attr, nBaseClientException* exception);

};
}
}
}
}

#endif

