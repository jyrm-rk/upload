/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef CONCURRENT_CONSTANTS_H
#define CONCURRENT_CONSTANTS_H

#include "fBase.h"
#include "Poco/Exception.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

namespace com {
namespace pcbsys {
namespace foundation {
namespace concurrent {
class ConcurrentConstants {

  public:
    static longlong SPIN_COUNT;
    static int LOCK_WAIT;
    static const bool sEnabled = true;

};
class ConcurrentConstantsInit {
  public:
    ConcurrentConstantsInit() {
        char sDefaultSpinCount[] = "1000000000";
        char sSpinWait[] = "1";

        if(ConcurrentConstants::sEnabled) {
            char* val = getenv("SPIN_COUNT");
            if(val == NULL) {
                val = sDefaultSpinCount;
            }
            longlong ival = 1000000000L;
            try {
                ival = atol(val);
            } catch (Poco::Exception& ignore) {
            }
            ConcurrentConstants::SPIN_COUNT = ival;
        } else {
            ConcurrentConstants::SPIN_COUNT = 100;
        }

        if(ConcurrentConstants::sEnabled) {
            int ival = 1;
            char* val = getenv("SPIN_WAIT");
            if(val == NULL) {
                val = sSpinWait;
            }
            try {
                ival = atoi(val);
            } catch (Poco::Exception& ignore) {
            }
            ConcurrentConstants::LOCK_WAIT = (int)ival;
        } else {
            ConcurrentConstants::LOCK_WAIT=100;
        }
    }
};


}
}
}
}


#endif
