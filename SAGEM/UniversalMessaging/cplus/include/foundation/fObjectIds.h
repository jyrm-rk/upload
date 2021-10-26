/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fObjectIds {
  public:
    fObjectIds(void);
    virtual ~fObjectIds(void);

    static const int sc_false = 0;
    static const int sc_true = 1;

    static const int sc_null = 20;
    static const int sc_Int = 21;
    static const int sc_Long = 22;
    static const int sc_Float = 23;
    static const int sc_String = 24;
    static const int sc_ByteArray = 25;

    static const int sc_Vector = 30;
    static const int sc_Queue = 31;
    static const int sc_SortedMap = 32;
    static const int sc_Stack = 33;

    static const int sc_nExternalable = 45;
    static const int sc_fBaseEvent = 46;

    static const int sc_Object = 50;

    static const int sc_byteSize = 1;
    static const int sc_intSize = 4;
    static const int sc_longSize = 8;
};

}
}
}
}

