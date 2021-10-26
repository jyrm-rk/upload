/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "ServerTransportContext.h"
#include <string>
#include <memory>



namespace com {
namespace softwareag {
namespace umtransport {

/**
* <summary>
* This factory allows you to construct ServerContextBuilders and therefore ServerTransportContexts
* by passing a String URL.  This way you can compile an application which is Transport agnostic
* and simply change the URL passed to the application to switch from SHM to Sockets etc.
* A URL is of the form protocol://host:port?Property=value&Property2=value2
* The relevant ServerContextBuilder will be constructed based on the protocol and then the properties
* will be set internally. So on a ServerSocketTransportContext there is a property called "WriteBufferSize"
* that you could set to 150000 using a URL like this:
*   \code
*     std::string url = "tcp://localhost:8080?WriteBufferSize=150000";
*     ServerTransportContext *context = ServerTransportContextFactory::build(url);
*  \endcode
*  Please note that the method is "withWriteBufferSize" but you should pass "WriteBufferSize" to the query string
* </summary>
*/

class UMTRANSPORTDLL ServerTransportContextFactory {

  public:
    /**
    * <summary>
    * Creates a ServerContextBuilder based on the protocol in the url and sets the host/port (the port is a
    * file path in SHM) as well as any other parameters which are passed in the url query string.
    * For example you can construct a ServerSocketTransportContext like this:
    * \code
    * ServerTransportContext *context = ServerTransportContextFactory::build("tcp://locahost:9000"); </summary>
    * <param name="ur"> protocol://host:port?property1=value provides the required information to construct a ServerContextBuilder </param>
    * <returns> a ServerTransportContext and then a Transport using the TransportFactory </returns>
    */
    static std::unique_ptr<ServerTransportContext> build(const std::string &url);

  protected:
    virtual ServerTransportContext *parse(URL *url) = 0;
    virtual fDriverConfig *getConfig() = 0;
    virtual void enableAsync();
};
}
}
}