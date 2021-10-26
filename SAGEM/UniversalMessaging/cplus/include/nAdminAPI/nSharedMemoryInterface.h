/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NSHAREDMEMORYINTERFACE
#define NSHAREDMEMORYINTERFACE



#include "nInterface.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {
namespace configuration {
class fSharedMemoryConfig;
class fHTTPConfig;
}
}
}
namespace nirvana {
namespace nAdminAPI {
class nSharedMemoryInterface : public nInterface {

  public:
    static const int sDefaultBufferSize = 1024000;
    static const int sDefaultTimeout = 20000;
    //
    //---------------------------------------------------------------------------
    // nHTTPInterface Constructors
    //---------------------------------------------------------------------------
    //


    /**
     * Creates a HTTP interface on the supplied adapter:port with the supplied autostart flag
     *
     * @param adapter   to bind to
     * @param port      to bind to
     * @param autostart Should be autostarted or not (default:true)
     * @throws nAdminIllegalArgumentException if adapter is null or the port range is invalid
     */
    nSharedMemoryInterface(std::string adapter, int port, bool autostart = true);

    /**
     * Creates a shared memory configuration with the supplied timeout and autostart flag
     *
     * @param path the path to use for the memory mapped files
     * @throws nAdminIllegalArgumentException if adapter is null or the port range is invalid
     */
    DLL nSharedMemoryInterface(std::string path);

    //
    //---------------------------------------------------------------------------
    // nHTTPInterface Interface
    //---------------------------------------------------------------------------
    //

    virtual ~nSharedMemoryInterface(void);

    /**
     * Get the path where the shared memory files wil be stored, default will be the temp directory on the host machine
     *
     * @return the directory path used by teh shared memory configurations
     */
    std::string getDirectoryPath();

    /**
     * Get the value for the Shared Memory Configuration read / write timeout
     *
     * @return the timeout value
    */
    int getTimeout();

    /**
     * Set the path where the shared memory files will be stored.
     *
     * @param path the path where the shared memory files will be created - such as /tmp or c:/temp
     */
    void setDirectoryPath(std::string path);

    std::string getURL();

    /**
     * Gets the size of the shared memory buffers used
     *
     * @return the size of the shared memory buffers
     */
    int getBufferSize();

    /**
     * Sets the size of the shared memory buffers used
     *
     * @param size of the shared memory buffer
     */
    void setBufferSize(int size);
    //
    //---------------------------------------------------------------------------
    // nHTTPInterface Inheritance Interface
    //---------------------------------------------------------------------------
    //

    nSharedMemoryInterface();

    nSharedMemoryInterface(std::string name, std::string protocol, std::string adapter,int port, bool autostart);

    int getType();

    bool isInterRealmAllow() override;

  protected:
    nSharedMemoryInterface(fSharedMemoryConfig* cfg, nInterfaceManager* im);

    fDriverConfig* convert();

    friend class nInterfaceStatus;

}; // End of nHTTPInterface Class
}
}
}
}

#endif
