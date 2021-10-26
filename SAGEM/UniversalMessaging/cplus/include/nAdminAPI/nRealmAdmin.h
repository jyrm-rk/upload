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
#include "nReconnectHandler.h"
#include "nAdminSession.h"

using namespace com::pcbsys::foundation::security;
using namespace com::pcbsys::foundation::collections;
using namespace com::pcbsys::nirvana::nbase;
using namespace com::pcbsys::nirvana::client;
using namespace com::pcbsys::nirvana::nAdmin;

namespace com {
namespace pcbsys {

namespace foundation {
namespace security {
class fAclList;
class fAclGroup;
class fAclEntry;
}
}

namespace nirvana {
namespace nbase {
class nSecureRealm;
}

namespace client {
class nSession;
class nSessionAttributes;
class nChannel;
class nChannelAttributes;
class nRealm;
class nQueue;
class nAbstractChannel;
class nReconnectHandler;
}

namespace nAdmin {
class nAdminSession;
}

namespace nAdminAPI {
class nACL;
class nACLEntry;
}
}

}
}

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
class nRealmAdmin {
  public:
    /**
    * Constructs a link with the realm server for admin operations
    *
    * @param sAttr nSessionAttributes representing the realm you wish to communicate with
    * @throws nBaseAdminException If the user is not authorised for admin functions
    */
    nRealmAdmin(nSessionAttributes* sAttr);

    /**
    * Constructs a link with the realm server for admin operations
    *
    * @param sAttr nSessionAttributes representing the realm you wish to communicate with
    * @param followMaster if set, this class will attempt to stay connected to the master realm
    * @throws nBaseAdminException If the user is not authorised for admin functions
    */
    nRealmAdmin(nSessionAttributes* sAttr, bool followMaster);

    /**
    * Constructs a link with the realm server for admin operations
    *
    * @param sAttr nSessionAttributes representing the realm you wish to communicate with
    * @param userName Username to use to login to the server
    * @throws nBaseAdminException If the user is not authorised for admin functions
    */
    nRealmAdmin(nSessionAttributes* sAttr, std::string userName);

    /**
    * Constructs a link with the realm server for admin operations
    *
    * @param sAttr nSessionAttributes representing the realm you wish to communicate with
    * @param userName Username to use to login to the server
    * @param followMaster if set, this class will attempt to stay connected to the master realm
    * @throws nBaseAdminException If the user is not authorised for admin functions
    */
    nRealmAdmin(nSessionAttributes* sAttr, std::string userName, bool followMaster);

    virtual ~nRealmAdmin();

    /**
    * Returns the nSession object for this nRealmAdmin
    *
    * @return The com.pcbsys.nirvana.client.nSession object
    * @see com.pcbsys.nirvana.client.nSession
    */
    virtual nSession* getSession();

    /**
    * Closes the session with the remote Realm
    */
    virtual void close();

    /**
    * Return the name of the Nirvana Realm Server currently connected to
    *
    * @return the name of the Nirvana Realm Server currently connected to
    */
    virtual std::string getConnectedRealmName();

    /**
    * If follow master has been set, then when the nRealmAdmin is disconnected, the underlying nSession will be set to the master realm when a new
    * master is elected after losing quorum. This method will determine whether the underlying nSession is actually connected to the master realm
    *
    * @return true when connected to the master realm, false if not
    */
    virtual bool isConnectedToMaster();

    /**
    * Creates a new channel on the realm this session is connected.
    * <p/>
    *
    * @param channelAttributes       The channel attributes object containing the parameters for
    *                   the new channel to be created
    * @param initialACL The initial ACLs to apply to the channel at creation time
    * @param initialEID The value to start the event id at
    * @param deadStore  The dead event store that will contain all purged, aged and dead events
    * @return an nChannel object representing the newly created nirvana channel
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    */
    virtual nChannel* createChannel(nChannelAttributes* channelAttributes, nACL* initialACL, long initialEID, nAbstractChannel* deadStore);

    /**
    * Creates a new channel on the realm this session is connected.
    * <p/>
    *
    * @param channelAttributes       The channel attributes object containing the parameters for
    *                   the new channel to be created
    * @param initialACL The initial ACLs to apply to the channel at creation time
    * @param initialEID The value to start the event id at
    * @return an nChannel object representing the newly created nirvana channel
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    */
    virtual nChannel* createChannel(nChannelAttributes* channelAttributes, nACL* initialACL, long initialEID);

