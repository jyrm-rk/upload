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
namespace nAdminAPI {

/**
 * Classes that implement this interface can register with the nRealmNode.addLogListener() to receive
 * the realms log events. Depending on the fLogger setting in the configuration for the realm this could
 * result in a large amount of data being delivered.
 */
class nLogListener {
  public:
    DLL nLogListener(void);
    virtual DLL ~nLogListener(void);

    /**
     * This method is called by the nRealmNode to inform the user object of a new log event. The event
     * contains the date/time, the severity and the text of the event
     *
     * @param message date/time:severity:text message
     */
    virtual void report(const std::string& message) = 0;
};

}
}
}
}
