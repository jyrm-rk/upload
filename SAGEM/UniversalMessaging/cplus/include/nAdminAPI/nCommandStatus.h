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

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

using namespace foundation::fbase;

/**
 * Any class implementing this interface can be used to find the current status of a request, for example a copy
 * operation of a nLeafNode. Useful if the command takes a long time, the caller can implement this interface and get the
 * current status and position.
 *
 * If the implementing class returns false the command is aborted at that point.
 */
class nCommandStatus : public CountableObject {
  public:
    /**
     * Callback method used to indicate the current status of the command
     *
     * @param percentComplete Percent of the command completed
     * @param eid current Event id the command is up to
     * @return boolean, if False causes the command to stop else continues.
     */
    virtual bool status(int percentComplete, longlong eid) = 0;
};

}
}
}
}
