/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fBase.h"

#ifndef BLOCKINGQUEUE_H
#define	BLOCKINGQUEUE_H

#include "fDriver.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace collections {
template<class T>
class BlockingQueue : public fbase::Countable{
  public:
    virtual void add(T driver)=0;
    virtual T poll(int waitTime)=0;
	virtual int size()=0;
};
}
}
}
}



#endif	/* BLOCKINGQUEUE_H */

