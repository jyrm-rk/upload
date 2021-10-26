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
namespace nirvana {
namespace nbase {

class nRuntime {
  public:
    nRuntime(void);
    virtual ~nRuntime(void);
	static bool acceptClientVersion(const std::string& sServerBuild, bool isAdmin);

    static const bool m_bEnableCompression = true;
    static const bool m_bEnableClustering = true;
    static const bool m_bEnableClusterSites = true;
    static const bool m_bEnableScheduling = true;
    static const bool m_bEnhancedAdminFunction = true;
    static const bool m_bSupportJoins = true;
    static const bool sEnableCompression = true;
    static const bool s_bEnableMulticast = true;
    static const std::string sBuildNumber;
    static const std::string sBuildDate;

	static DLL const std::string& getReleaseDetails();
	static DLL const std::string& getBuildDetails();
	static DLL void setReleaseDetails(const std::string& relDetails);

private:
	static std::string sReleaseDetails;
	static std::string additionalBuildInfo;
	static float convertToVersion(const std::string& sBuildId);
};

}
}
}
}
