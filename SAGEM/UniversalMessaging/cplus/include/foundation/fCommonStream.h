/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */

#pragma once

#include "Stream.h"

#define MAX_BUFFER 10000

namespace com {
	namespace pcbsys {
		namespace foundation {
			namespace Net {
				class fCommonStream : public Stream {
				public:
					fCommonStream();
					virtual ~fCommonStream();

					virtual void write(unsigned char *pBuffer, int offset, int length);

					virtual int read(unsigned char *pBuffer, int length);
					virtual int read(unsigned char *pBuffer, int offset, int length);
					virtual int readNB(unsigned char *pBuffer, int offset, int length);

					virtual void flush();
					virtual int length();
					virtual int position();
					virtual int readByte();
					virtual void setPosition(int position);
					virtual void close();
				protected:
					virtual void send(unsigned char* pBuffer, int length) = 0;
					virtual int receive(unsigned char* pBuffer, int length) = 0;
				private:
					int read(unsigned char *pBuffer, int offset, int length, bool block);
					void checkCapacity(int length);

					unsigned char *m_writeBuffer;
					int m_writeCapacity;
					int m_writeLength;

					unsigned char m_readBuffer[MAX_BUFFER];
					int m_readLength;
					int m_readOffset;
				};
			}
		}
	}
}