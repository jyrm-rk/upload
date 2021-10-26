/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NMULTICASTMANAGER_H
#define NMULTICASTMANAGER_H

#include <vector>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fMulticastConfig;
}
}
}
namespace nirvana {
namespace nAdminAPI {
using namespace com::pcbsys::foundation::drivers::configuration;

class nInterfaceManager;
class nMulticastConfiguration;

class nMulticastManager {

  private:
    const nInterfaceManager* myInterfaceManager;

  protected:
    nMulticastManager(const nInterfaceManager* im);

    void updateInfo(fMulticastConfig* cfg);

    //void callNotify(Object obj);


  public:
    /**
    * Returns a vector of nMulticastConfiguration objects that are currently configured on the Realm Server
    *
    * @return a vector of nMulticastConfiguration objects
    */
    std::vector<nMulticastConfiguration*> getMulticastConfigurations();


    /**
       * Adds a new multicast configuration to the Realm Server. If Autostart is set to true then the interface is also started
       *
       * @param newConfiguration The new multicast configuration
       * @throws com.pcbsys.nirvana.client.nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
       * @throws com.pcbsys.nirvana.client.nUnexpectedResponseException   is thrown if the server responds with an unexpected protocol response
       * @throws com.pcbsys.nirvana.client.nRequestTimedOutException      is thrown if the protocol request times out
       * @throws nAdminIllegalArgumentException is thrown if null is passed as the interface to be added
       * @throws nAdminSecurityException        is thrown if used on a virtual realm
       * @throws com.pcbsys.nirvana.client.nSessionPausedException        is thrown if session paused
       */
    void addMulticastConfiguration(nMulticastConfiguration* newConfiguration);

    /**
       * Deletes an existing multicast configuration from the Realm Server.
       *
       * @param delConfiguration The configuration to delete
       * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
       * @throws nUnexpectedResponseException   is thrown if the server responds with an unexpected protocol response
       * @throws nRequestTimedOutException      is thrown if the protocol request times out
       * @throws nAdminIllegalArgumentException if null is passed as the interface to be added
       * @throws nAdminSecurityException        is thrown if used on a virtual realm
       * @throws nSessionPausedException        is thrown if session paused
       */
    void delMulticastConfiguration(nMulticastConfiguration* delConfiguration);

    /**
     * Changes the existing multicast configuration so that it takes the new settings supplied.
     *
     * @param modMulticastConfiguration Changed the multicast configuration
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nUnexpectedResponseException   is thrown if the server responds with an unexpected protocol response
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException if null is passed as the interface to be deleted
     * @throws nSessionPausedException        is thrown if session paused
     */
    void modifyMulticastConfiguration(nMulticastConfiguration* modMulticastConfiguration);

    /**
     * Returns the number of multicast configurations that are currently on the Realm Server
     *
     * @return a count of multicast configurations
     */
    int getNumberOfConfigurations();

    /**
     * Finds the nMulticastConfiguration object identified by the string supplied
     *
     * @param name to find
     * @return an nMulticastConfiguration object for the configuration found or null of none could be found.
     * @throws nAdminIllegalArgumentException if null or a zero length string is passed as the name of the configuration to be found
     */
    nMulticastConfiguration* findInterface(std::string name);

    /**
     * Disables the specified configuration on the Realm Server
     *
     * @param config The configuration to disable
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException if null is passed as the configuration to be disabled, or the configuration specified can not be found
     * @throws nSessionPausedException        if session is paused
     */
    void disableConfiguration(nMulticastConfiguration* config);

    /**
     * Enables the configuration, specified in the nMulticastConfiguration object, on the Realm Server
     *
     * @param config The configuration to enable
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException if null is passed as the configuration to be enabled, or the configuration specified can not be found
     */
    void enableConfiguration(nMulticastConfiguration* config);

    friend class nInterfaceManager;

};
}
}
}
}

#endif

