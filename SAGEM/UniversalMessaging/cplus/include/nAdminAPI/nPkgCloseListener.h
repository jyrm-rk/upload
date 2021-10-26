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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

class nRealmNode;

class nPkgCloseListener {
  public:
    nPkgCloseListener(void);
    virtual ~nPkgCloseListener(void);

    virtual void closed(nRealmNode *pClose) = 0;

    //Some classes which extend this are countable but in nRealmNode we used to just delete
    //all close listeners with no regard to reference counting.  We should make this class countable
    //but then we any classes which extend this AND CountableObject will have ambiguous
    //add and delRef() methods.  The solution we have come up with is to add these two methods which
    //means for any classes which previously had CountableObject in their hierarchy will have to
    //Override these and call the correct super class to overcome the ambiguity.  Other classes
    //can be left as they were and delRef() will always return true meaning it can be deleted
    virtual void addRef() {

    }
    virtual bool delRef() {
        return true;
    }
};

}
}
}
}
