/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef __Project__nInvalidCertificateHandlerPoco__
#define __Project__nInvalidCertificateHandlerPoco__

#include "Poco/Net/InvalidCertificateHandler.h"
#include "fInvalidCertificateHandler.h"
namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace ssl{

class fInvalidCertificateHandlerPoco : public Poco::Net::InvalidCertificateHandler {
public:
    fInvalidCertificateHandlerPoco(bool bServer, fInvalidCertificateHandler* handler);
    fInvalidCertificateHandlerPoco(bool bServer);
    virtual ~fInvalidCertificateHandlerPoco(void);
    
    virtual void onInvalidCertificate(const void * pSender, Poco::Net::VerificationErrorArgs & errorCert);
    
private:
    fInvalidCertificateHandler* m_handler;
};
}
}
}
}
}

#endif /* defined(__Project__fInvalidCertificateHandlerPoco__) */
