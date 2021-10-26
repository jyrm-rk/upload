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
#include "fObject.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace foundation::fbase;

class nEventPropertyChangeListener {
  public:
    nEventPropertyChangeListener(void);
    virtual ~nEventPropertyChangeListener(void);

    /**
     * Called when an event property is added
     * @param key Key to the entry which was added
     * @param val Data which was stored
     * @param original original value of data
     */
    virtual void added(const std::string& key, fObject *pVal, fObject *original) = 0;

    /**
     * Called when an event property is deleted
     * @param key Key to the entry which was deleted
     */
    virtual void deleted(const std::string& key) = 0;
};

}
}
}
}
