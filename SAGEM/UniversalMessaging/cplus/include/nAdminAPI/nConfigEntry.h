/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Observable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace configuration {
class fConfigObject;
}
}
namespace nirvana {
namespace nAdminAPI {

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::configuration;
/**
 * This class contains all the information about a configuration parameter, including the name,
 * the current value, a description of it and a warning or constraint string.
 *
 * This class extends Observable since the value can be changed asynchronously from the
 * realm. When this happens any observer is notified of the changed value, passed as a String
 */
class nConfigEntry :
    public Observable {
  public:
    /**
     * Constructs a new nConfigEntry
     * @param *pCo the config object for this config entry
     * @param key the unique key to use for this entry
     */
    nConfigEntry(fConfigObject *pCo, const std::string& key);
    virtual ~nConfigEntry(void);

    /**
     * Retrieves the current value of this parameter. The parameter is always a string though it
     * could represent longs/ints/booleans etc.
     *
     * @return the current value of this configuration parameter as a String
     */
    virtual const std::string& getValue ();

    /**
    * Sets the parameters value to the new value passed. This value is nit committed to the realm until
    * the nRealmNode.commitConfig(nConfigGroup) is called.
    *
    * @param value The new value to set this parameter to as a String
    *
    * @exception nAdminIllegalArgumentException thrown if value is null, not the correct type, or not within a specific range
    *
    * @see nRealmNode
    * @see nConfigGroup
    */
    virtual void setValue (const std::string&);
    /**
     * Retrieves the name of the configuration parameter
     *
     * @return the name of this configuration parameter as a String
     */
    virtual const std::string& getName();

    /**
     * Returns a string which contains the description for this parameter and typically what it is used for.
     *
     * @return a description for this config entry as a String
     */
    virtual const std::string& getDescription();

    /**
     * Returns a String which contains information about the limits/bounds of this parameter and what would
     * be nominal values
     *
     * @return a warning for this config entry as a String
     */
    virtual const std::string& getWarning();

    /**
     * Update this nConfigEntry based on the fConfigObject passed in.
     *
     * @param the fConfigObject to update from.
     */
    virtual void update(fConfigObject *pCo);

    /**
     * Retrieves the type of the configuration parameter
     *
     * @return type of config object
     */
    virtual int getType();

    virtual bool Equals(nConfigEntry *pItem);

    /**
     * Compares this object with the passed object. For internal use only
     * @param aLong long to compare against
     * @return True if this object is equal to the passed long
     */
    virtual bool Equals(longlong aLong);

    /**
     * Retrieves the maximum range value of the configuration parameter
     *
     * @return maximum range value of config object
     */
    virtual longlong getMax();

    /**
     * Retrieves the minimum range value of the configuration parameter
     *
     * @return minimum range value of config object
     */
    virtual longlong getMin();

    /**
         * Retrieves the isAdvanced value of the configuration parameter
         *
         * @return minimum range value of config object
         */
        virtual bool isAdvanced();

    /**
     * Retrieves the parent object of this entry
     *
     * @return fConfigObject parent object
     */
    virtual fConfigObject* getParent();

    /**
     * Returns whether the specific entry is read only and therefore cannot be modifed
     * @return if the entry is read only
     */
    virtual bool isReadOnly();

    /**
     * Compares this object with the passed object. For internal use only
     *
     * @param item Object to compare against
     * @return True if this object is less than the passed object
     */
    virtual bool lessThan(nConfigEntry *pItem);

    /**
     * Compares this object with the passed object. For internal use only
     * @param aLong long to compare against
     * @return True if this object is less than the passed long
     */
    virtual bool lessThan(longlong aLong);

    /**
     * Validates a proposed new value for the config entry.
     *
     * @param value a string object specifying the value to be validated
     * @exception nAdminIllegalArgumentException thrown if not the correct type, or not within a specific range
     *
     */
    virtual void validateNewValue(const std::string& value);

  private:
    std::string checkRange(longlong val, longlong min, longlong max);
    int compare(nConfigEntry *pItem);
    int compare(const std::string& item);

    fConfigObject *m_pParent;
    std::string m_name;
    std::string m_value;
    std::string m_desc;
    std::string m_warning;
    bool m_bReadOnly;
};

}
}
}
}
