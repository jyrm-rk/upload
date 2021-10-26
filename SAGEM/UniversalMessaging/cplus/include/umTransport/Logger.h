/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "LogListener.h"
#include "fLogListener.h"
#include "TcpStream.h"
#include <string>
#include <list>
#include <stdexcept>
#include <memory>

using namespace com::pcbsys::foundation::fbase;
using namespace com::pcbsys::foundation::Net;



namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// The class used to log messages in UM Transport
/// </summary>
class Logger {
  private:
    class Impl;
    std::unique_ptr<Impl> m_Impl;

  public:
    /// <summary>
    /// Get the active Logger instance
    /// </summary>
    /// <returns> Logger the Logger instance which UM Transport is using </returns>
    DLL static Logger& getLogger();

    /// <summary>
    /// Adds a client provided LogListener to intercept all the log messages from the transport so they can be reported and logged in a
    /// custom mechanism
    /// </summary>
    /// <param name="listener"> LogListener to be added to the list </param>
    DLL void addLogListener(LogListener *listener);

    /// <summary>
    /// Removes an existing LogListener from the logging mechanism
    /// </summary>
    /// <param name="listener"> LogListener to be removed from the list
    /// </param>
    DLL void delLogListener(LogListener *listener);

    /// <summary>
    /// Write a message to a LogListener or stdout
    /// </summary>
    /// <param name="msg"> the message to log </param>
    DLL void log(const std::string& msg);

    /// <summary>
    /// Write the stack trace of the Throwable to stdout
    /// </summary>
    /// <param name="th"> the Throwable to log </param>
    DLL void log(const std::exception& ex);

  private:
    Logger();
    ~Logger();
    Logger(const Logger &logger);
    const Logger &operator=(const Logger& logger);
};
}
}
}