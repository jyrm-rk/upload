/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef __Project__fSSLExtendedConfig__
#define __Project__fSSLExtendedConfig__

#include "fSSLConfig.h"
#include "fPrivateKeyPassPhraseHandler.h"
#include "fInvalidCertificateHandler.h"
#include "Poco/Net/Context.h"
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {

    class fSSLExtendedConfig : public fSSLConfig{
    public:
        //Copied from poco so we can keep poco contained
        
        enum VerificationMode
        {
            VERIFY_NONE    = Poco::Net::Context::VERIFY_NONE,
            /// Server: The server will not send a client certificate
            /// request to the client, so the client will not send a certificate.
            ///
            /// Client: If not using an anonymous cipher (by default disabled),
            /// the server will send a certificate which will be checked, but
            /// the result of the check will be ignored.
            
            VERIFY_RELAXED = Poco::Net::Context::VERIFY_RELAXED,
            /// Server: The server sends a client certificate request to the
            /// client. The certificate returned (if any) is checked.
            /// If the verification process fails, the TLS/SSL handshake is
            /// immediately terminated with an alert message containing the
            /// reason for the verification failure.
            ///
            /// Client: The server certificate is verified, if one is provided.
            /// If the verification process fails, the TLS/SSL handshake is
            /// immediately terminated with an alert message containing the
            /// reason for the verification failure.
            
            VERIFY_STRICT  = Poco::Net::Context::VERIFY_STRICT,
            /// Server: If the client did not return a certificate, the TLS/SSL
            /// handshake is immediately terminated with a handshake failure
            /// alert.
            ///
            /// Client: Same as VERIFY_RELAXED.
            
            VERIFY_ONCE    = Poco::Net::Context::VERIFY_ONCE,
            /// Server: Only request a client certificate on the initial 
            /// TLS/SSL handshake. Do not ask for a client certificate 
            /// again in case of a renegotiation.
            ///
            /// Client: Same as VERIFY_RELAXED.

        };

        fSSLExtendedConfig();
        fSSLExtendedConfig(const std::string& name, const std::string& adapter, int port);
        virtual ~fSSLExtendedConfig();
        
        void initialise();
        
        ssl::fPrivateKeyPassPhraseHandler* getPrivateKeyPassPhraseHandler();
        void setPrivateKeyPassPhraseHandler(ssl::fPrivateKeyPassPhraseHandler* handler);
        
        ssl::fInvalidCertificateHandler*  getInvalidCertificateHandler();
        void setInvalidCertificateHandler(ssl::fInvalidCertificateHandler* handler);
        
        std::string getPrivateKeyFileLocation();
        void setPrivateKeyFileLocation(const std::string& location);
        
        VerificationMode getVerificationMode();
        void setVerificationMode(VerificationMode mode);
        
        int getVerificationDepth();
        void setVerificationDepth(int depth);
        
        bool isUseDefaultCertificateAuthority();
        void setUseDefaultCertificateAuthority(bool useDefaultCertificateAuthority);
        
        const std::string getCipherLister();
        void setCipherList(const std::string& cipherList);
        
        //This method is for the SSL drivers not above
        Poco::Net::Context::VerificationMode getPocoVerificationMode();
        
    private:
        ssl::fPrivateKeyPassPhraseHandler* m_privateKeyPassPhraseHandler;
        ssl::fInvalidCertificateHandler* m_invalidCertificateHandler;
        std::string m_privateKeyFileLocation;
        VerificationMode m_verificationMode;
        int m_verificationDepth;
        bool m_useDefaultCertificateAuthorityBool;
        std::string m_cipherList;

    };

}}}}}

#endif /* defined(__Project__fSSLExtendedConfig__) */