    /**
    * Creates a new channel on the realm this session is connected.
    * <p/>
    *
    * @param channelAttributes       The channel attributes object containing the parameters for
    *                   the new channel to be created
    * @param initialACL The initial ACLs to apply to the channel at creation time
    * @return an nChannel object representing the newly created nirvana channel
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    */
    virtual nChannel* createChannel(nChannelAttributes* channelAttributes, nACL* initialACL);

    /**
    * Creates a new channel on the realm this session is connected.
    * <p/>
    *
    * @param channelAttributes       The channel attributes object containing the parameters for
    *                   the new channel to be created
    * @return an nChannel object representing the newly created nirvana channel
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    */
    virtual nChannel* createChannel(nChannelAttributes* channelAttributes);

    /**
    * Creates a new queue on the realm this session is connected.
    * <p/>
    *
    * @param queueAttributes       The channel attributes object containing the parameters for
    *                   the new queue to be created
    * @param initialACL The initial ACLs to apply to the queue at creation time
    * @param deadStore  The dead event store that will contain all purged, aged and dead events
    * @return an nQueue object representing the newly created nirvana queue
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    */
    virtual nQueue* createQueue(nChannelAttributes* queueAttributes, nACL* initialACL, nAbstractChannel* deadStore);

    /**
    * Creates a new queue on the realm this session is connected.
    * <p/>
    *
    * @param queueAttributes       The channel attributes object containing the parameters for
    *                   the new queue to be created
    * @param initialACL The initial ACLs to apply to the queue at creation time
    * @return an nQueue object representing the newly created nirvana queue
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    */
    virtual nQueue* createQueue(nChannelAttributes* queueAttributes, nACL* initialACL);

    /**
    * Creates a new queue on the realm this session is connected.
    * <p/>
    *
    * @param queueAttributes       The channel attributes object containing the parameters for
    *                   the new queue to be created
    * @return an nQueue object representing the newly created nirvana queue
    * @throws nUnknownRemoteRealmException   The remote realm responded with an unknown exception
    * @throws nSecurityException             User is not authorised for the function
    * @throws nChannelAlreadyExistsException The channel already exists
    * @throws nSessionNotConnectedException  Current session is not connected
    * @throws nUnexpectedResponseException   Internal Error has occurred, since we received a response from the server out of sequence
    * @throws nRequestTimedOutException      The server has not responded to the request in the timeout period
    * @throws nIllegalArgumentException      Illegal parameter, check the message for more information
    * @throws nSessionPausedException        The session is currently paused, please resume
    */
    virtual nQueue* createQueue(nChannelAttributes* queueAttributes);

    /**
    * Adds a specific acl entry to the realm acl
    *
    * @param entry An nACL entry containing the subject and permissions to add to the realm acl
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void addRealmACLEntry(nACLEntry* entry);

    /**
    * Adds a list of acl entries to the realm acl
    *
    * @param entry An nACL list containing the subjects and permissions to add to the realm acl
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void addRealmACLEntries(nACL* entry);

    /**
    * Removes a specific acl entry from the realm acl.
    *
    * @param entry An nACLEntry containing the subject and permissions to remove from the realm acl
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void removeRealmACLEntry(nACLEntry* entry);

    /**
    * Removes a list of acl entries from the realm acl.
    *
    * @param entry An nACL list containing the subjects and permissions to remove from the realm acl
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void removeRealmACLEntries(nACL* entry);

    /**
    * Modifies a specific acl entry's permissions in the realm acl.
    *
    * @param entry An nACLEntry containing the subject and permissions to modify in the realm node
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void modRealmACLEntry(nACLEntry* entry);

    /**
    * Modifies the acl entries in the list of realm acl entries.
    *
    * @param entry An nACL list containing the subjects and permissions to modify in the realm
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void modRealmACLEntries(nACL* entry);

    /**
    * Adds a specific acl entry to the channel or queue acl
    *
    * @param entry An nACL entry containing the subject and permissions to add to the channel or queue acl
    * @param chan   the channel or queue
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void addACLEntry(nACLEntry* entry, nAbstractChannel* chan);

    /**
    * Adds an ACL entry to all objects in an array of channels and / or queues
    *
    * @param entry the acl to apply
    * @param chans  the vector of channels and / or queues to apply the acl to
    * @throws nBaseAdminException
    */
    virtual void addACLEntry(nACLEntry* entry, std::vector<nAbstractChannel*>* chans);

