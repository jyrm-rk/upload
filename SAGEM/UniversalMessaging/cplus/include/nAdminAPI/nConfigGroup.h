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
#include "fSortedList.h"
#include "fBase.h"

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

/**
 * This class manages a group of nConfigEntry objects that are related. This class is
 * observable so that if new nConfigEntry objects are added to this group the Observer will
 * be notified with the new nConfigEntry
 */
class nConfigEntry;

using namespace com::pcbsys::foundation::configuration;
using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::collections;
/**
 * This class manages a group of nConfigEntry objects that are related. This class extends
 * Observable so that if new nConfigEntry objects are added to this group the Observer will
 * be notified with the new nConfigEntry
 */
class nConfigGroup :
    public Observable {
  public:
    /**
     * Constructs a new nConfigGroup
     * @param *pCo the fConfigObject for this group
     */
    nConfigGroup(fConfigObject *pCo);
    virtual ~nConfigGroup(void);

    /**
     * Retrieve this groups unique name
     *
     * @return String name
     */
    virtual const std::string& getName();

    /**
     * Retrieves the description of this group
     *
     * @return the description of this config group as a String
     */

    virtual const std::string& getDescription();

    /**
     * Finds a nConfigEntry that matches the name specified from within this group
     *
     * @see nConfigEntry
     * @param itemName Name of the nConfigEntry to find as a String
     * @return the nConfigEntry object found or null if the name does not exist within the group
     */
    virtual nConfigEntry* find(const std::string& itemName);

    /**
     * Returns the group as an Enumeration of all the nConfigEntry objects that the group consists of
     *
     * @return an fSortedList of string, nConfigEntry* pairs.
     */
    virtual fSortedList<std::string, nConfigEntry*>& getItems ();
    /**
     * Returns the type of this object
     * @return the type of the object.
     */
    virtual int getType();

    /**
     * Returns whether this config group is read only
     * @return bool value representing if it's read only
    */
	virtual bool isReadOnly();
    
    /**
     * Compares this object with the passed object. For internal use only
     * @param nConfigGroup to compare against
     * @return True if this object is equal to the passed long
     */
    virtual bool Equals(nConfigGroup *pItem);

    /**
     * Compares this object with the passed object. For internal use only
     * @param aLong long to compare against
     * @return True if this object is equal to the passed long
     */
    bool Equals(longlong aLong);

    /**
     * Returns the length of the configuration group, ie the number of items
     *
     * @return The number of config entries in this group
    */
    virtual int Length();

    /**
     * Compares this object with the passed object. For internal use only
     * @param aLong long to compare against
     * @return True if this object is less to the passed long
     */
    virtual bool lessThan(nConfigGroup *pItem);

    /**
     * Compares this object with the passed object. For internal use only
     * @param aLong long to compare against
     * @return True if this object is less to the passed long
     */
    virtual bool lessThan(longlong aLong);

  protected:
    virtual void update(fConfigObject *pCo);
    virtual fConfigObject* getBaseConfigObject();
    int compare(nConfigGroup *pItem);
    int compare(const std::string& item);

  private:
    std::string m_name;
    std::string m_description;
    fSortedList<std::string, nConfigEntry*> m_entries;
    fConfigObject *m_pObject;
    bool m_bReadOnly;

    friend class nPkgConfigListener;
    friend class nRealmNode;
};

}
}
}
}
