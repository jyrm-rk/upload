/*
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fDictionaryIterator.h"
#include "fObject.h"

#include <string>
#include <map>

using namespace com::pcbsys::foundation::fbase;

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
/**
* This class enables you to iterate through the values in an event header.
* <p>
* For example:
* <pre>
* nHeader* header = event->getHeader();
* nHeaderIterator* headerIterator = header->getIterator();
*
* while (headerIterator->hasNext()) {
*     // get the key and value
*     std::string headerKey = headerIterator->getKey(); // nrvdead.orig.eid, nrvpub.time etc.
*     fObject* headerValue = headerIterator->getValue();
*
*     // do something with them
*     .....
*
*     // move the next value in the header
*     headerIterator->next();
* }
*
* delete headerIterator;
*/
class nHeaderIterator : public Countable {
  public:
    /**
    * Destructor of the header iterator
    */
    DLL virtual ~nHeaderIterator(void);

    /**
    * Returns whether there is any more headers to process
    */
    DLL bool hasNext ();

    /**
    * Move to the next header in the iterator
    */
    DLL void next ();

    /**
    * Return the key of the current header in the iterator
    */
    DLL const std::string getKey ();

    /**
    * Return the value of the current header in the iterator. The caller has ownership of the pointer and must free it when it's no longer used
    */
    DLL fObject* getValue ();

    /**
    * Represents the different header fields
    */
    enum HeaderType {
        NRVPUB_TIME,
        NRVPUB_HOST,
        NRVPUB_NAME,
        NRVPUB_REDELIVERY,
        NRVSUB_HOST,
        NRVSUB_NAME,
        NRVSUB_ID,
        NRVDEAD_ORIG_CHAN,
        NRVDEAD_ORIG_EID,
        NRVJOIN_ORIG_CHAN,
        NRVJOIN_ORIG_REALM,
        NRVJOIN_PATH,
        NRVSUB_ORIG_EID
    };

  private:
    friend class nHeader;

    static std::map<std::string, HeaderType> s_nHeaderKeys;

    nHeaderIterator(nHeader *header);
    nHeader *m_nHeader;
    std::map<std::string, HeaderType>::iterator it;

};

}
}
}
}