    /**
    * Adds a list of acl entries to all objects in an array of channels and / or queues
    *
    * @param acl  the acl to apply
    * @param objs the channels and / or queues to apply the acl to
    * @throws nBaseAdminException
    */
    virtual void addACLEntries(nACL* entries, nAbstractChannel* chan);

    /**
    * Adds a list of acl entries to all objects in an array of channels and / or queues
    *
    * @param acl  the acl to apply
    * @param chans the vector of channels and / or queues to apply the acl to
    * @throws nBaseAdminException
    */
    virtual void addACLEntries(nACL* acl, std::vector<nAbstractChannel*>* chans);

    /**
    * Removes a ACL entry from the given channel or queue
    *
    * @param entry the ACL entry to apply
    * @param chan the channel or queue to apply the ACL to
    * @throws nBaseAdminException
    */
    virtual void removeACLEntry(nACLEntry* entry, nAbstractChannel* chan);

    /**
    * Removes an ACL entry from all objects in an vector of channels and / or queues
    *
    * @param entry  the acl to apply
    * @param chans the channels and / or queues to apply the acl to
    * @throws nBaseAdminException
    */
    virtual void removeACLEntry(nACLEntry* entry, std::vector<nAbstractChannel*>* chans);

    /**
    * Removes a list of ACL entries from the channel or queue acl.
    *
    * @param entries An nACL list containing the subjects and permissions to remove from the channel or queue acl
    * @param chan     the channel or queue
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void removeACLEntries(nACL* entries, nAbstractChannel* chan);

    /**
    * Removes a list of ACL entries from all objects in a vector of channels and / or queues
    *
    * @param entries  the acl to apply
    * @param chans the channels and / or queues to apply the acl to
    * @throws nBaseAdminException
    */
    virtual void removeACLEntries(nACL* entries, std::vector<nAbstractChannel*>* chans);

    /**
    * Modifies a specific acl entry's permissions in the channel or queue
    *
    * @param entry An nACL entry containing the subject and permissions to modify in the channel or queue ACL
    * @param chan the channel or queue to modify the ACL on
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void modACLEntry(nACLEntry* entry, nAbstractChannel* chan);

    /**
    * Adds a list of acl entries to all objects in a vector of channels and / or queues
    *
    * @param entry  the ACL entry to apply
    * @param chans the channels and / or queues to apply the acl to
    * @throws nBaseAdminException
    */
    virtual void modACLEntry(nACLEntry* entry, std::vector<nAbstractChannel*>* chans);

    /**
    * Modifies a list of acl entries in the channel or queue acl.
    *
    * @param entries An nACL list containing the subjects and permissions to remove from the channel or queue acl
    * @param chan    the channel or queue
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void modACLEntries(nACL* entries, nAbstractChannel* chan);


    /**
    * Modifies a list of acl entries for each object in a vector of channel and/or queues.
    *
    * @param entries An nACL list containing the subjects and permissions to remove from the channel or queue acl
    * @param chans the channels and / or queues to apply the acl to
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void modACLEntries(nACL* entries, std::vector<nAbstractChannel*>* chans);


    /**
    * Replaces the ACL on the Nirvana Realm with that which is passed in. This method is synchronous and will return once the operation
    * has been completed by the server or cluster.
    * <p/>
    * This method should be used with extreme caution. Unlike the nRealmNode, the nRealmAdmin does not maintain an up
    * to date image of the Realm ACL. This function will overwrite the acl at the server with the acl entries passed in.
    *
    * @param acl A nACL containing nRealmACLEntry
    * @throws nBaseAdminException If unable to successfully perform this operation, check the message for more information
    */
    virtual void setRealmACL(nACL* acl);

