/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NNODEUTILITIES_H
#define NNODEUTILITIES_H



#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {
class nRealmNode;

class nNodeUtilities {
  public:
  	/**
     * Searches the list of known realms for a realm node with the name given by realmName
     * @param realmName The name of the realm to find.
     * @return If the realm node is known, then it returns the instance of nRealmNode for this realm. Otherwise this method will return null.
     */
    static nRealmNode* findRealmNode(const std::string& realmName);
  private:
    nNodeUtilities(void);
    virtual ~nNodeUtilities(void);
};

}
}
}
}

#endif
