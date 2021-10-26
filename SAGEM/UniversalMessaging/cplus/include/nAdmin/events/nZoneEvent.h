/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fZone.h"
#include "nSynchronous.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {
namespace events {

using namespace com::pcbsys::nirvana::nbase::events;

class nZoneEvent :
	public nSynchronous
{
public:
	nZoneEvent(void);
	nZoneEvent(int command);
	nZoneEvent(int command, fZone* zone);
	nZoneEvent(int command, std::string zoneName, std::string uniqueIdentifier);
	virtual ~nZoneEvent(void);

    //class Object abstract method overrides
    virtual DLL int getType();

	//class fBaseEvent abstract method overrides
	virtual const std::string getTypeString();

	//class nEvent abstract method overrides
	virtual nEvent* createInstance();
	virtual void performRead(fEventInputStream *pIstream);
    virtual void performWrite(fEventOutputStream *pOstream);

	void setZoneName(std::string zoneName);
	std::string getZoneName();

	void setUniqueIdentifier(std::string uniqueIdentifier);
	std::string getUniqueIdentifier();

	int getCommand();


    static const int ZONE_GET = 0;
    static const int ZONE_SET = 1;
    static const int ZONE_REMOVE = 2;

protected:
	//ZONE_REPLACE is a server side event.
	//making this protected to bar end users from create one
	static const int ZONE_REPLACE = 3;

private:
	int m_command;
	std::string m_zoneName;
	std::string m_uniqueIdentifier;


};

}
}
}
}
}