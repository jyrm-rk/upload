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

#include "fBase.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdminAPI {

/**
 * Provides an interface which allows the status of cluster conversions to be monitored
 */
class nClusterConversionStatus {
  public:
    nClusterConversionStatus(void);
    virtual ~nClusterConversionStatus(void);

    /**
     * Called to report the current status of cluster conversion.
     *
     * @param storeName       the name of the store currently being converted
     * @param currentEvent    the event on the store currently being converted
     * @param totalEvents     the total number of events in the store to be converted
     * @param storesRemaining the number of stores still to be converted
     */
    virtual void status(const std::string& storeName, longlong currentEvent, longlong totalEvents, int storesRemaining) = 0;
};

}
}
}
}
