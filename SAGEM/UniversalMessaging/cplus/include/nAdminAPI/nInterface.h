/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fSortedList.h"
#include "fBase.h"
#include "Poco/SynchronizedObject.h"
#include <stdio.h>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {
class fAclEntry;
class fAclList;
}
namespace drivers {
namespace configuration {
class fDriverConfig;
}
}
}
namespace nirvana {
namespace nAdminAPI {

class nInterfaceManager;
class nACL;
class nACLEntry;

using namespace foundation::drivers::configuration;
using namespace foundation::collections;
using namespace foundation::fbase;
using namespace foundation::security;

/**
 * Abstract Class nInterface. This class exposes the common attributes to
 * all Nirvana Realm interfaces.
 */
class nInterface : public Poco::SynchronizedObject {
  public:

    nInterface() {}
    /**
     * Creates a new nInterface object from the supplied fDriverConfig and nInterfaceManager
     *
     * @param *pCfg the fDriverConfig associated with this interface
     * @param *pIm the Interface Manager for this interface
     */
    nInterface(fDriverConfig *pCfg, nInterfaceManager *pIm);


    virtual ~nInterface();

    /**
     * Get the name of this interface. This is the unique name for this interface on the realm
     *
     * @return String name of the interface
     */
    virtual const std::string& getName();

    /**
     * Retrieves the interfaces Via list. This list is contained in a nACL object.
     *
     * @see nACL
     * @return nACL
     */
    virtual nACL* getViaList();

    /**
     * Returns whether this interface is allowed to be used in inter realm / cluster communication
     *
     * @return whether this interface is allowed for cluster communication
     */
    virtual bool isInterRealmAllow();

    /**
     * Will this interface be used by other realms to send client redirects to.
     *
     * @return true if this interface can send redirects
     */
    bool canAdvertise();
    bool Equals(longlong aLong);

    /**
     * Compares the name of this interface with the string parameter
     *
     * @param item the string name to compare to this interface name
     * @return true if these names match
     */
    virtual bool Equals(const std::string& item);

    /**
     * Compares this nInterface object with another object.
     *
     * @param an nInterface object
     * @return true if these objects are equal.
     */
    virtual bool Equals(nInterface *pItem);

    /**
     * Returns the interfaces known alias's.
     *
     * This is used by the server to tell other servers how to contact it if it is behind a NAT or Proxy server. It is
     * specified as a HOST:PORT syntax
     *
     * @return String alias
     */
    virtual const std::string& getAdapaterAlias();

    /**
     * Get the adapter that this interface will use. Reserved interfaces are
     *
     * 0.0.0.0 - Bind to all physical interfaces on the machine
     * 127.0.0.1 - Bind to local loopback
     *
     * @return The current interface
     */
    virtual const std::string& getAdapter();

    /**
     * Returns the number of milliseconds that the remote client has to authenticate with the server before
     * the server closes the communications with the client.
     *
     * @return The current timeout
     */
    virtual int getAuthTimeOut();

    /**
     * The number of socket connect requests that the Operating System will queue before
     * sending a reject to the remote client.
     *
     * @return The current setting
     */
    virtual int getBacklog();

    /**
     * Get the port that this interface will bind to at startup
     *
     * @return Integer value of the port
     */
    virtual int getPort();

    /**
     * Returns the protocol string used by this interface. Can be one of nsp, nsps, nhps or nhp
     *
     * @return The protocol used by this interface
     */
    virtual const std::string& getProtocol();

    /**
     * Return the socket buffer size in bytes used by this interface when receiving data
     *
     * @return the inbound socket buffer size in bytes used by this interface
     */
    virtual int getRecvBufferSize();

    /**
     * Returns the number of select threads used by NIO
     *
     * @return the number of select threads used
     */
    virtual int getSelectThreadSize();

    /**
     * Return the socket buffer size in bytes used by this interface when sending data
     *
     * @return the outbound socket buffer size in bytes used by this interface
     */
    virtual int getSendBufferSize();

    /**
     * Returns the current Thread Pool size that handles client socket connections. Depending on the
     * number of connections/second this size should be around 1 or 2 anything more may not really gain
     * any improvement
     *
     * @return The current size
     */
    virtual int getThreadCount();

    /**
     * Get the URL that specifies this interface. It is made up from the protocol
     * the adapter and port
     *
     * @return URL string
     */
    virtual std::string getURL();

    /**
     * Returns whether NIO is enabled on this interface
     *
     * @return if NIO is enabled
     */
    virtual bool isAllowNIO();

    /**
     * Returns whether this interface can be used by clients to connect
     *
     * @return whether this interface is allowed for client communication
     */
    virtual bool isClientConnectionsAllowed();

    virtual bool lessThan(longlong aLong);
    virtual bool lessThan(const std::string& item);
    virtual bool lessThan(nInterface *pItem);

