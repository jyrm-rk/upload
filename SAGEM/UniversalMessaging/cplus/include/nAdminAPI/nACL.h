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

namespace com {
namespace pcbsys {
namespace nirvana {
/*! \namespace com.pcbsys.nirvana.nAdminAPI
Documentation for the Nirvana C++ Admin API
*/
/**
Nirvana Administration (nAdminAPI) Package, incorporating all the tools necessary to monitor, configure and manage one or more Nirvana realms and / or clusters of realms.
*/
namespace nAdminAPI {

class nACLEntry;
class Merge;

struct ci_less : std::binary_function<std::string, std::string, bool>
{
	// case-independent (ci) compare_less binary function
	struct nocase_compare : public std::binary_function<unsigned char, unsigned char, bool>
	{
		bool operator() (const unsigned char& c1, const unsigned char& c2) const {
			return tolower(c1) < tolower(c2);
		}
	};
	bool operator() (const std::string & s1, const std::string & s2) const {
		return std::lexicographical_compare
			(s1.begin(), s1.end(),   // source range
			s2.begin(), s2.end(),   // dest range
			nocase_compare());  // comparison
	}
};

using namespace foundation::fbase;
using namespace foundation::collections;
/**
 * represents a list of nACLEntry classes used by the Nirvana Realm server to control access
 * to secured objects such as Realms, Channels and Queues.
 * @see nACLEntry
 */
class nACL :
    public Observable {
  public:
    virtual ~nACL(void);

    /**
     * Returns whether an nACLEntry exists the nACL which matches this subject.
     *
     * @param subject String representation of the subject (user\@host)
     * @return whether a matching acl entry exists
     */
    virtual bool contains(const std::string& subject);

    /**
     * Removes the nACLEntry which matches the subject specified the nACLEntry object.
     *
     * @param entry The nACLEntry to be removed from the list
     */
    virtual void remove(nACLEntry *pEntry);

    /**
     * Adds a new nACLEntry into the list.
     *
     * @param *pEntry The new nACLEntry to add to the list
     */
    virtual void add(nACLEntry *pEntry);

    /**
     * Finds an nACLEntry which matches the passed in nACLEntry. The comparison is done
     * on the subject only and not the permissions since the subject must be unique in the
     * list.
     * If it could not find a match it will throw nACLEntryNotFoundException
     *
     * @param pEntry An nACLEntry* to locate within the list
     * @return the nACLEntry* which matches
     */
    virtual nACLEntry* find(nACLEntry* pEntry);

    /**
     * Returns the number of entries within the list
     *
     * @return int size of this list
     */
    virtual int size();

    /**
     * Returns the nACLEntry specified by the index parameter
     * is useful to examine/walk the list.
     *
     * @param index the index position of the nACLEntry to be retrieved
     * @return the nACLEntry* at the specified index
     */
    virtual nACLEntry* get(int index);


    /**
     * Finds an nACLEntry within the list which matches this subject. If it could
     * not find a match it will throw nACLEntryNotFoundException
     *
     * @param subject String representation of the subject (user\@host)
     * @return the nACLEntry which matched
     */
    virtual nACLEntry* find(const std::string& subject);


    /**
     * Returns an Enumeration of nACLEntry objects which make up the list. This
     * is useful to examine/walk the list.
     *
     * @return <std::string, nACLEntry*>& of nACLEntry
     */
    virtual fSortedList<std::string, nACLEntry*>& getEntries();

    /**
     * Removes the nACLEntry which matches the subject specified by the string passed in.
     * Currently no wild card removals are supported so only a direct match will result in
     * the removal of the nACLEntry
     *
     * @param subject String representation of the subject (user\@host)
     * @exception nACLEntryNotFoundException thrown if acl entry is not found
     * @exception nAdminIllegalArgumentException thrown if acl entry is null
     */
    virtual void remove(const std::string& subject);

    /**
     * Replaces the existing nACLEntry privileges with the passed nACLEntry. Useful for changing
     * permissions for a subject within a list
     *
     * @param *pEntry The nACLEntry containing the updated privileges
     */
    virtual void replace(nACLEntry *pEntry);

    /**
     * Removes ALL of the nACLEntry objects from the list.
     * WARNING: if you commit an empty nACL you will effectively block ALL access
     * to the secure object. There is no way to override this so be careful when calling
     * this function that you do actually add nACLEntry objects to this to at least allow
     * the administrator back in
     */
    virtual void removeAll();

  protected:
    /**
     * Default constructor for nACL. The user should not typically need to call this
     * since all the original lists are supplied by the realm itself.
     */
    nACL(void);

    /**
     * Constructs a new nACL
     * @param acl The list of nACLEntry to be held by this nACL
     */
    nACL(fSortedList<std::string, nACLEntry*>& acl);

    virtual void sendToObservers(Object *pChange);
    virtual void merge(nACL *pChanges);
    virtual void copy(nACL *pCpy);
    virtual void resetChange();
    virtual bool changedShape();

    fSortedList<std::string, nACLEntry*, ci_less> m_ACL;
    bool m_bHasChanged;

  private:
    virtual int checkMalformedSubject(const std::string& subject);

    Poco::Mutex m_removeMutex;
    Poco::Mutex m_addMutex;
    Poco::Mutex m_copyMutex;
    Poco::Mutex m_mergeMutex;
    Poco::Mutex m_replaceMutex;

    friend class Merge;
    friend class nPkgAdminListener;
    friend class nNode;
    friend class nLeafNode;
    friend class nServiceNode;
    friend class nRealmNode;
    friend class nInterface;
};

}
}
}
}
