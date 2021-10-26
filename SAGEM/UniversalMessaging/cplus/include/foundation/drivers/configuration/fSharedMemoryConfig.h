/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FSHAREDMEMORYCONFIG
#define FSHAREDMEMORYCONFIG

#include "fDriverConfig.h"


namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fSharedMemoryConfig : public fDriverConfig {

  public:
    DLL fSharedMemoryConfig();

    DLL fSharedMemoryConfig(std::string name, std::string adapter, int port, int timeout, bool autoStart = true);

    DLL fSharedMemoryConfig(std::string name, std::string protocol, std::string adapter, int port, int timeout, bool autoStart);

    std::string getBaseDirectory();

    void setBaseDirectory(std::string directory);

    DLL int getBufferSize();

    DLL void setBufferSize(int bufSize);

    void readExternal(fEventInputStream* eis);

    void writeExternal(fEventOutputStream* eos);

    int getType();

    DLL void setTimeout(int timeout);
    DLL int getTimeout();

};
}
}
}
}
}

#endif

