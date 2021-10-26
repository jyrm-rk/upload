/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fHTTPConfig.h"
#include "fBaseSSLConfig.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {

class fHTTPSConfig :
    public fHTTPConfig, public fBaseSSLConfig {
  public:
    fHTTPSConfig(void);
    fHTTPSConfig(const std::string& name, const std::string& adapter, int port, bool autostart = true);
    virtual ~fHTTPSConfig(void);

    virtual const std::string& getAlias();
    virtual int getType();
    virtual const std::string& getPrivateKeyPassword();
    virtual void setPrivateKeyPassword(const std::string& password);
    virtual void setAlias(const std::string& alias);
    virtual bool getCertRequired();
    virtual void setCertRequired(bool required);
    virtual const std::string& getKeyStore();
    virtual void setKeyStore(const std::string& keyStore);
    virtual const std::string& getKeyStorePassword();
    virtual void setKeyStorePassword(const std::string& keyStorePassword);
    virtual const std::string& getTrustStore();
    virtual void setTrustStore(const std::string& trustStore);
    virtual const std::string& getTrustStorePassword();
    virtual void setTrustStorePassword(const std::string& trustStorePassword);
    virtual void setEnabledCiphers(std::string* pCiphers, int nCipher);
    virtual std::string* getEnabledCiphers(int& nCipher);
    virtual void setConfiguredCiphers(std::string* pCiphers, int nCipher);
    virtual std::string* getConfiguredCiphers(int& nCipher);
    virtual const std::string& getRandomAlgorithm();
    virtual const std::string& getRandomProvider();
    virtual void setRandomAlgorithm(const std::string& alg);
    virtual void setRandomProvider(const std::string& prov);
    virtual const std::string& getCRL();
    virtual void setCRL(const std::string& CRL);
    virtual const std::string& getCRLClassName();
    virtual void setCRLClassName(const std::string& CRLClassName);
    virtual void setProvider(const std::string& provider);
    virtual const std::string& getProvider();
	virtual void setPKCS11ConfigFile(const std::string& location);
	virtual const std::string& getPKCS11ConfigFile();
	virtual void setPKCS11NSSName(const std::string& name);
	virtual const std::string& getPKCS11NSSName();

    virtual void readExternal(fEventInputStream *pEis);
    virtual void writeExternal(fEventOutputStream *pEos);
    virtual void readOldExternal(fEventInputStream *pEis);
    virtual void readOrigExternal(fEventInputStream *pEis);

  protected:
    bool m_bClientCertRequired;
    std::string m_alias;
    std::string m_privatePassword;
    std::string *m_ppEnabledCiphers;
    int m_nEnabledCipher;
    std::string *m_ppConfiguredCiphers;
    int m_nConfiguredCipher;
    std::string m_randomAlgorithm;
    std::string m_randomProvider;
    std::string m_CRL;
    std::string m_CRLClassName;
    std::string m_provider;
    std::string m_keyStore;
    std::string m_keyStorePassword;
    std::string m_truststore;
    std::string m_truststorePassword;
    std::string m_PKCS11Location;
    std::string m_PKCS11NSSName;
};

}
}
}
}
}
