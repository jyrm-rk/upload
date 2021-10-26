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
namespace nirvana {
namespace nAdminAPI {

/**
 * This interface is used to expose the SSL attributes for all interfaces that are SSL enabled. If a class
 * implements this interface it means that they support the listed API's and that SSL is active.
 */
class nSSLInterfaceAPI {
  public:

    /**
     * Returns an array of strings which represent the current Ciphers enabled for
     * use by this interface
     * @param nCipher integer to hold the size of the array
     * @return pointer to an array of Strings containing the names of the ciphers enabled for use by this interface
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual std::string* getEnabledCiphers(int& nCipher) = 0;

    /**
     * Specifies the names of the ciphers enabled for use by this interface.
     *
     * @param ciphers a pointer to an array of ciphers enabled for use by this interface
     * @param size of this array
     * @exception nAdminIllegalArgumentException if an empty or null array is specified
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setEnabledCiphers(std::string* pCiphers, int nCipher) = 0;

    /**
     * Returns the certificate name/alias that this interface uses as its
     * primary certificate
     *
     * @return the Name/Alias of the certificate as a String
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual const std::string& getAlias() = 0;

    /**
     * Sets the private key password so that the key can be loaded from the key store
     *
     * @param password for the private key as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setPrivateKeyPassword(const std::string& password) = 0;

    /**
     * Sets the certificate name/alias that this interface will use to select its certificate
     * from a keystore with multpiple entries.
     *
     * @param alias the name/alias to use as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setAlias(const std::string& alias) = 0;

    /**
     * Returns whether this interface requires SSL client authentication or not.
     * <p>
     * If this is set to false then this interface allows anonymous connections
     * using SSL.  Otherwise the client must have and present a valid certificate chain
     * during the SSL handshake.
     * </p>
     * @return a boolean specifying the SSL client authentication setting
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual bool getCertRequired() = 0;

    /**
     * Specifies whether this interface requires SSL client authentication or not.
     * <p>
     * If this is set to false then this interface allows anonymous connections
     * using SSL.  Otherwise the client must have and present a valid certificate chain
     * during the SSL handshake.
     * </p>
     * @param required a bool specifying if this interface will force client authentication
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setCertRequired(bool required) = 0;


    /**
     * Returns the name of the keystore file that this interface uses to load the
     * certificate from.
     *
     * @return The name of the keystore file to use as a String
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual const std::string& getKeyStore() = 0;

    /**
     * Sets the keystore file that this interface uses to load the certificate from
     *
     * @param keyStore the new keystore name as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setKeyStore(const std::string& keyStore) = 0;

    /**
     * Sets the keystore password that this interface will use to access the keystore file
     * specified.
     *
     * @param keyStorePassword the new password as a string
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setKeyStorePassword(const std::string& keyStorePassword) = 0;

    /**
     * Returns the current truststore file that this interface uses to validate
     * the client certificate chain against.
     *
     * @return the Truststore file name as a String
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual const std::string& getTrustStore() = 0;

    /**
     * Sets the truststore file that this interface uses to validate the client
     * certificate against.
     *
     * @param trustStore the new truststore file to use
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setTrustStore(const std::string& trustStore) = 0;

    /**
     * Returns an array of ciphers this this interface can be configured for use by
     * this interface.
     *
     * If the cipher is not in this list then the interface can not support it.
     *
     * @param an int in which to write the size of the array
     * @return a pointer to an array of ciphers which can be configured for use by this interface
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual std::string* getSupportedCiphers(int& nCipher) = 0;

    /**
     * Changes the truststore's password that the server uses to access the trust
     * store
     *
     * @param trustStorePassword the new password to use as a String
     * @exception nAdminIllegalArgumentException if an illegal argument is specified
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setTrustStorePassword(const std::string& trustStorePassword) = 0;

    /**
     * Returns the SecureRandom algoritm used for this interface. If it is null it uses the system default
     * algorithm.
     *
     * @return a String specifying the Random Algorithm used by this interface
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual const std::string& getRandomAlgorithm() = 0;

    /**
     * Returns the SecureRandom provider used by this interface. If it is null it uses the system default
     * provider.
     *
     * @return a String specifying the Secure Random provider used by this interface
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual const std::string& getRandomProvider() = 0;

    /**
     * Sets the SecureRandom algorithm to use for this interface
     *
     * @param alg the name of the new SecureRandom algorithm to use
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setRandomAlgorithm(const std::string& alg) = 0;

    /**
     * Sets the SecureRandom provider to use for this interface
     *
     * @param prov the name of the new SecureRandom provider to use
     * @see nSSLInterface
     * @see nHTTPSInterface
     */
    virtual void setRandomProvider(const std::string& prov) = 0;

    /**
     * Sets the Certificate revocation list file name that the interface should use
     * to check the incomming ssl connections. Is only used when client certificates
     * are required.
     *
     * The file should be in a standard X.509 Certificate Revocation List (CRL)
     *
     * @param fileName the CRL file name that the interface uses
     */
    virtual void setCRLFile(const std::string& fileName) = 0;

    /**
     * Returns the Certificate revocation list that the server uses.
     *
     * @return the CRL file name that the interface uses
     */
    virtual const std::string& getCRLFile() = 0;

    /**
     * Any class that extends com.pcbsys.nirvana.server.api.nSSLCertficateValidator can be used
     * by the server to perform CRL management. The class name can be supplied per interface and
     * then when a client connects a callout is issued to this class to validate the connection.
     *
     * @return current class name of the CRL validation
     */
    virtual const std::string& getCRLValidationClassName() = 0;

    /**
     * Any class that extends com.pcbsys.nirvana.server.api.nSSLCertficateValidator can be used
     * by the server to perform CRL management. The class name can be supplied per interface and
     * then when a client connects a callout is issued to this class to validate the connection.
     *
     * @param className the classname of the certificate validator to use within this interface
     */
    virtual void setCRLValidationClassName(const std::string& className) = 0;

    /**
     * Sets the name of the JSSE provider to use for the interface
     * @param providerName the name of the JSSE provider to use
     */
    virtual void setProvider(const std::string& providerName) = 0;

    /**
     * Get the name of the JSSE provider used by this SSL interface
     * @return The name of the JSSE provider being used for the interface
     */
    virtual const std::string& getProvider() = 0;

	/**
	 * Get the PKCS11 configuration file used by this SSL interface
	 * on the UM server.
	 * @return The name of the PKCS11 configuration file.
	 */
	virtual const std::string getPKCS11ConfigFile() = 0;

	/**
	 * Sets the name of the PKCS11 configuration used by this SSL interface
	 * on the UM server.
	 * @param location the location/path of the PKCS11 configuration file.
	 */
	virtual void setPKCS11ConfigFile(const std::string location) = 0;

	/**
	 * Get the PKCS11 NSS name that unique identifies the PKCS11 configuration
	 * on the UM server.
	 * @return The NSS Name used in the PKCS11 configuration file.
	 */
	virtual const std::string getPKCS11NSSName() = 0;

	/**
	 * Sets the name of the PKCS11 NSS name that uniquely identifies the PKCS11
	 * configuration on the UM server.
	 * @param name The NSS name of the PKCS11 configuration file.
	 */
	virtual void setPKCS11NSSName(const std::string name) = 0;
};

}
}
}
}
