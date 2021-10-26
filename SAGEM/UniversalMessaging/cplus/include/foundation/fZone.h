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
#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fZone
{
protected:
	std::string m_zoneName;
	std::string m_uniqueIdentifier;

public:
	fZone(std::string zoneName);
	fZone(std::string zoneName, std::string uniqueIdentifier);
	virtual ~fZone(void);

	DLL std::string getName();
	std::string getUniqueIdentifier();
	DLL bool Equals(fZone* pZone);
	DLL bool operator==(const fZone& objZone) const;
};

}
}
}
}