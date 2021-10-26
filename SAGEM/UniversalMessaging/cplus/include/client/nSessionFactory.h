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

#include <string>
#include <list>

namespace Poco {
class Mutex;
}

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

class nSession;
class nSessionAttributes;
class nReconnectHandler;

/**
 * This class is used with a nSessionAttributes object to create a Nirvana session.
 */
class nSessionFactory {
  public:
    virtual ~nSessionFactory(void);

    /**
    * Creates an nSession object (Nirvana session) based on the nSessionAttributes object supplied
    *
    * @param *pAttr The nSessionAttributes object containing the parameters for the session to be created
    * @return the newly created nSession object
    *
    * @exception nIllegalArgumentException if the nSessionAttributes is invalid
    */
    static DLL nSession* create(nSessionAttributes *pAttr);

    /**
    * Creates an nSession object (Nirvana session) based on the nSessionAttributes object and
    * the specified reconnect handler.
    *
    * @param *pAttr The nSessionAttributes object containing the parameters for the session to be created
    * @param name The user name to be used by this session to authenticate
    * @return the newly created nSession object
    *
    * @exception nIllegalArgumentException if the nSessionAttributes is invalid or the username
    */
    static DLL nSession* create(nSessionAttributes *pAttr, std::string& name);

    /**
    * Creates an nSession object (Nirvana session) based on the nSessionAttributes object and
    * the specified reconnect handler.
    *
    * @param *pAttr The nSessionAttributes object containing the parameters for the session to be created
    * @param *pHandler A nReconnectHandler to use if the connection to the Server is lost
    * @return the newly created nSession object
    *
    * @exception nIllegalArgumentException if the nSessionAttributes is invalid
    */
    static DLL nSession* create(nSessionAttributes *pAttr, nReconnectHandler *pHandler);

    /**
    * Creates an nSession object (Nirvana session) based on the nSessionAttributes object and
    * the specified reconnect handler.
    *
    * @param *pAttr The nSessionAttributes object containing the parameters for the session to be created
    * @param *pHandler A nReconnectHandler to use if the connection to the Server is lost
    * @param userName A String token to use when authenticating with the server
    *
    * @return the newly created nSession object
    *
    * @exception nIllegalArgumentException if the nSessionAttributes is invalid
    *
    * @see nReconnectHandler
    */
    static DLL nSession* create(nSessionAttributes *pAttr, nReconnectHandler *pHandler,
                                std::string& userName);

    /**
    * Closes a Nirvana session
    *
    * @param *pSession The nSession object to be closed
    *
    * @exception nIllegalArgumentException if the nSession is invalid
    */
    static DLL void close(nSession *pSession);

    /**
    * Shuts down the session factory by closing all nirvana sessions that have
    * been created
    *
    */
    static DLL void shutdown(bool closeAllThreads = false);

    /**
    * Gets the number of nirvana sessions vended
    *
    * @return an int specifying the number of nirvana sessions vended with this
    * session factory
    */

    static DLL int getNoVended();

    /**
    * Creation of multiplexed session is not supported in C#/C++ API. A standard session is created instead
    * based on the nSessionAttributes object contained in the passed session and the supplied credentials
    *
    * @param pSession this session attributes will be used to create new standard session
    * @return new standard session
    * @deprecated Creation of multiplexed sessions is deprecated since 10.7 and will be removed in future releases. Standard
    * sessions should be used instead
    */
    static UM_DEPRECATED DLL nSession* createMultiplexed(nSession *pSession);

    /** 
    * Creation of multiplexed session is not supported in C#/C++ API. A standard session is created instead
    * based on the nSessionAttributes object
    * 
    * @param sessionAttributes the nSessionAttributes object containing the parameters for the session to be created
    * @return new standard session
    * @deprecated Creation of multiplexed sessions is deprecated since 10.7 and will be removed in future releases. Standard
    * sessions should be used instead
    */
    static UM_DEPRECATED DLL nSession* createMultiplexed(nSessionAttributes *sessionAttributes);

    /**
    * Creation of multiplexed session is not supported in C#/C++ API. A standard session is created instead
    * based on the nSessionAttributes object and the provided username
    * 
    * @param sessionAttributes the nSessionAttributes object containing the parameters for the session to be created
    * @param userName the user name to be used by this session to authenticate
    * @return new standard session
    * @deprecated Creation of multiplexed sessions is deprecated since 10.7 and will be removed in future releases. Standard
    * sessions should be used instead
    */
    static UM_DEPRECATED DLL nSession* createMultiplexed(nSessionAttributes *sessionAttributes, std::string userName);

  protected:
    nSessionFactory(void);
    static bool setupEnv();

    static std::list<nSession*> m_sessionList;
    static Poco::Mutex m_sessionListMutex;
    static bool m_sEnableMultiplexedSessions;
    static bool m_sSetup;
};

}
}
}
}