    /**
    * Returns the current ACL on the Nirvana Realm. This call makes a synchronous call to the realm to obtain the current acl list.
    *
    * @return The realm nACL
    * @throws nBaseAdminException If unable to successfully perform this operation, check the message for more information
    */
    virtual nACL* getRealmACL();

    /**
     * Returns a list of all ACL groups defined on the realm.
     *
     * @return A list of ACL groups
     * @exception nBaseClientException if the operation cannot be performed
     */
    virtual std::list<fAclGroup*>* getACLGroups();

    /**
    * Replaces the ACL on the Realm Server for this channel / queue with the acl list passed in. This will entirely replace the channel / queue acl
    * with the contents of the acl passed into the function.
    * <p/>
    * This method should be used with extreme caution. Unlike the nRealmNode, the nRealmAdmin does not maintain an up
    * to date image of any of the channel ACL lists. This function will overwrite the acl at the server for the specific channel / queue with the acl entries passed in.
    *
    * @param acl A nACL containing list of subjects and permissions
    * @param obj The channel or queue to set the acl on
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void setACL(nACL* acl, nAbstractChannel* chan);

    /**
    * Returns the current ACL for the specified channel or queue on the Nirvana Realm. This call makes a synchronous call to the realm to obtain the current acl.
    *
    * @param chan the channel or queue to obtain the current permissions for
    * @return The channel or queue nACL
    * @throws nBaseAdminException If unable to successfully perform this operation, check the message for more information
    */
    virtual nACL* getACL(nAbstractChannel* chan);

    /**
    * Commits the nACL object passed in with the Realm Server for the specified interface
    *
    * @param iface The name of the interface
    * @param acl   A nACL containing nInterfaceViaEntry objects
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual void setInterfaceACL(std::string iface, nACL* acl);

    /**
    * Returns the nACL object passed for the interface in question
    *
    * @param iface The name of the interface
    * @return An nACL containing nInterfaceViaEntry objects
    * @throws nBaseAdminException if unable to perform the operation, check the message for further information
    */
    virtual nACL* getInterfaceACL(std::string iface);

    /**
    * Add a session reconnect handler to the underlying admin session.
    *
    * @param handler - the nReconnectHandler object for the underlying admin session
    */
    virtual void addReconnectHandler(nReconnectHandler* handler);

  protected:
    static const Poco::SynchronizedObject sessionListLock;
    static fSortedList<std::string, nSession*>* mySessionList;
    static const Poco::SynchronizedObject realmListLock;
    static fSortedList<std::string, nRealm*>* myRealmList;

    nRealm* myRealm;
    nSecureRealm* myBaseRealm;
    std::vector<nReconnectHandler*>* reconnectHandlers;

    nAdminSession* mySession;
    std::string myUsername;
    std::string myName;
    std::string myMaster;

    nSessionAttributes* myAttr;

    bool isClosed;
    bool isAuthorised;
    bool _connectToMaster;

    virtual void create();
    virtual void connectToRealm();
    virtual nACL* convertToAdminAPI(fAclList* secureObject);
    virtual BitArray* convertLong(long priv);
    virtual void convertTofAclList(nACL* acls, fAclList* fAcls);
    virtual fAclEntry* convertTofAclList(nACLEntry* entry);
    virtual nAdminSession* createSession();
    virtual void connectToMaster(std::string master);
    virtual void connectToAll(std::string master);
    virtual nAdminSession* getMasterSession();

  private:
    void doClose();
    void cleanup();
    std::vector<fAclEntry*>* createAclList(nACL* acl);
    std::vector<std::string>* createNodeList(std::vector<nAbstractChannel*>* objs);

    class ReconnectHandler : public nReconnectHandler {
      public:
        ReconnectHandler(nRealmAdmin* admin);
        ~ReconnectHandler();

        virtual void disconnected(nSession* aSession);
        virtual void reconnected(nSession* aSession);
        virtual bool tryAgain(nSession* aSession);
      private:
        nRealmAdmin* myAdmin;
    };

    class RealmConnect {
      public:
        RealmConnect(nRealmAdmin* admin, nSecureRealm* realm, bool master);
        ~RealmConnect();
      private:
        nRealmAdmin* myAdmin;
        nRealm* myBRealm;
        bool connected;
        nSessionAttributes* mySAttr;
        bool isMaster;

        void connect();
    };
};
}
}
}
}
