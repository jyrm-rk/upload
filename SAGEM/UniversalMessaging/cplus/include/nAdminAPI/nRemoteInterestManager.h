/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "nPkgCloseListener.h"
#include <string>
#include "Poco/SynchronizedObject.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {
class nRemoteInterestEntry;
}
namespace nAdminAPI {

class nLeafNode;
using namespace com::pcbsys::nirvana::nAdmin;

class nRemoteInterestManager:
	public nPkgCloseListener
{
public:
	virtual ~nRemoteInterestManager(void);

	/**
	 * Called when the nRealmNode is closed, for internal use only.
	 *
	 * @param close The nRealmNode which has been closed.
	 */
	DLL virtual void closed(nRealmNode *pClose);

	/**
	 * Adds a single remote interest entry to the realm to enable sending and receiving of messages between different realms.
	 * Adding an entry with the canSend and canReceive properties of the entry as false is the same as removing the entry from the realm.
	 *
	 * @param entry the entry to add to the realm server
	 * @throws nAdminIllegalArgumentException if the given channelName does not represent a channel, this exception is thrown
	 * @throws nBaseClientException if there was some problem with adding the entry to the realm server, this exception is thrown
	 */
	DLL void add(nRemoteInterestEntry* pEntry);
	/**
	 * Adds a new remote interest entry with the given name, send and receive properties.
	 * Adding an entry with the canSend and canReceive properties of the entry as false is the same as removing the entry from the realm.
	 * @param channelName the name of the channel
	 * @param canSend if the channel can send events to other realms connected to its parent realm
	 * @param canReceive if the channel can receive events from other realms connected to its parent realm
	 * @throws nBaseClientException if there was some problem with adding the entry to the realm server, this exception is thrown
	 * @throws nAdminIllegalArgumentException if the given channelName does not represent a channel, this exception is thrown
	 */
	DLL void add(std::string channelName, bool canSend, bool canReceive);

	/**
	 * Adds a collection of remote interest entries to the realm to enable sending and receiving of messages between realms.
	 * This is a composite operation, if one entry would fail being added to the realm in question, then no entry is added.
	 * Adding an entry with the canSend and canReceive parameters of false is the same as performing a remove operation.
	 * @param entries the collection of entries to add to the realm server
	 * @throws nAdminIllegalArgumentException if the given channelName of any entry does not represent a channel, this exception is thrown
	 * @throws nBaseClientException if there was some problem with adding the entries to the realm server, this exception is thrown
	 */
	DLL void add(std::list<nRemoteInterestEntry*> entries);
	/**
	 * Removes a single entry from the realm, disabling sending and receiving of messages if previously enabled.
	 * The canSend and canReceive values of the entry have no effect on the outcome of this operation.
	 * @param entry the entry to remove interest propagation from the realm for
	 * @throws nAdminIllegalArgumentException if the given channelName contained within the entry does not represent a channel, this exception is thrown
	 * @throws nBaseClientException if there was some problem removing the entry from the server, this exception is thrown.
	 */
	DLL void remove(nRemoteInterestEntry* pEntry);
	/**
	 * Removes a single entry from the realm, disabling sending and receiving of messages if previously enabled.
	 * @param channelName the name of the channel to remove interest propagation from
	 * @throws nAdminIllegalArgumentException if the given channelName does not represent a channel, this exception is thrown
	 * @throws nBaseClientException if there was some problem removing the entry from the server, this exception is thrown
	 */
	DLL void remove(std::string channelName);
	/**
	 * Removes a collection of entries from the realm, disabling sending and receiving of messages if previously enabled.
	 * This operation is composite, if removing one entry from the realm would result in failure then all entries will remain attached to the realm.
	 * The canSend and canReceive values of any entry in the collection have no effect on the outcome of this operation.
	 * @param entries the collection of entries to remove interest propagation from the realm for
	 * @throws nAdminIllegalArgumentException if any of the given entries to not contain a channelName which represents a channel, this exception is thrown
	 * @throws nBaseClientException if there was some problem removing the entries from the server, this exception is thrown.
	 */
	DLL void remove(std::list<nRemoteInterestEntry*> entries);
	/**
	 * Queries whether a given leaf node has the ability to propagate messages to other realms its parent realm is connected to
	 * @param channelNode the given leaf node to test
	 * @return returns true if the given leaf node will propagate messages to other realms, providing the correct canReceive value is set on them. It returns false if there is no interest entry for this realm or if the sending flag is explicitly disabled for this leaf node.
	 */
	DLL bool canSend(nLeafNode* channelNode);
	/**
	 * Queries whether a given leaf node has the ability to receive propagated messages from other realms.
	 * @param channelNode the given leaf node to test
	 * @return returns true if the given leaf node will receive messages from other realms, providing the correct canSend value is set on them. It returns false if there is no interest entry for this leaf node or if the receipt flag is explicitly set to false.
	 */
	DLL bool canReceive(nLeafNode* channelNode);
protected:
	nRemoteInterestManager(nRealmNode* pRealmNode);

	void del(std::list<nRemoteInterestEntry*>& entries);
	void del(std::string& channelName);
	void update(std::list<nRemoteInterestEntry*>& entries);
	void update(std::string& channelName, bool canSend, bool canReceive);
private:
	nRealmNode* m_pRealm;
	std::map<std::string, nRemoteInterestEntry*> m_channelEntries;
	Poco::Mutex m_channelEntriestMutex;
	bool m_bisClosed;

	//Made a friend declaration to give package level access of this class to nPkgAdminListener
	//equivalent of package/library level access in C# (internal) and Java (protected)
	friend class nPkgAdminListener;
	friend class nRealmNode;
};
}
}
}
}