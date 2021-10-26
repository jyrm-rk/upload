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
#include <map>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fObject;

class fDictionaryIterator {
  public:
    fDictionaryIterator(std::map<std::string, fObject*> *pMap);
    virtual ~fDictionaryIterator(void);

    virtual bool hasNext ();
    virtual void increment ();
    virtual const std::string getKey ();
    virtual fObject* getValue ();

  protected:
    std::map<std::string, fObject*> *m_pMap;
    std::map<std::string, fObject*>::iterator m_iterator;
};

}
}
}
}
