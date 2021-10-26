/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fExternalable.h"
#include "fBase.h"
#include <string>

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nAdmin {

	using namespace com::pcbsys::foundation::io;
	using namespace com::pcbsys::foundation::fbase;

	class nRemoteInterestEntry : public fExternalable {
	private:
		std::string m_channelName;
		bool m_canSend;
		bool m_canReceive;
		bool m_isDynamic;
	protected:
		bool m_hasInterest;
		//Default constructor
		nRemoteInterestEntry(void);
		//Copy constructor
		nRemoteInterestEntry(const nRemoteInterestEntry& entry);
		//Copy Assignment operator
        nRemoteInterestEntry& operator=(const nRemoteInterestEntry& entry);

		void init(const std::string& channelName, bool canSend, bool canReceive, bool isDynamic);
		void readState(longlong bitmask); 
		long packState(); 
	public:
		/**
		 * Creates a new remote interest entry for a given channel name
		 *
		 * @param channelName the name of the channel to set interest properties for
		 * @param canSend if set to true messages published to the corresponding channel will be propagated to realms
		 * @param canReceive if set to true messages from other realms will be propagated to this channel
		 */
		nRemoteInterestEntry(const std::string& channelName, bool canSend, bool canReceive);
		/**
		* Creates a new remote interest entry for a given channel name
		*
		* @param channelName the name of the channel to set interest properties for
		* @param canSend if set to true messages published to the corresponding channel will be propagated to realms
		* @param canReceive if set to true messages from other realms will be propagated to this channel
		* @param isDynamic if set to true the ability to receive messages from other realms will be dependent to whether there is a subscriber present on the given channel
		* @throws NullPointerException     The channel specified is null
		*/
		nRemoteInterestEntry(const std::string& channelName, bool canSend, bool canReceive, bool isDynamic);
		virtual ~nRemoteInterestEntry(void);

		/**
		 *
		 * @return returns the channel name for this entry
		 */
		std::string& getChannelName();
		std::string& getChannelName() const;
		/**
		 *
		 * @return returns true if the entry allows propagation of messages to other realms
		 */
		bool canSend();
		/**
		 *
		 * @param canSend if set to true will allow the propagation of messages to other realms for this channel
		 */
		void setCanSend(bool canSend);
		/**
		 *
		 * @return returns true if the entry allows receipt of messages from other realms
		 */
		bool canReceive();
		/**
		 *
		 * @param canReceive if set to true will allow the receipt of messages from other realms for this channel
		 */
		void setCanReceive(bool canReceive);

		/**
		 *
		 * @return returns true if receipt of messages from other realms is based on the presence of subscribers on the given channel.
		 */
		bool isDynamic();
		/**
		 *
		 * @return returns a clone of this object created on heap
		 */
		nRemoteInterestEntry* clone();

		bool Equals(const nRemoteInterestEntry* pEntry);
		bool operator==(const nRemoteInterestEntry& objEntry) const;

		static nRemoteInterestEntry* readEntry(fEventInputStream *fIstream);

		virtual void readExternal(fEventInputStream *fIstream);
		virtual void writeExternal(fEventOutputStream *fOstream);
	};
}
}
}
}