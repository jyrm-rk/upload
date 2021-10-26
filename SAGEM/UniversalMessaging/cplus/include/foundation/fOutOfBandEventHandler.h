/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FOUTOFBANDEVENTHANDLER_H
#define FOUTOFBANDEVENTHANDLER_H

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fConnection;

class fOutOfBandEventHandler {

  public:

    virtual void handleRequest(fConnection* connection)=0;

};
}
}
}
}
#endif
