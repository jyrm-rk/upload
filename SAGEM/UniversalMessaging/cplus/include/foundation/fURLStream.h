/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fCommonStream.h"
#include "fURLDriver.h"

#include <istream>

namespace com {
	namespace pcbsys {
		namespace foundation {
			namespace drivers {
				class fURLDriver;
			}
			namespace Net {

				using namespace drivers;

				class fURLStream :
					public fCommonStream {
				public:
					virtual ~fURLStream(void);

					virtual int length();
					virtual int position();
					virtual void setPosition(int position);
					virtual void close();

					void setInStream(std::istream *pInStream);

				protected:
					virtual void send(unsigned char* pBuffer, int length);
					virtual int receive(unsigned char* pBuffer, int length);

				private:
					DLL fURLStream(fURLDriver *pDriver);

					fURLDriver *m_pDriver;

					std::istream *m_pInStream;
					bool m_bClosed;
					friend class foundation::drivers::fURLDriver;
				};

			}
		}
	}
}
