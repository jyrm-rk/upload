/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NCUSTOMHEADER
#define NCUSTOMHEADER

#include "fCustomHeader.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace foundation {
class fCustomHeader;
}
namespace nAdminAPI {
using namespace com::pcbsys::foundation::drivers::configuration;
using namespace com::pcbsys::nirvana::client;
/**
 * This Class represent a single custom header field which will be used by javascript
 */

class nCustomHeader {
  public:

    /**
    * A custom header deceleration for javascript.
    *
    * @param key the header value
    * @param value the header value (optional)
    * @param userAgents set this to '*' if you wish this to apply to all javascript communications or
    * a comma separated list of specific user agents
    * @exception nIllegalArgumentException if the key is less than 1 character
    */
    nCustomHeader(std::string key, std::string value, std::string userAgents);

    /**
    * The header key field
    * @return the header key
    */
    std::string getKey();

    /**
    * The header value
    * @return the header value
    */
    std::string getValue();

    /**
    * The user agents this applies to
    * @return the user agents
    */
    std::string getUserAgents();

    /**
    * Sets the value for the header field
    * @param value the value of the header field
    */
    void setMyValue(std::string value);

    /**
    * Sets the user agents this header field will apply to
    * @param myUserAgents sets the user agents this applies (* for all agents)
    */
    void setMyUserAgents(std::string myUserAgents);

    nCustomHeader(fCustomHeader* header);

  protected:
    fCustomHeader* getHeader();

  private:
    fCustomHeader* myHeader;
    friend class nHTTPInterface;
};
}
}
}
}
#endif
