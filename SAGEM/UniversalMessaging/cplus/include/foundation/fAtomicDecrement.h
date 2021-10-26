/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef FATOMICDECREMENT_H
#define	FATOMICDECREMENT_H

#include "Poco/AtomicCounter.h"

class fAtomicDecrement {
public:
    fAtomicDecrement(Poco::AtomicCounter& counter);
    virtual ~fAtomicDecrement();
private:

    Poco::AtomicCounter& count;
};

#endif	/* FATOMICDECREMENT_H */

