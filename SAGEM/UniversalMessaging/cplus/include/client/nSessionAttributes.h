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

#include <list>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
class fConnectionDetails;
}
}
namespace nirvana {
namespace client {

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::drivers;

/**
 * This class is a container for the attributes necessary to create a Nirvana session.
 */
class nSessionAttributes : public Countable {
  public:

    virtual DLL ~nSessionAttributes(void);

    /**
    * Constructs an nSessionAttributes object with the string URL specified and
    * retry count for initial connection attempts.
    *
    * @param url A string in the form protocol://host:port
    * e.g. nsp://127.0.0.1:9000
    * Protocol can be one of nsp, nhp, nsps, nhps
    * @param initialConnectionRetry A long specifying amount of times to retry
    * for initial connection
    *
    * @exception nIllegalArgumentException if the URL is invalid
    */
	DLL nSessionAttributes(const std::string& url, long initialConnectionRetry = 0);

    /**
    * Constructs an nSessionAttributes object with the collection of string URLs specified.
    *
    * @param *pUrls A string array, containing strings in the form protocol://host:port
    * e.g. nsp://127.0.0.1:9000
    * Protocol can be one of nsp, nhp, nsps, nhps
    * @param nUrl The number of URLs
    * @param initialConnectionRetry A long specifying amount of times to retry
    * for initial connection
    *
    * @exception nIllegalArgumentException if the URL is invalid
    */
	DLL nSessionAttributes(std::string *pUrls, int nUrl, long initialConnectionRetry = 0);

    /**
    * Returns the number of protocols used by this nSession
    *
    * @return Number of rnames used by this nSession
    */
    DLL int getNumberOfConnections();

    /**
    * Returns the rname indexed by idx. These where passed in when the initial nSession was
    * created
    *
    * @param idx the index of the connection details to return
    * @return String RNAME value
    * @exception Exception If the index is out of bounds
    */
    DLL const std::string getConnectionDetail(int idx);

    /**
    * Gets the initial connection retry count
    *
    * @return a long specifying the number of retry attempts for establishing initial connection
    */
    DLL long getInitialConnectionRetryCount();

    /**
    * Queries the property which requests a priority connection to the server.
    *
    * @return true if the request attribute is true, false otherwise.
    */
    UM_DEPRECATED DLL bool isRequestPriorityConnection();

    /**
     * Sets the property which requests a priority connection to the server. If this is true, sessions started with
     * these session attributes will request their connection be a priority connection.
     *
     * @param requestPriorityConnection boolean set to true to request a priority connection, false for a normal connection.
     *
     * DEPRECATED. The priority connection will be removed in future versions.
     */

    UM_DEPRECATED DLL void setRequestPriorityConnection(bool requestPriorityConnection);

	/**
	* Sets the initial keep alive interval of the session.
	*
	* @param timeMS long specifies the initial keep alive interval (in milliseconds) of the first keep alive event
	* sent to the server.
	*/
	DLL void setInitialKeepAliveInterval(long timeMS);

	/**
	* Queries the property which requests an unthrottled connection to the server.
	* 
	*
	* @param true if the unthrottled connection attribute is true, false otherwise
	*/
	DLL bool isRequestUnthrottledConnection();

	/**
	* Sets the property which requests an unthrottled connection to the server. If this is true, sessions started with
	* these session attributes will request that the server not throttle this connection when the available memory on the server is low.
	* This is only necessary if the server has the EnableFlowControl config item set to true and the session publishes to the server.
	* Otherwise the connection will not be throttled regardless.

	* @param requestUnthrottledConnection boolean set to true to request an unthrottled connection, false for a normal connection.
	*/
	DLL void setRequestUnthrottledConnection(bool requestUnthrottledConnection);


  protected:
    void setConnectionDetails(std::list<fConnectionDetails*>& newDetailsFromServer);
    void processRNAMES (const std::string& url);
    fConnectionDetails* getConnection(int idx);

  private:
	long m_initKeepAliveInterval;
    std::string* parseRealmProperties(const std::string& realmdetails, int& nNames, const std::string& delim = ",");

    std::list<fConnectionDetails*> m_details;
    static long INITIAL_COXN_RETRY_COUNT;
    /*DEPRECATED. The priority connection will be removed in future versions.*/
    bool requestPriorityConnection;
	  bool requestUnthrottledConnection;
    friend class nSession;

};

}
}
}
}
