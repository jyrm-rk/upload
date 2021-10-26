/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"
#include "nPkgCloseListener.h"
#include "fBase.h"
#include "fSortedList.h"
#include <list>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fDriverConfig;
}
}
}
namespace nirvana {
namespace nbase {
class nBaseInterfaceStatus;
}
namespace nAdminAPI {

class nRealmNode;
class nInterfaceStatus;
class nInterfacePluginConfiguration;
class nInterface;
class nMulticastConfiguration;
class nMulticastManager;

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::drivers::configuration;
using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::foundation::collections;

/**
 * This class exposes the Realm Servers interface management API so that the control and management of the interfaces
 * can be performed by an authorised Administrator.
 */
class nInterfaceManager :
    public Observable, public nPkgCloseListener {
  public:

    virtual void addRef() {
        Observable::addRef();
    }

    virtual bool delRef() {
        return Observable::delRef();
    }

    /**
     * Creates a new nInterfaceManager
     *
     * @param *pNode the node to be associated with this Interface Manager
     */
    nInterfaceManager(nRealmNode *pNode);

    virtual ~nInterfaceManager(void);
    /**
     * Returns the type of this object, for internal use only.
     * @return the type of the object
     */
    virtual int getType();
    /**
     * Called when a realm node is closed, for internal use only
     * @param *pClose the node which has been closed
     */
    virtual void closed(nRealmNode *pClose);

    /**
     * Returns a list of nInterfacePluginConfiguration objects.
     * @see nInterfacePluginConfiguration
     * @return Vector
     */
    std::list<nInterfacePluginConfiguration*>& getPluginConfiguration();

    /**
     * Finds the nInterface object identified by the string supplied
     *
     * @param name null if the interface does not exist
     * @return an nInterfaceStatus object for the nInterface found or null of none could be found.
     * @exception nAdminIllegalArgumentException if null or a zero length string is passed as the name of the interface to be found
     */
    virtual nInterfaceStatus* findInterface(const std::string& name);

    /**
     * Returns an array of nInterfaceStatus objects that are currently configured on the Realm Server
     *
	 * @param numInterface[out]- contains the length of the returned array
     * @return an array of nInterfaceStatus objects
     * @see nInterfaceStatus
     */
    virtual nInterfaceStatus** getInterfaces(int& numInterface);

    /**
     * Adds a new interface to the Realm Server. If Autostart is set to true then the interface is also started
     *
     * @param newInterface The new interface configuration
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nUnexpectedResponseException   is thrown if the server responds with an unexpected protocol response
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException is thrown if null is passed as the interface to be added
     * @throws nAdminSecurityException        is thrown if used on a virtual realm
     * @throws nSessionPausedException        is thrown if session paused
     */
    virtual void addInterface(nInterface *pNewInterface);

    /**
     * Deletes an existing Interface from the Realm Server. All current connections on this interface are
     * disconnected immediatly.
     *
     * @param delInterface The interface to delete
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nUnexpectedResponseException   is thrown if the server responds with an unexpected protocol response
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException if null is passed as the interface to be added
     * @throws nAdminSecurityException        is thrown if used on a virtual realm
     * @throws nSessionPausedException        is thrown if session paused
     */
    virtual void delInterface(nInterface *pDelInterface);

    /**
     * Returns the number of NHP interfaces that are currently configured on the Realm Server
     *
     * @return a count of NHP interfaces
     */
    virtual int getNumberOfNHP();

    /**
     * Returns the number of NHPS interfaces that are currently configured on the Realm Server
     *
     * @return a count of NHPS interfaces
     */
    virtual int getNumberOfNHPS();

    /**
     * Returns the number of NSP interfaces that are currently configured on the Realm Server
     *
     * @return a count of NSP interfaces
     */
    virtual int getNumberOfNSP();

    /**
     * Returns the number of NSPS interfaces that are currently configured on the Realm Server
     *
     * @return a count of NSPS interfaces
     */
    virtual int getNumberOfNSPS();

    /**
     * Returns the number of SHM interfaces that are currently configured on the Realm Server
     *
     * @return a count of SHM interfaces
     */
    virtual int getNumberOfSHM();

    /**
     * Changes the existing interface so that it takes the new settings supplied.
     * This method will automatically start and stop the interface.
     * <p/>
     * Note : When this method is called in the interface that you are connected to, the interface will drop your connection and you will be either reconnected and this method will return or an Exception will be thrown.
     *
     * @param modInterface Changed settings for the interface
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nUnexpectedResponseException   is thrown if the server responds with an unexpected protocol response
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException if null is passed as the interface to be deleted
     * @throws nSessionPausedException        is thrown if session paused
     */
    virtual void modInterface(nInterface *pModInterface);

    /**
     * Starts the interface, specified in the nInterface object, on the Realm Server
     *
     * @param inter The interface to start
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException if null is passed as the interface to be started, or
     *                                        the interface specified can not be found
     */
    virtual void startInterface(nInterface *pInter);

    /**
     * Stops the specified interface on the Realm Server
     *
     * @param inter The interface to stop
     * @throws nSessionNotConnectedException  is thrown if the underlying session to perform the AdminAPI request is not connected
     * @throws nRequestTimedOutException      is thrown if the protocol request times out
     * @throws nAdminIllegalArgumentException if null is passed as the interface to be stopped, or the interface specified
     *                                        can not be found
     */
    virtual void stopInterface(nInterface *pInter);

    nMulticastManager* getMulticastManager();

  protected:
    virtual void loadInterfaces(const std::string& inter = "");
    virtual void addInterface(fDriverConfig *pCfg, int status);
    virtual void delInterface(fDriverConfig *pCfg);
    virtual void modInterface(fDriverConfig *pCfg, int status);
    virtual void reloadInterface(const std::string& name);
    virtual void update(std::list<nBaseInterfaceStatus*>& status);
    virtual void setACL(fDriverConfig *pDc);
    longlong m_timeout;

    nRealmNode *m_pRealm;

  private:
    static const std::string GRP_NAME;
    static const std::string GRP_VALUE;
    std::list<nInterfacePluginConfiguration*> m_configuredPlugins;
    fSortedList<std::string,nInterfaceStatus*>* myInterfaces;
    fSortedList<std::string,nMulticastConfiguration*>* myMulticastConfigurations;

    nMulticastManager* myMulticastManager;

    friend class nPkgAdminListener;
    friend class nPkgStatusListener;
    friend class Reload;
    friend class nInterface;
    friend class InterfaceStatusHandler;
    friend class nMulticastManager;
};

}
}
}
}
