/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */

#ifndef __fSSLServerSocketDriver__
#define __fSSLServerSocketDriver__

#include "fServerSocketDriver.h"
#include "fDriverConfig.h"
#include "fAcceptHandler.h"
#include "Poco/Net/Context.h"
#include "fSSLExtendedConfig.h"
#include "Poco/Net/SecureStreamSocket.h"

#include <stdio.h>
namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
                
class fSSLServerSocketDriver : public fServerSocketDriver{
    
public:
    
    fSSLServerSocketDriver(com::pcbsys::foundation::drivers::configuration::fDriverConfig* config, com::pcbsys::foundation::drivers::handlers::fAcceptHandler* aHandler, const std::string& alias);
    virtual ~fSSLServerSocketDriver();
    virtual void initialise();

    virtual bool validate(fDriver* driver);

protected:
    
    virtual void createServerSocket(configuration::fDriverConfig* cfg);
    virtual fDriver* createDriver(const Poco::Net::SecureStreamSocket& socket);
    virtual fDriver* performAccept();
    
};
}
}
}
}

#endif /* defined(__fSSLServerSocketDriver__) */
