/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "TransportContext.h"
#include <sstream>
#include <map>
#include <memory>



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Represents a Builder object which is used to create client or server TransportContexts
/// </summary>
/// <seealso cref= com::softwareag::umtransport::ClientTransportContext </seealso>
/// <seealso cref= com::softwareag::umtransport::ServerTransportContext </seealso>
class ContextBuilder {
  private:
    std::map<std::string, std::string> m_sortedQueryProperties;

  protected:
    ContextBuilder() {}
    virtual TransportContext *buildTransport() = 0;

  public:
    virtual ~ContextBuilder() {}

    void setQueryValue(std::string key, std::string value);
    std::string getQueryValue(const std::string& key);

  protected:
    /*
    	For every key name, we add "set" to the front of it to see if we can find the appropriate method to call, so if you want to
    	set the ReadBufferSize on a socket you add a

    	ReadBufferSize=1024000

    	To the query part of the URL and the code will then call

    	withReadBufferSize(int 1024000)

    	This allows us to update the contexts without editing this parser code, as long as we have get/set syntax
    */
    void parseQuery(const std::string &query);
};
}
}
}