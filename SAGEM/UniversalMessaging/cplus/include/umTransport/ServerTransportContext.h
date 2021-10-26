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
#include "fDriverConfig.h"
#include <string>

using namespace com::pcbsys::foundation::drivers::configuration;



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// Abstract class which defines methods common to all ServerTransportContexts
/// </summary>
/// <seealso cref= com::softwareag::umtransport::ServerSocketTransportContext </seealso>
/// <seealso cref= com::softwareag::umtransport::ServerSSLTransportContext </seealso>
/// <seealso cref= com::softwareag::umtransport::ServerRDMATransportContext </seealso>
/// <seealso cref= com::softwareag::umtransport::ServerSHMTransportContext </seealso>
class ServerTransportContext : public TransportContext {
  protected:
    virtual fDriverConfig *getConfig() = 0;
    DLL virtual void enableAsync();
    static void checkAdapter(const std::string &adapter);
  public:
    virtual ~ServerTransportContext() {}
    friend class TransportFactory;
};
}
}
}