/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nInterface.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fSocketConfig;
}
}
}
namespace nirvana {
namespace nAdminAPI {

class nInterfaceManager;

using namespace com::pcbsys::foundation::drivers::configuration;

/**
 * Socket Interface class. This class exposes the current settings for a nsp
 * protocol adapter on the Nirvana Realm server. It is also used to construct a
 * new interface on the Realm server, however, the name is only valid when the
 * Realm server has added the interface.
 */
class DLL nSocketInterface :
    public nInterface {
  public:
    /**
     * Creates a new Socket Interface with the supplied values
     *
     * @param *pSock The fSocketConfig to use
     * @param *pIm The interface manager to use
     * @param autostart Specifies whether to autostart this interface
     */
    nSocketInterface(fSocketConfig *pSock, nInterfaceManager *pIm);
    nSocketInterface(const std::string& adapter, int port, bool autostart = true);
    virtual ~nSocketInterface(void);

    virtual int getType ();

  protected:
    nSocketInterface(const std::string& name, const std::string& protocol, const std::string& adapter, int port, bool autostart);
    fDriverConfig* convert();
    void convert(fSocketConfig *pCfg);

    friend class nInterfaceStatus;
};

}
}
}
}
