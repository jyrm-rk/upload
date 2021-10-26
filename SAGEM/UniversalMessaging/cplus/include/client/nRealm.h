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

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fConnectionDetails;
}
}
namespace nirvana {
namespace nbase {
class nBaseRealm;
}
namespace client {
using namespace nbase;
using namespace foundation::drivers;

/**
 * This class represents a nirvana Realm
 */
class nRealm {
  public:

    virtual ~nRealm(void);

    /**
    * Constructs a new nRealm object
    * @exception nIllegalArgumentException if the parameters are invalid, refer to the exception message for more information
    */
    nRealm(void);

    /**
    * Constructs a new nRealm object with the specified name and collection of network interfaces
    *
    * @param name A string specifying the realm's name
    * @param pConnections An array of strings specifying the realm's network interfaces.
    * @param nConnection length of the pConnections array
    * These have to be in the form: protocol://host:port/servlet File , where:
    *
    * Protocol can be one of nsp, nhp, nsps, nhps where:
    *
    * nsp => Nirvana Socket Protocol
    * nhp => Nirvana HTTP Protocol
    * nsps => Nirvana Socket Protocol Secure (Socket protocol over SSL/TLS)
    * nhps => Nirvana HTTP Protocol Secure (HTTP protocol over SSL/TLS)
    *
    * Host is the host the realm is running on
    *
    * Port is the port the realm is listening on
    *
    * servlet File specifies the location that servlets are mapped if talking to
    * the realm via a web server (e.g. in a DMZ environment)
    *
    * @exception nIllegalArgumentException if the parameters are invalid, refer to the exception message for more information
    */

    DLL nRealm(std::string name, std::string *pConnections, int nConnection);

    /**
    * Gets the collection of the network interfaces this realm listens in.
    *
    * @return A list containing an Strings of rnames for each realm interface.
    */

    DLL std::list<std::string>* getConnections();


    /**
    * Returns the relative name of the realm within the namespace
    *
    * @return String mount point name
    */

    DLL const std::string getMountPoint();

    /**
    * Gets the name of this realm
    *
    * @return A string specifying the name of this realm
    */

    DLL std::string getName();

    /**
    * Returns an array of Strings with the rnames for this realm
    *
    * @return the Protocols, or rnames, supported by this realm
    */

    DLL std::string* getProtocols(int& nString);

    /**
    * Sets the relative name for the realm within the namespace
    *
    * @param mountPoint the name to add this realm in the namespace
    *
    * @exception nIllegalArgumentException Illegal parameter, check the message for more information
    */

    DLL void setMountPoint(const std::string& mountPoint);

    /**
    * Sets the name on this realm
    *
    * @param data a string specifying the name of this realm
    *
    * @exception nIllegalArgumentException Illegal parameter, check the message for more information
    */

    DLL void setName(std::string data);

    /**
     * Constructs a new nRealm object with the specified name and collection of network interfaces
     *
     * @param name A string specifying the realm's name
     * @param connections A list of fConnectionDetails objects. These are created
     * using strings specifying the realm's network interfaces.
     * The strings have to be in the form: protocol://host:port/servlet File , where:
     * Protocol can be one of nsp, nhp, nsps, nhps where:
     *
     * nsp => Nirvana Socket Protocol
     * nhp => Nirvana HTTP Protocol
     * nsps => Nirvana Socket Protocol Secure (Socket protocol over SSL/TLS)
     * nhps => Nirvana HTTP Protocol Secure (HTTP protocol over SSL/TLS)
     *
     * Host is the host the realm is running on
     *
     * Port is the port the realm is listening on
     *
     * servlet File specifies the location that servlets are mapped if talking to
     * the realm via a web server (e.g. in a DMZ environment)
     *
     * @exception nIllegalArgumentException if the parameters are invalid, refer to the exception message for more information
     */
    nRealm(std::string name, std::list<fConnectionDetails*> connections);

  private:
    nRealm(nBaseRealm *pRealm);
    nBaseRealm *m_pRealm;
    nBaseRealm* getRealm();

    friend class nSession;
    friend class nChannelAttributes;
};

}
}
}
}
