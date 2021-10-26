/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef NBASEBATCHEDCHANNEL_H
#define NBASEBATCHEDCHANNEL_H

#include "nSynchronous.h"

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
class nChannelAttributes;
class nBaseClientException;
}
namespace nbase {
namespace events {
using namespace com::pcbsys::nirvana::client;
class nBaseBatchedChannel : public nSynchronous {
  public:

    struct fExternalableHolder {
        fExternalable* obj;
        unsigned char type;

        fExternalableHolder(fExternalable* _obj,unsigned char _type) {
            obj = _obj;
            type=_type;
        }
        ~fExternalableHolder() {
            delete obj;
        }
    };

    static const unsigned char sCHANNEL = 0;
    static const unsigned char sSECURITY = 1;
    static const unsigned char sEXCEPTION = 2;
    static const unsigned char sMAKE = 3;
    static const unsigned char sDELETE = 4;

    nBaseBatchedChannel();

    ~nBaseBatchedChannel();

    nBaseBatchedChannel(int id);

    void setRequestAttributes(std::vector<fExternalable*>* attrib);

    void setResponseAttributes(std::vector<fExternalableHolder*>* attrib);

    virtual fExternalable* getRequestAttribute() = 0;

    std::vector<fExternalableHolder*>* getResults();

    std::vector<fExternalable*>* getRequestAttributes();

    nChannelAttributes** getAttributes(int& sizeofArr);

    nBaseClientException** getExceptions(int& sizeofArr);

  protected:
    std::vector<fExternalable*>* myRequestAttributes;
    std::vector<fExternalableHolder*>* myResponseAttributes;

    fExternalableHolder* getResponseAttribute(unsigned char type);

    unsigned char getResponseAttributeType(fExternalableHolder* attr);

    void performRead( fEventInputStream* ois );

    void performWrite( fEventOutputStream* oos );

};
}
}
}
}
}

#endif
