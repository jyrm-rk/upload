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
#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {

using namespace foundation::fbase;

/**
 * This class contains the information about a single channel key. It contains the
 * name and the depth of the key.
 */
class nChannelPublishKeys : public CountableObject {
  public:

    virtual ~nChannelPublishKeys(void);
    /**
    * Constructs a publish key object to be used in the channel creation
    *
    * @param name name of the key
    * @param depth The number of unique values to keep in the channel
    * @exception nIllegalArgumentException If the name is invalid or the depth is less then 1
    */
    DLL nChannelPublishKeys(std::string name, int depth);

    /**
    * Returns the name of the publish key
    *
    * @return String name
    */
    DLL std::string getName();

    /**
    * Returns the depth of the publish key
    *
    * @return int depth
    */
    DLL int getDepth();

  private:
    std::string m_name;
    int m_depth;
};

}
}
}
}
