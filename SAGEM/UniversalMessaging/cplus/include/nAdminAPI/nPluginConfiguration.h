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
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::fbase;

class nPluginConfigEntry;

/**
 * This class contains the configuration context for a single plugin on a single HTTP type interface.
 *
 * A single interface can have many nPluginConfiguration objects defined, each one specifying what type of processing
 * is done within the URI of the request.
 *
 */
class nPluginConfiguration : public CountableObject {
  public:
    /**
     *  Constructs an empty configuration object binding the specified nInterfacePluginConfiguration to the URI.
     * @param name.
     * @param mount where to bind.
     */
    nPluginConfiguration(const std::string& name, const std::string& mount);
    ~nPluginConfiguration(void);

    /**
     * Get the list of config entries for this plugin.
     *
     * @return list of config entries.
     */
    std::list<nPluginConfigEntry*>& getConfiguration();

    /**
     * Return the name of the plugin.
     * This would be the type of plugin, XML, SOAP, file etc.
     *
     * @return string name.
     */
    const std::string& getName();

    /**
     * Returns the URI where the Realm Server will pass the request off to this plugin.
     *
     * @return String mount point.
     */
    virtual const std::string& getMountPoint();

    /**
     * Returns the name of the configuration
     *
     * @return String name
     */
    std::string toString();

  protected:
    virtual void add(nPluginConfigEntry *pEntry);

  private:
    std::string m_name;
    std::string m_mount;
    std::list<nPluginConfigEntry*> m_configuration;

    friend class nHTTPInterface;
};

}
}
}
}
