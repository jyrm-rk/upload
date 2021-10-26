/*
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include <string>
#include "nCachedChannelAttributes.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace nbase {
class nBaseChannelAttributes;

namespace events {

    class nPauseSub : public nCachedChannelAttributes {
    public:
        nPauseSub();
        nPauseSub(longlong attrib, long consumerID, const std::string &connectionID, bool pause);
        virtual ~nPauseSub();

        virtual const std::string getTypeString();
        virtual int getType();
        virtual bool isSynchronous();
        virtual void performRead(fEventInputStream *pIstream);
        virtual void performWrite(fEventOutputStream *pOstream);
        virtual nEvent* createInstance();

        bool isPause();
        longlong getConsumerID();
        std::string getConnectionID();

    private:
        longlong m_consumerID;
        bool m_pause;
        std::string m_connectionID;
    };
}
}
}
}
}
