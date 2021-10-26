/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSocketInterface.h"
#include "nSSLInterfaceAPI.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fSSLConfig;
}
}
}
namespace nirvana {
namespace nAdminAPI {

class nInterfaceManager;

using namespace com::pcbsys::foundation::drivers::configuration;
/**
 * This class contains all the configuration required by the Nirvana Realm server to start
 * and control the SSL interface.
 */
class DLL nSSLInterface :
    public nSocketInterface, public nSSLInterfaceAPI {
  public:

    /**
     * Creates a new SSL interface for the suplied SSL config and Interface Manager
     *
     * @param *pCfg the fSSLConfig associated with this nSSLInterface
     * @param *pIm the nInterfaceManager object associated with this interface
     * @throws nAdminIllegalArgumentException if the adapter is null or the port is in an invalid range
     */
    nSSLInterface(fSSLConfig *pCfg, nInterfaceManager *pIm);
    nSSLInterface(const std::string& adapter, int port, bool autostart = true);

    virtual ~nSSLInterface(void);

    /**
     * Returns an array of strings which represent the current Ciphers enabled for
     * use by this interface
     *
     * @param nCipher the number of entries in the array of strings
     * @return an array containing the names of the ciphers enabled for use by this interface
     *
     * @see nHTTPSInterface
     */
    virtual std::string* getEnabledCiphers(int& nCipher);

    /**
     * Specifies the names of the ciphers enabled for use by this interface.
     *
     * @param ciphers an array of ciphers enabled for use by this interface as strings
     * @param nCipher the number of ciphers
     * @exception nAdminIllegalArgumentException if an empty or null array is specified
     *
     * @see nHTTPSInterface
     */
    virtual void setEnabledCiphers(std::string* pCiphers, int nCipher);

    /**
     * Returns the certificate name/alias that this interface uses as its
     * primary certificate
     *
     * @return the Name/Alias of the certificate as a String
     *
     * @see nHTTPSInterface
     */
    virtual const std::string& getAlias();


    /**
     * Sets the private key password so that the key can be loaded from the key store
     *
     * @param password for the private key as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     *
     * @see nHTTPSInterface
     */
    virtual void setPrivateKeyPassword(const std::string& password);

    /**
     * Sets the certificate name/alias that this interface will use to select its certificate
     * from a keystore with multpiple entries.
     *
     * @param alias the name/alias to use as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     *
     * @see nHTTPSInterface
     */
    virtual void setAlias(const std::string& alias);

    /**
     * Returns whether this interface requires SSL client authentication or not.
     * <p>
     * If this is set to false then this interface allows anonymous connections
     * using SSL.  Otherwise the client must have and present a valid certificate chain
     * during the SSL handshake.
     * </p>
     * @return a bool specifying the SSL client authentication setting
     *
     * @see nHTTPSInterface
     */
    virtual bool getCertRequired();

    /**
     * Specifies whether this interface requires SSL client authentication or not.
     * <p>
     * If this is set to false then this interface allows anonymous connections
     * using SSL.  Otherwise the client must have and present a valid certificate chain
     * during the SSL handshake.
     * </p>
     * @param required a bool specifying if this interface will force client authentication
     *
     * @see nHTTPSInterface
     */
    virtual void setCertRequired(bool required);

    /**
     * Returns the name of the keystore file that this interface uses to load the
     * certificate from.
     *
     * @return The name of the keystore file to use as a String
     *
     * @see nHTTPSInterface
     */
    virtual const std::string& getKeyStore();

    /**
     * Sets the keystore file that this interface uses to load the certificate from
     *
     * @param keyStore the new keystore name as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     *
     * @see nHTTPSInterface
     */
    virtual void setKeyStore(const std::string& keyStore);

    /**
     * Sets the keystore password that this interface will use to access the keystore file
     * specified.
     *
     * @param keyStorePassword the new password as a string
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     *
     * @see nHTTPSInterface
     */
    virtual void setKeyStorePassword(const std::string& keyStorePassword);

    /**
     * Returns the current truststore file that this interface uses to validate
     * the client certificate chain against.
     *
     * @return the Truststore file name as a String
     *
     * @see nHTTPSInterface
     */
    virtual const std::string& getTrustStore();

    /**
     * Sets the truststore file that this interface uses to validate the client
     * certificate against.
     *
     * @param trustStore the new truststore file to use
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     *
     * @see nHTTPSInterface
     */
    virtual void setTrustStore(const std::string& trustStore);

    /**
     * Returns an array of ciphers this this interface can be configured for use by
     * this interface.
     *
     * If the cipher is not in this list then the interface can not support it.
     * @param nCipher the number of entries within the array
     * @return pointer to array of ciphers which can be configured for use by this interface
     *
     * @see nHTTPSInterface
     */
    virtual std::string* getSupportedCiphers(int& nCipher);

    /**
     * Changes the truststore's password that the server uses to access the trust
     * store
     *
     * @param trustStorePassword the new password to use as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     *
     * @see nHTTPSInterface
     */
    virtual void setTrustStorePassword(const std::string& trustStorePassword);

    /**
     * Returns the SecureRandom algoritm used for this interface. If it is null it uses the system default
     * algorithm.
     *
     * @return a String specifying the Random Algorithm used by this interface
     *
     * @see nHTTPSInterface
     */
    virtual const std::string& getRandomAlgorithm();

    /**
     * Returns the SecureRandom provider used by this interface. If it is null it uses the system default
     * provider.
     *
     * @return a String specifying the Secure Random provider used by this interface
     *
     * @see nHTTPSInterface
     */
    virtual const std::string& getRandomProvider();

    /**
     * Sets the SecureRandom algorithm to use for this interface
     *
     * @param alg the name of the new SecureRandom algorithm to use
     *
     * @see nHTTPSInterface
     */
    virtual void setRandomAlgorithm(const std::string& alg);

    /**
     * Sets the SecureRandom provider to use for this interface
     *
     * @param prov the name of the new SecureRandom provider to use
     *
     * @see nHTTPSInterface
     */
    virtual void setRandomProvider(const std::string& prov);

    /**
     * Sets the Certificate revocation list file name that the interface should use
     * to check the incomming ssl connections. Is only used when client certificates
     * are required.
     *
     * The file should be in a standard X.509 Certificate Revocation List (CRL)
     *
     * @param fileName the file name used as the CRL
     */
    virtual void setCRLFile(const std::string& fileName);

    /**
     * Returns the Certificate revocation list that the server uses.
     *
     * @return the CRL file name that the interface uses
     */
    virtual const std::string& getCRLFile();

    /**
     * Any class that extends com.pcbsys.nirvana.server.api.nSSLCertficateValidator can be used
     * by the server to perform CRL management. The class name can be supplied per interface and
     * then when a client connects a callout is issued to this class to validate the connection.
     *
     * @return current class name of the CRL validation
     */
    virtual const std::string& getCRLValidationClassName();

    /**
     * Any class that extends com.pcbsys.nirvana.server.api.nSSLCertficateValidator can be used
     * by the server to perform CRL management. The class name can be supplied per interface and
     * then when a client connects a callout is issued to this class to validate the connection.
     *
     * @param className the classname of the certificate validator to use within this interface
     */
    virtual void setCRLValidationClassName(const std::string& className);

    /**
     * Sets the name of the JSSE provider to use for the interface
     * @param providerName the name of the JSSE provider to use
     */
    virtual void setProvider(const std::string& providerName);

    /**
     * Get the name of the JSSE provider used by this SSL interface
     * @return The name of the JSSE provider being used for the interface
     */
    virtual const std::string& getProvider();

    virtual int getType ();

	/**
	* Get the PKCS11 configuration file used by this SSL interface
	* on the UM server.
	* @return The name of the PKCS11 configuration file.
	*/
	virtual const std::string getPKCS11ConfigFile();

	/**
	* Sets the name of the PKCS11 configuration used by this SSL interface
	* on the UM server.
	* @param location the location/path of the PKCS11 configuration file.
	*/
	virtual void setPKCS11ConfigFile(const std::string location);

	/**
	* Get the PKCS11 NSS name that unique identifies the PKCS11 configuration
	* on the UM server.
	* @return The NSS Name used in the PKCS11 configuration file.
	*/
	virtual const std::string getPKCS11NSSName();

	/**
	* Sets the name of the PKCS11 NSS name that uniquely identifies the PKCS11
	* configuration on the UM server.
	* @param name The NSS name of the PKCS11 configuration file.
	*/
	virtual void setPKCS11NSSName(const std::string name);

  protected:
    virtual fDriverConfig* convert();
    void convert(fSSLConfig *pCfg);

    bool m_bClientCertRequired;
    std::string m_keyStore;
    std::string m_keyStorePassword;
    std::string m_alias;
    std::string m_truststore;
    std::string m_truststorePassword;
    std::string m_privatePassword;
    std::string *m_pCiphers;
    int m_nCipher;
    std::string *m_pSupportedCiphers;
    int m_nSupportedCipher;
    std::string m_rndAlg;
    std::string m_rndProv;
    std::string m_CRL;
    std::string m_CRLClassName;
    std::string m_provider;
	std::string m_PKCS11Location;
	std::string m_PKCS11NSSName;

  private:
    void validateKeystore(const std::string& keystore);
    void validatePassword(const std::string& password);
};

}
}
}
}
