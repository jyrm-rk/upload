/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "fObject.h"
#include "fEventDictionary.h"

#include <string>

using namespace com::pcbsys::foundation::io;
using namespace com::pcbsys::foundation::fbase;

namespace com {
namespace pcbsys {
namespace nirvana {
namespace client {
/**
 * This class is a holder for different types of object.
 * It is used in situations where a function needs to return various different types of object for example it is used
 * in conjunction with the nEventPropertiesIterator which, on each iteration, may return a different object type.
 *
 * An nObject can be cast to whatever object it contains e.g. int x = (int)nobject;
 *
 * @see nEventProperties
 * @see nEventPropertiesIterator
 */
class nObject : public fObject {
  public:
    nObject(void);
    DLL virtual ~nObject(void);

    /**
    * Construct a new nObject which holds an unsigned char
    * @param val the value to be held in the nObject
    */
    DLL nObject(unsigned char val):fObject(val) {};
    /**
    * Construct a new nObject which holds a char
    * @param val the value to be held in the nObject
    */
    DLL nObject(char val):fObject(val) {};
    /**
    * Construct a new nObject which holds a boolean
    * @param val the value to be held in the nObject
    */
    DLL nObject(bool val):fObject(val) {};
    /**
    * Construct a new nObject which holds a short
    * @param val the value to be held in the nObject
    */
    DLL nObject(short val):fObject(val) {};
    /**
    * Construct a new nObject which holds an int
    * @param val the value to be held in the nObject
    */
    DLL nObject(int val):fObject(val) {};
    /**
    * Construct a new nObject which holds a long
    * @param val the value to be held in the nObject
    */
    DLL nObject(longlong val):fObject(val) {};
    /**
    * Construct a new nObject which holds a float
    * @param val the value to be held in the nObject
    */
    DLL nObject(float val):fObject(val) {};
    /**
    * Construct a new nObject which holds a double
    * @param val the value to be held in the nObject
    */
    DLL nObject(double val):fObject(val) {};
    /**
    * Construct a new nObject which holds a string
    * @param str the value to be held in the nObject
    */
    DLL nObject(const std::string& str):fObject(str) {};
    /**
    * Construct a new nObject which holds an fEventDictionary*
    * @param pDict the value to be held in the nObject
    */
    DLL nObject(fEventDictionary* pDict):fObject(pDict) {};
    /**
    * Construct a new nObject which holds an array of unsigned chars
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(unsigned char* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of chars
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(char* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of booleans
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(bool* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of shorts
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(short* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of ints
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(int* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds a array of longs
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(longlong* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of floats
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(float* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of doubles
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(double* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of strings
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(std::string* val, int size):fObject(val,size) {};
    /**
    * Construct a new nObject which holds an array of fEventDictionary*
    * @param val the value to be held in the nObject
    * @param size the number of elements in the array
    */
    DLL nObject(fEventDictionary** val, int size):fObject(val,size) {};

    /**
    * Return the type of the value contained in the nEventProperties
    */
    DLL int getType ();

    /**
    * If it is an array of objects, return the size of the array
    */
    DLL int getSize ();

    /**
    * Convert the object to a string
    */
    DLL void toString (std::string& value);

    /**
    * Return the type as a String representation, for example, LONG, STRING etc. etc.
    */
    DLL const std::string getTypeString();

	//
	// Wrap around the fObject class to get direct access to the underlying object.  Used for
	// comparison operations with other nObjects.
	//
	DLL nObject(fObject *obj);

};

}
}
}
}

