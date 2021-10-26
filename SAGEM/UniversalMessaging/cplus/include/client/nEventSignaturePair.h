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
namespace nbase {

using namespace com::pcbsys::foundation::fbase;

class nEventSignaturePair :
    public Object {
  public:
    nEventSignaturePair(void);
    virtual ~nEventSignaturePair(void);

    Object *m_pEvent;
    unsigned char *m_pSignature;
};

}
}
}
}
