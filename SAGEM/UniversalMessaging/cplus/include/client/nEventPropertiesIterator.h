/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fDictionaryIterator.h"
#include "nObject.h"

#include <string>
#include <map>

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::nirvana::client;

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
/**
* This class enables you to iterate through the event properties keys and values.
* <p>
* For example:
* <pre>
*	nEventProperties *props = event->getEventProperties();
*	nEventPropertiesIterator *pIterator = pProp->getIterator ();
*	while (pIterator->hasNext ())
*	{
*		std::string key = pIterator->getKey ();
*		nObject *pObject = pIterator->getValue();
*		int type = pObject->getType ();
*
*		if (type == nObject::EVENTPROPERTIES)
*		{
*			nEventProperties *pvalue = (nEventProperties*)pObject;
*			.....
*		}
*		else
*		{
*			.....
*		}
*		pIterator->increment();
*	}
* </pre>
*
*
*/
class nEventPropertiesIterator {
  public:
    DLL virtual ~nEventPropertiesIterator(void);

    /**
    * Returns whether there is any more key/value pairs to process
    */
    DLL bool hasNext ();

    /**
    * Move to the next pair in the iterator
    */
    DLL void increment ();

    /**
    * Return the key of the current key / value pair in the iterator
    */
    DLL const std::string getKey ();

    /**
    * Return the value of the current key / value pair in the iterator
    */
    DLL nObject* getValue ();

  private:
    nEventPropertiesIterator(fDictionaryIterator *dic);
    fDictionaryIterator *it;
	std::map<fObject *, nObject *> m_nObjectValues;
    friend class nEventProperties;

};

}
}
}
}
