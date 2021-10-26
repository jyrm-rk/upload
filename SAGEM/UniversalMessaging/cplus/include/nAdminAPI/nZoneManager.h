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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nZone;

class nZoneManager :
	public nPkgCloseListener
{
public:
	virtual ~nZoneManager(void);

	//Override for nPkgCloseListener::closed()
	DLL virtual void closed(nRealmNode *pClose);

    /**
     * Creates a new Zone object with the given name and a globally unique identifier. Zones may have the same name,
     * but different unique identifiers which differentiate them from each other.
     *
     * @param zoneName The String value for the Zone name.
     * @return A Zone object with the given name and a randomly generated unique identifier.
     */
	DLL static nZone* createZone(std::string zoneName);

	/**
     * Returns the zone that this realm is a member of, if any. Otherwise returns null.
     *
     * @return The Zone that this realm is a member of, if any. Otherwise returns null.
     */
	DLL nZone* getZone();

    /**
     * The Realm of this ZoneManager will attempt to join the given Zone. If the Realm is already a member of a Zone, or if
     * the Zone specified is not valid then this method will throw an Exception.
     *
     * @param zone The Zone to join.
     * @return True if joining the zone is successful.
     * @throws nAdminIllegalArgumentException If the Realm is already a member of another Zone then this exception will be thrown.
     * @throws nBaseClientException If there was some problem in applying the joinZone operation then this exception will be thrown.
     */
	DLL bool joinZone(nZone* zone);

	/**
     * The Realm of this ZoneManager will attempt to leave the given Zone. If the Realm is not a member of this Zone, or
     * if the Zone specified is not valid then this method will throw an Exception.
     *
     * @param zone The Zone to leave.
     * @return True is the Realm successfully leaves the given Zone. False if the operation was not attempted as the underlying connection is down
     * @throws nAdminIllegalArgumentException If the Realm is not a member of a Zone, or is a member of a different Zone then this exception will be thrown.
     * @throws nBaseClientException If there was some problem in applying the leaveZone operation then this exception will be thrown.
     */
	DLL bool leaveZone(nZone* zone);

private:
	nZoneManager(nRealmNode* pRealmNode);
	void reconnected();
	void setZone(nZone* pZone);
	void removeZone(nZone* zone);

private:
	nRealmNode* m_pRealm;
    nZone* m_pZone;
	
	//Made a friend declaration to give package level access of this class to nPkgAdminListener
	//equivalent of package/library level access in C# (internal) and Java (protected)
	friend class nPkgAdminListener;
	friend class nRealmNode;
};

}
}
}
}