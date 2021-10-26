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
#include <string.h>

namespace Poco {
	namespace Net {
		class StreamSocket;
	}
}

namespace com {
	namespace pcbsys {
		namespace foundation {
			namespace Net {

				class TcpStream :
					public fCommonStream {
				public:
					virtual ~TcpStream(void);
					DLL TcpStream(Poco::Net::StreamSocket *pSocket);

				protected:
					virtual void send(unsigned char* pBuffer, int length);
					virtual int receive(unsigned char* pBuffer, int length);

				private:
					Poco::Net::StreamSocket *m_pSocket;

					friend class fSocketDriver;
					friend class fSSLSocketDriver;

				};

			}
		}
	}
}
