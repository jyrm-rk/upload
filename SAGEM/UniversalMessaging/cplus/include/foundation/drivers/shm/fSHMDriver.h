/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FSHMDRIVER_H
#define FSHMDRIVER_H

#include "MapManager.h"
#include "fDriver.h"
#include "Stream.h"
#include "Poco/Timespan.h"
#include "ByteBuffer.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace shm {
class MemoryMappedInputStream;
class MemoryMappedOutputStream;
class MemoryMap;
class DirectBufferAccess;

class DLL fSHMDriver : public fDriver {

  private:

    MemoryMappedInputStream* myInputStream;

    MemoryMappedOutputStream* myOutputStream;

    MemoryMap* m_serverConnectMap;
	ByteBuffer *m_map;

    DirectBufferAccess* m_dba;

    void connectToServer(std::string pathName);

    void setupStreams(std::string fileName, std::string in, std::string out, int bufferSize);

    longlong myTimeout;

    std::string myPath;

    bool isClosed;

  public:

    virtual ~fSHMDriver(void); // DLL in front

    fSHMDriver(std::string name, fLoginContext* ctx);

    fSHMDriver(std::string basedir, std::string shareName, int bufferSize, fLoginContext* ctx);

    void close();

    fSubject* getSubject();

    void setSubject(fSubject* sub);

    virtual Stream* getOutputStream();

    virtual Stream* getInputStream();

    void setTimeout(Poco::Timespan value);

    int getTimeout();

    virtual bool isIPC();

    const std::string getId();

    const std::string getLocalId();

    int getLocalPort();

    bool supportAsyncReading();

    bool supportAsyncWriting();

    fConnectionDetails* getConnectionDetails();

    bool isSecure();

    bool hasTimedOut(); // DLL in front

    virtual int getType() {	// DLL in front
        return fBase::SHMDRIVER;
    }

    /*class CloseExitHandler : Poco::Runnable {
    private:
      fSHMDriver* parent
    public:
    CloseExitHandler();

      void shutdown();

      void run();

    };*/

};
}
}
}
}
}

#endif
