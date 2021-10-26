/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */

#ifndef Project_fPassPhraseHandler_h
#define Project_fPassPhraseHandler_h

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace ssl {


    class fPrivateKeyPassPhraseHandler : public com::pcbsys::foundation::fbase::Countable{

public:
    virtual void onPrivateKeyRequested(std::string & privateKey)=0;
};
}

}
}
}
}


#endif
