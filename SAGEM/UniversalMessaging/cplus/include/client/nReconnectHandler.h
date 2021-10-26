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

class nSession;

/**
 * This interface should be implemented by classes wishing to register to receive
 * callbacks when sessions are disconnected or to take control over the reconnect logic
 */
class nReconnectHandler {
  public:
    DLL nReconnectHandler(void);
    virtual DLL ~nReconnectHandler(void);

    /**
    * This method is called asynchronously when a session is disconnected
    *
    * @param *pSession The session that got disconnected
    */
    virtual DLL void disconnected(nSession *pSession) = 0;

    /**
    * This method is called asynchronously between a session being disconnected
    * and a reconnection attempt. If you wish to use the default reconnect logic,
    * simply return true. If not return false and implement your own custom reconnect logic.
    *
    * @param *pSession The session to try and reconnect
    * @return a bool specifying whether the default reconnect logic should be used
    * or not.
    */
    virtual DLL bool tryAgain(nSession *pSession) = 0;

    /**
    * This method is called asynchronously when a session is reconnected
    *
    * @param *pSession The session that got reconnected
    */
    virtual DLL void reconnected(nSession *pSession) = 0;
};

}
}
}
}

