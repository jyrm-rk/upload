/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {

class fBaseSSLConfig {
  public:
    virtual const std::string& getAlias() = 0;
    virtual const std::string& getPrivateKeyPassword() = 0;
    virtual void setPrivateKeyPassword(const std::string& password) = 0;
    virtual void setAlias(const std::string& alias) = 0;
    virtual bool getCertRequired() = 0;
    virtual void setCertRequired(bool required) = 0;
    virtual const std::string& getKeyStore() = 0;
    virtual void setKeyStore(const std::string& keyStore) = 0;
    virtual const std::string& getKeyStorePassword() = 0;
    virtual void setKeyStorePassword(const std::string& keyStorePassword) = 0;
    virtual const std::string& getTrustStore() = 0;
    virtual void setTrustStore(const std::string& trustStore) = 0;
    virtual const std::string& getTrustStorePassword() = 0;
    virtual void setTrustStorePassword(const std::string& trustStorePassword) = 0;
    virtual void setEnabledCiphers(std::string* pCiphers, int nCipher) = 0;
    virtual std::string* getEnabledCiphers(int& nCipher) = 0;
    virtual void setConfiguredCiphers(std::string* pCiphers, int nCipher) = 0;
    virtual std::string* getConfiguredCiphers(int& nCipher) = 0;
    virtual const std::string& getRandomAlgorithm() = 0;
    virtual const std::string& getRandomProvider() = 0;
    virtual void setRandomAlgorithm(const std::string& alg) = 0;
    virtual void setRandomProvider(const std::string& prov) = 0;
    virtual const std::string& getCRL() = 0;
    virtual void setCRL(const std::string& myCRL) = 0;
    virtual const std::string& getCRLClassName() = 0;
    virtual void setCRLClassName(const std::string& myCRLClassName) = 0;
    virtual void setProvider(const std::string& myProvider) = 0;
    virtual const std::string& getProvider() = 0;
	virtual void setPKCS11ConfigFile(const std::string& location) = 0;
	virtual const std::string& getPKCS11ConfigFile() = 0;
	virtual void setPKCS11NSSName(const std::string& name) = 0;
	virtual const std::string& getPKCS11NSSName() = 0;
};

}
}
}
}
}
