/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef __Project__nInvalidCertificateHandler__
#define __Project__nInvalidCertificateHandler__

#include "fBase.h"
#include "fInvalidCertificateHandler.h"
#include "Poco/Net/VerificationErrorArgs.h"

namespace com {
    namespace pcbsys {
        namespace foundation {
            namespace drivers {
                namespace ssl{
                    
                    class fInvalidCertificateHandler : public com::pcbsys::foundation::fbase::Countable {
                    public:
                        //We need to overload this class as well
                        virtual void onInvalidCertificate(Poco::Net::VerificationErrorArgs & errorCert)=0;
                    };
                }
            }
        }
    }
}


#endif /* defined(__Project__fInvalidCertificateHandler__) */
