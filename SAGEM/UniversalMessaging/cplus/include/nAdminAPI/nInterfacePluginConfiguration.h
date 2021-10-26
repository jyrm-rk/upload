/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"

#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nPluginDetails;
}
namespace nAdminAPI {

using namespace nbase;
using namespace com::pcbsys::foundation::fbase;

/**
 * This class contains the plugin static information used by the plugin instances.
 */
class nInterfacePluginConfiguration : public CountableObject {
  public:
    /**
     * Creates a new nACLEntry with the subject being name@host. There are no
     * default permissions set so this subject can perform NO actions on the secured objects
     *
     * @param name Username/Token for the subject
     * @param host the host they can connect from
     */
    nInterfacePluginConfiguration(nPluginDetails *pDetails);

    virtual ~nInterfacePluginConfiguration(void);

    /**
     * Returns the name of the plugin.
     * @return String name.
     */

    virtual const std::string& getName();
    /**
     * Returns a string containing information regarding this plugin.
     *
     * @return String description.
     */

    virtual const std::string& getDescription();
    /**
     * Returns the description for the key specified.
     * @param key string.
     * @return String description for the key.
     */
    virtual const std::string getDescription(const std::string& key);

  private:
    nPluginDetails *m_pDetails;
};

}
}
}
}
