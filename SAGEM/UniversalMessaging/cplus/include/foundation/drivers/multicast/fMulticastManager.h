/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FMULTICASTMANAGER_H
#define FMULTICASTMANAGER_H

#include <fOutOfBandEventHandler.h>
#include <map>
#include "fEventInputStream.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fConnection;
}
namespace drivers {
class fAsyncReadListener;
namespace configuration {
class fMulticastConfig;
}
namespace multicast {
class fMulticastClient;

using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::drivers::configuration;
class fMulticastManager : public fOutOfBandEventHandler {

  private:
    static fMulticastManager* myManager;

    //  TLongObjectHashMap<fMulticastServer*> myServers;
    std::map<long,fMulticastClient*>* myClients;
    short uniqueStreamId;

    fMulticastManager();
    virtual ~fMulticastManager();


  public:
    static fMulticastManager* getInstance();
    static void shutdown();

    void handleRequest(fConnection* connection);

    // throws IOException, InvalidKeyException, NoSuchAlgorithmException, NoSuchPaddingException, InvalidAlgorithmParameterException
    fMulticastClient* createReceiver(short streamId, fMulticastConfig* config, fConnection* recoveryStream, fAsyncReadListener* listener);

    fMulticastClient* findReceiver(short streamId);

    void removeReceiver(short streamId);

    std::map<long,fMulticastClient*>::iterator getClients();

//  Iterator<fMulticastServer*> getServers();

    short getUniqueStreamId();

    void clearStream(fEventInputStream* stream, fConnection* connection);

};
}
}
}
}
}

#endif


