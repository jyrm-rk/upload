/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fPrivateKeyPassPhraseHandler.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace drivers {


class PassphraseHandler : public ssl::fPrivateKeyPassPhraseHandler {
  public:
    PassphraseHandler();
    virtual ~PassphraseHandler(void);

    void onPrivateKeyRequested(std::string & privateKey);
};

}
}
}
}
