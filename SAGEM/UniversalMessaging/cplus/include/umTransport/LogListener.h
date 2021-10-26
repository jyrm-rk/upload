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
#include <exception>


namespace com {
namespace softwareag {
namespace umtransport {
/// <summary>
/// This class provides a mechanism to override the default Logging within the umTransport code. This allows users to then log messaging using any log mechanism they want to use
///
/// </summary>
class LogListener {
  public:
    /// <summary>
    /// This call receives generic String messages to be logged
    /// </summary>
    /// <param name="message"> </param>
    virtual void log(const std::string &message) = 0;

    /// <summary>
    /// This call receives exceptions that have been thrown and need to be logged within the umTransport code base </summary>
    /// <param name="ex"> </param>
    virtual void log(const std::exception& ex) = 0;
};
}
}
}