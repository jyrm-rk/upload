/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef Project_fPassPhraseHandlerPoco_h
#define Project_fPassPhraseHandlerPoco_h

#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include "fPrivateKeyPassPhraseHandler.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace ssl {


class fPrivateKeyPassPhraseHandlerPoco : public Poco::Net::PrivateKeyPassphraseHandler {

public:
    fPrivateKeyPassPhraseHandlerPoco(bool bServer, fPrivateKeyPassPhraseHandler * handler);
    fPrivateKeyPassPhraseHandlerPoco(bool bServer);
    virtual ~fPrivateKeyPassPhraseHandlerPoco(void);

    virtual void onPrivateKeyRequested(const void * pSender, std::string & privateKey);
   
    private :
    
    fPrivateKeyPassPhraseHandler* m_handler;
};
}

}
}
}
}

#endif
