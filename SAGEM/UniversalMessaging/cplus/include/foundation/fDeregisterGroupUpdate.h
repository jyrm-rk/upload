/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fAclGroup.h"
#include "fBase.h"

using namespace com::pcbsys::foundation::security;

namespace com {
namespace pcbsys {
namespace foundation {
namespace security {

class fDeregisterGroupUpdate : public Object {
  public:
    fDeregisterGroupUpdate(fAclGroup* group) {
        myGroup = group;
    }

    ~fDeregisterGroupUpdate() {
        if(myGroup && myGroup->delRef()) {
            delete myGroup;
        }

        myGroup = NULL;
    }

    virtual fAclGroup* getfAclGroup() {
        return myGroup;
    }

    virtual int getType() {
        return fBase::FDEREGISTERGROUPUPDATE;
    }


  private:
    fAclGroup* myGroup;
};

}
}
}
}
