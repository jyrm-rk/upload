/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "nSynchronous.h"
#include "nRemoteInterestEntry.h"
#include <string>
#include <list>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {
namespace events {

	using namespace nbase::events;

	class nRemoteInterestEvent : public nSynchronous {
	private:
		int m_command;
		std::list<nRemoteInterestEntry*> m_remoteInterestEntries;
		//Copy Constructor
		nRemoteInterestEvent(const nRemoteInterestEvent& event) {}
		//Assignment operator
		nRemoteInterestEvent& operator=(const nRemoteInterestEvent& event) {}
		void releaseEntries();
	public:
		nRemoteInterestEvent(void);
		~nRemoteInterestEvent(void);
		
		nRemoteInterestEvent(int command);
		nRemoteInterestEvent(int command, nRemoteInterestEntry* entry);
		nRemoteInterestEvent(int command, std::list<nRemoteInterestEntry*>& entries);
		nRemoteInterestEvent(int command, std::string channelName, bool canSend, bool canReceive);

		int getCommand();
		std::list<nRemoteInterestEntry*>::iterator getIterator();

		int iteratorSize();
		void clearEntries();
		void addEntries(std::list<nRemoteInterestEntry*>& entries);
		std::list<nRemoteInterestEntry*>& getEntries();

		virtual nEvent* createInstance();
		virtual const std::string getTypeString();
		virtual int getType();
		virtual void readExternal(fEventInputStream *pEventInputStream);
		virtual void writeExternal(fEventOutputStream *pEventOutputStream);

		static const int ADD = 0;
		static const int DEL = 1;
		static const int GET = 2;
		static const int REPLACE = 3;
	};
}
}
}
}
}