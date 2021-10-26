/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Transport.h"
#include "fDriver.h"
#include "Stream.h"
#include <memory>

using namespace com::pcbsys::foundation::drivers;



namespace com {
namespace softwareag {
namespace umtransport {
class TransportFactory;
class SynchronousServerTransport;
/// <summary>
/// This Transport represents a client connection.  It is created on the client side using TransportFactory.connect
/// and on the server side using SynchronousServerTransport.accept().  Read and write calls to this Transport
/// are blocking calls.
/// </summary>
class UMTRANSPORTDLL SynchronousTransport : public Transport {
  private:
    class Impl;
    std::unique_ptr<Impl> m_Impl;

    SynchronousTransport(fDriver *drv);
    friend class TransportFactory;
    friend class SynchronousServerTransport;

  public:
    class UMTRANSPORTDLL InputStream {
      private:
        class Impl;
        std::unique_ptr<Impl> m_Impl;

        virtual int actualRead(unsigned char *pBuffer, int offset, int length);
      public:
        InputStream(fDriver *drv);
        virtual ~InputStream();
        int read(unsigned char *pBuffer, int length);
        int read(unsigned char *pBuffer, int offset, int length);
    };

    class UMTRANSPORTDLL OutputStream {
      private:
        class Impl;
        std::unique_ptr<Impl> m_Impl;

        virtual void actualWrite(unsigned char *pBuffer, int offset, int length);
      public:
        OutputStream(fDriver *drv);
        virtual ~OutputStream();
        void write(unsigned char *pBuffer, int length);
        void write(unsigned char *pBuffer, int offset, int length);
        void flush();
    };

    ~SynchronousTransport();

    virtual bool isClosed();
    virtual void close();

    /// <summary>
    /// Get the InputStream for this Transport.  This can be used to read data sent by/to the client.
    /// </summary>
    /// <returns> the InputStream for this client Transport </returns>
    InputStream &getInputStream();

    /// <summary>
    /// Get the OutputStream for this Transport.  This can be used to write data to the client/server.
    /// </summary>
    /// <returns> OutputStream for this client Transport </returns>
    OutputStream &getOutputStream();
};
}
}
}