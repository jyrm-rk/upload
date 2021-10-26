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
#include "Exception.h"
#include "fLogListener.h"

#include "Poco/Mutex.h"

#include <string>
#include <vector>
#include <stdio.h>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class DLL fLogger {
  public:
    fLogger(FILE *pFile);
    virtual ~fLogger(void);

    static fLogger log;
    static const int sSuccess = 0;  // Normal operation.  Typically used for verbose
    static const int sInformative = 1; // Normal status changes or such
    static const int sWarning = 2;  // Something is wrong but can be handled
    static const int sFailure = 3;  // A failure has occured but need not
    static const int sFatal = 4;    // This means that the system can not continue
    static const int sSecurity = 5; // Used to log Security related entries
    static const int sAudit = 6;
    static const int sLog = 7;      // Just log the event

    static void setLogFile(FILE *file);

    void report (const std::string& val);
    void report (int logLevel, const std::string& val);
    void report (int logLevel, Exception& e);
    void report (int logLevel, Poco::Exception& e);

    void report (int logLevel, const std::exception& e);
    void report (int logLevel, const Poco::Exception& e);

    static void println(int logLevel, const std::string& msg);
    static void println(int logLevel, Exception& e);
    static void println(int logLevel, Poco::Exception& e);
    static void println(int logLevel, const Poco::Exception& e);
    static void println(int logLevel, const std::exception& e);


    static bool canLog (int logLevel);
    static void setLogLevel(int logLevel);
    static int getLogLevel();

    static bool isDebugEnabled();
    static void setDebugEnabled(bool enable);
    static void println(Exception& e);
    static void println(Poco::Exception& e);

    static void addListener(fLogListener* lis);
    static void delListener(fLogListener* lis);
    static void delAllListeners();

  protected:
    FILE *m_pFile;

  private:
    int m_logLevel;
    static bool m_bDebug;
    Poco::Mutex m_mutex;
    std::vector<fLogListener*> myListeners;
};

}
}
}
}

