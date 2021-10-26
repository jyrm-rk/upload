/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once
#include "fMonitorable.h"
#include "fDriverConfig.h"
#include "fAcceptHandler.h"
#include "fServerDriver.h"
#include "fServerLoginContext.h"
#include "fSharedMemoryConfig.h"
#include "DirectBufferAccess.h"
#include "MemoryMap.h"
#include "SHMConstants.h"
#include <memory>

using namespace com::pcbsys::foundation::drivers::configuration;

namespace com {
	namespace pcbsys {
		namespace foundation {
			namespace drivers {
				namespace shm {

					class DLL fSHMServerDriver : public fServerDriver, public virtual fVendorDriver, public virtual com::pcbsys::foundation::base::fMonitorable {
					public:
						fSHMServerDriver(com::pcbsys::foundation::drivers::configuration::fSharedMemoryConfig* config, com::pcbsys::foundation::drivers::handlers::fAcceptHandler* aHandler, const std::string& alias);
						virtual ~fSHMServerDriver();

						fDriver* performAccept();
						virtual bool validate(fDriver* driver);
						void close();

					protected:
					private:
						fSharedMemoryConfig *m_config;
						fServerLoginContext *m_context;

						MemoryMap *m_memoryMap;
						DirectBufferAccess *m_bufferAccess;
						ByteBuffer *m_map;

						long m_currentId;
						int m_bufferSize;

						class LockFile;
						std::unique_ptr<LockFile> m_lockFile;
					};
				}

			}
		}
	}
}