    /**
     * Sets the interfaces alias.
     *
     * This string is of the format HOST:PORT where HOST is the alias interface and port is the number used to communicate with
     * the server.
     *
     * @param alias an alias hostname for the interface
     */
    virtual void setAdapterAlias(const std::string& alias);

    /**
     * Change the current advertise status for this interface
     *
     * @param flag True or False
     */
    virtual void setAdvertise(bool flag);

    /**
     * Sets whether this interface can accept client connections or not
     *
     * @param clientconnections whether this interface can be used by clients
     */
    virtual void setAllowClientConnections(bool clientconnections);

    /**
     * Set whether NIO is enabled on the interface
     *
     * @param allowNIO whether NIO is enabled
     */
    virtual void setAllowNIO(bool allowNIO);

    /**
     * Changes the number of milliseconds that the remote client has to authenticate with the server.
     *
     * @param timeout time in milliseconds
     */
    virtual void setAuthTimeOut(int timeout);

    /**
     * Change the current Autostart status for this interface
     *
     * @param flag True or False
     */
    virtual void setAutostart(bool flag);

    /**
     * Changes the number of connections to queue before the Operating System will send rejects
     * to the remote client
     *
     * @param backlog Must be between 1 and 100
     */
    virtual void setBacklog(int backlog);

    /**
    * Sets whether this interface is allowed to be used in inter realm / cluster communication
    *
    * @param interealmAllow whether this interface is allowed for cluster commincation
    */
    virtual void setInterRealmAllow(bool interealmAllow);

    /**
     * Set the Interface Manager
     *
     * @param pIm the interface manager to use
     */
    virtual void setManager(nInterfaceManager *pIm);

    /**
     * Set the socket buffer size in bytes used by this interface when receiving data
     *
     * @param recvBufferSize the inbound socket buffer size in bytes used by this interface
     */
    virtual void setRecvBufferSize(int recvBufferSize);

    /**
     * Sets the number of select threads used by NIO
     *
     * @param selectThreadSize the number of select threads used
     */
    virtual void setSelectThreadSize(int selectThreadSize);

    /**
     * Set the socket buffer size in bytes used by this interface when sending data
     *
     * @param sendBufferSize the size to set the outbound buffer size to
     */
    virtual void setSendBufferSize(int sendBufferSize);

    /**
     * Changes the thread pool size handling the client connections
     *
     * @param count Must be between 1 and 5 inclussive
     */
    virtual void setThreadCount(int count);

    /**
     * Commits the nACL object passed in with the Realm Server. This causes these nInterfaceViaEntry to be active once the function
     * returns. The nACL object can be retrieved by calling the getViaList() function which returns the interface
     * current VIA list.
     *
     * @param pAcl A nACL containing nInterfaceViaEntry
     * @exception nInsufficientPrivilegesException
     *                             If the user is not permissioned to perform this operation
     * @exception nNodeException      if the ACLs being set are invalid
     * @exception nBaseAdminException if unable to perform the operation, check the message for further information
     */
    virtual void setViaList(nACL *pAcl);

    /**
     * Return a string representation of the interface details
     *
     * @return a string representation of the interface details
     */
    virtual std::string toString();

    /**
    * Will this interface automatically be started when the Realm Server starts
    *
    * @return true if the interface will automatically start
    */
    virtual bool willAutostart();


    virtual int getType() = 0;

    static const int SOCKETINTERFACE = 1;
    static const int SSLINTERFACE = 2;
    static const int HTTPINTERFACE = 3;
    static const int HTTPSINTERFACE = 4;
    static const int SHMINTERFACE = 5;

  protected:
    nInterface(const std::string& name, const std::string& protocol, const std::string& adapter, int port, bool autoStart = true);
    virtual nACL* convertToAdminAPI(fAclList* vec);
    virtual BitArray* convertLong(longlong priv);
    virtual nACLEntry* createACLEntry(const std::string& subject, BitArray *pBs);
    virtual void convert(fDriverConfig *pCfg);
    virtual longlong convertBitMap(BitArray *pBs);
    virtual void convertTofAclList(nACL *pAcls, fAclList* fAcls);
    virtual fDriverConfig* convert() = 0;

    std::string m_name;
    std::string m_protocol;
    bool m_bAutoStart;
    bool m_bAdvertise;
    std::string m_adapter;
    int m_port;
    int m_poolSize;
    int m_backlog;
    int m_authTimeOut;

  private:
    int compare(const std::string& test);

    nACL *m_pACLs;
    nInterfaceManager *m_pManager;
    std::string m_alias;
    int m_recvBufferSize;
    int m_sendBufferSize;
    bool m_bAllowForInterRealmComms;
    bool m_bAllowClientConnections;
    bool m_bAllowNIO;
    int m_selectThreadSize;

    friend class nPkgAdminListener;
    friend class nInterfaceManager;
};

}
}
}
}
