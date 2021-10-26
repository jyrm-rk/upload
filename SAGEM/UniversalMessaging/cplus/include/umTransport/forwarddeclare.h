/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
/*! \namespace com.softwareag.umtransport
Documentation for the Universal Messaging C++ I/O API
*/
#ifdef WIN32
#ifdef IMPORT
#define UMTRANSPORTDLL __declspec(dllimport)
#else
#define UMTRANSPORTDLL __declspec(dllexport)
#endif
#else
#define UMTRANSPORTDLL
#endif

//class fAcceptHandler {};								// TransportFactory.h
//class fDriver {};										// TransportFactory.h
//class fServerDriver {};									// TransportFactory.h



//class Closeable {};										// Transport.h
//class AutoCloseable {};									// Transport.h
//class ByteBuffer {};									// DataHandler.h
//class fAsyncReadListener {};							// AsynchronousTransport.h
class fWriteReadyCallback {};							// AsynchronousTransport.h
//class InputStream {};									// AsynchronousTransport.h, SynchronousTransport.h
//class OutputStream {};									// AsynchronousTransport.h, SynchronousTransport.h
//class fDriverConfig {};									// ServerTransportContext.h, ServerSHMTransportContext.h
//class fLogListener {};									// Logger.h
//class fSharedMemoryConfig {};							// ServerSHMTransportContext.h
class URL {};											// ServerSHMTransportContext.h
class fRDMAConfig {};									// ServerRDMATransportContext.h
//class fSocketConfig {};								// ServerSocketTransportContext.h
//class fBaseDriverConfig : public fDriverConfig {};		// ServerSocketTransportContext.h
//class fSSLConfig {};									// ServerSSLTransportContext.h
