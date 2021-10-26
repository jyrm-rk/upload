/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>
#include "fZone.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::fbase;


class nZone : public fZone
{
public:
	/**
     * Constructor for nZone.
     * Equivalent to Zone(zoneName, null)
     * @param zoneName: The name of the zone
     */
	nZone(std::string zoneName);

	 /**
     * Constructor for nZone.
     * @param zoneName: The name of the zone
     * @param uniqueIdentifier: Unique ID for this zone. If null, a unique ID will be generated for you.
     */
	nZone(std::string zoneName, std::string uniqueIdentifier);
	virtual ~nZone(void);
};

}
}
}
}