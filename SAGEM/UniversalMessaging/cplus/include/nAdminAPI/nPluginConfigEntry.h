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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
/**
 *  Contains information for a plugin configuration entry.
 *
 * This data contains the name of the configuration, a description of what this entry does and the current value.
 */
class nPluginConfigEntry {
  public:

    /**
     * Construct a new nPluginConfigEntry
     *
     * @param name the string name of this entry
     * @param desc the string description of this entry
     * @param value the vale of this entry
     */
    nPluginConfigEntry(const std::string& name, const std::string& desc, const std::string& value);
    virtual ~nPluginConfigEntry(void);

    /**
     * Returns the name of the configuration entry.
     *
     * @return name.
     */
    const std::string& getName();

    /**
     * Returns the current value.
     * @return value.
     */
    const std::string& getValue();

    /**
     * Returns the a string describing what this configuration entry is.
     * @return description.
     */
    const std::string& getDescription();

    /**
     * Sets the value to the string specified.
     *
     * @param myValue new value.
     */
    void setValue (const std::string& value);

    /**
     * String of the object.
     * @return string representation.
     */
    std::string toString();

  protected:
    std::string m_name;
    std::string m_desc;
    std::string m_value;
};

}
}
}
}
