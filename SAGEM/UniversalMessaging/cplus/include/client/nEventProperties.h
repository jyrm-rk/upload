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
#include "fObject.h"
#include "nEventPropertiesIterator.h"

#include <string>
#include <map>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class fEventDictionary;
class fDictionaryIterator;
}
}
namespace nirvana {
namespace client {

class nSession;
class nEventPropertiesIterator;
class nEventPropertyChangeListener;

using namespace foundation::fbase;

/**
 * This class contains a collection of key-value pairs, defining event meta
 * data which can be used to create filter rules.
 */
class nEventProperties : public fObject {
  public:
    /**
     * Default constructor
     */
    DLL nEventProperties(void);
    // This constructor is used by the Python build
    DLL nEventProperties(fEventDictionary *pEd);
    DLL virtual ~nEventProperties(void);

    /**
    * Constructs an event properties object that is a copy of the specified
    * event properties.
    *
    * @param *pEd the event properties object to be copied
    */
    DLL nEventProperties(nEventProperties *pEd, bool bCopyNew = true);

    /**
    * Retrieves a string by the name given
    *
    * @param key Name for the string
    * @return string value
    */
    DLL std::string getString(const std::string& key);

    /**
    * Retrieves a longlong by the name given
    *
    * @param key Name for the long
    * @return long value
    */
    DLL longlong getLong(const std::string& key);

    /**
    * Retrieves an int by the name given
    *
    * @param key Name for the int
    * @return int value
    */
    DLL int getInt(const std::string& key);

    /**
    * Retrieves a string array by the name given
    *
    * @param key Name for the string array
    * @param nString The number of strings
    * @return string array
    */
    DLL std::string* getStringArray(const std::string& key, int& nString);

    /**
    * Retrieves an nEventPropertiesIterator*
    * @return nEventPropertiesIterator*
    */
    DLL nEventPropertiesIterator* getIterator ();

    /**
    * Places a String into the properties
    *
    * @param key Name for the value
    * @param value String
    */
    DLL void put(const std::string& key, const std::string& value);

    /**
    * Places an int into the properties
    *
    * @param key Name for the value
    * @param value int
    */
    DLL void put(const std::string& key, int value);

    /**
    * Places a longlong into the properties
    *
    * @param key Name for the value
    * @param value longlong
    */
    DLL void put(const std::string& key, longlong value);

    /**
    * Places a short into the properties
    *
    * @param key Name for the value
    * @param value short
    */
    DLL void put(const std::string& key, short value);

    /**
    * Places a bool into the properties
    *
    * @param key Name for the value
    * @param value bool
    */
    DLL void put(const std::string& key, bool value);

    /**
    * Places a float into the properties
    *
    * @param key Name for the value
    * @param value float
    */
    DLL void put(const std::string& key, float value);

    /**
    * Places a double into the properties
    *
    * @param key Name for the value
    * @param value double
    */
    DLL void put(const std::string& key, double value);

    /**
    * Places a char into the properties
    *
    * @param key Name for the value
    * @param value char
    */
    DLL void put(const std::string& key, char value);

    /**
    * Places an unsigned char into the properties
    *
    * @param key Name for the value
    * @param value unsigned char
    */
    DLL void put(const std::string& key, unsigned char value);

    /**
    * Put an nEventProperties into this one to enable nested properties
    *
    * @param key name of this value
    * @param *pValue nEventProperty to insert
    */
    DLL void put(const std::string& key, nEventProperties *pValue);

    /**
    * Retrieves an fObject* by the key given
    *
    * @param key string key to return
    * @return fObject of the value
    */
    DLL fObject* get(const std::string& key);

    /**
    * Retrieves an fObject* by the key given
    *
    * @param *pKey fObject
    * @return fObject*
    */
    DLL fObject* get(fObject *pKey);

    /**
    * Removes the value indexed by the key
    *
    * @param key Key to remove
    */
    DLL void remove(const std::string& key);

    /**
    * Retrieve nEventProperties from this one
    *
    * @param key Name of the nEventProperty
    * @return an nEventProperty
    */
    DLL nEventProperties* getDictionary(const std::string& key);

    /**
    * Return an array of nEventProperties
    *
    * @param key name of the array to return
    * @param nDict length of the dictionary array
    * @return nEventProperties[]
    */

    DLL nEventProperties** getDictionaryArray(const std::string& key, int& nDict);

    /**
    * Returns true if the key is contained within the dictionary
    *
    * @param key Name of the key to search for
    * @return True if the properties contains the key
    */
    DLL bool containsKey(const std::string& key);

    /**
    * Copies the properties from one to this
    *
    * @param *pDictionary dictionary to copy
    */

    DLL void copy(nEventProperties *pDictionary);

    /**
    * Retrieves the data from the table based on the key as a bool
    *
    * @param key Key to reference the data
    * @return a bool with the value associated with this key
    */

    DLL bool getBoolean(const std::string& key);

    /**
    * Retrieves a bool[] from the properties
    *
    * @param key Name of the bool[]
    * @param &nBoolean length of the array
    * @return bool[]
    */

    DLL bool* getBooleanArray(const std::string& key, int &nBoolean);

    /**
    * Retrieves a byte by the name given
    *
    * @param key Name for the byte
    * @return byte value
    */

    DLL unsigned char getByte(const std::string& key);

    /**
    * Retrieves a byte[] from the dictionary
    *
    * @param key name for the byte[]
    * @param &nByte length of the array
    * @return byte[]
    */

    DLL unsigned char* getByteArray(const std::string& key, int &nByte);

    /**
    * Retrieves a char from the properties
    *
    * @param key name of the char
    * @return char
    */

    DLL char getChar(const std::string& key);

    /**
    * Retrieves a char[] from the properties
    *
    * @param key name of the char array
    * @param &nChar length of the array
    * @return char[]
    */

    DLL char* getCharArray(const std::string& key, int &nChar);

    /**
    * Get the class name of the value represented by the key
    *
    * @param key String value to lookup
    * @return String class name of the value
    */

    DLL const std::string getClass(const std::string& key);

    /**
    * Retrieves the data from the table based on the key as a double
    *
    * @param key Key to reference the data
    * @return a double with the value associated with this key
    */

    DLL double getDouble(const std::string& key);

    /**
    * Retrieves a double[] from the properties
    *
    * @param key Name of the double[]
    * @param nDouble length of the array
    * @return double[]
    */

    DLL double* getDoubleArray(const std::string& key, int& nDouble);

    /**
    * Get an iterator of the key and values in an Map.Entry. Allows the user to get both the
    * key and value from one iteration of the nEventProperties.
    *
    * @return nEventPropertiesIterator Map.Entrys in the properties
    */

    DLL std::map<std::string, fObject*>& getEntrySet();

    /**
    * Retrieves a float from the properties
    *
    * @param key Name of the float
    * @return float value
    */

    DLL float getFloat(const std::string& key);

    /**
    * Retrieves a float[] from the properties
    *
    * @param key Name of the float[]
    * @param nFloat length of the array
    * @return float[]
    */

    DLL float* getFloatArray(const std::string& key, int& nFloat);

    /**
    * Gets an int[] from the properties
    *
    * @param key Name of the int[]
    * @param nInt length of the array
    * @return int[]
    */

    DLL int* getIntArray(const std::string& key, int& nInt);

    /**
    * Get an enumeration of keys
    *
    * @return enumerator of keys
    */

    DLL std::map<std::string, fObject*>::iterator getKeys();

    /**
    * Get an enumeration of keys as Strings
    *
    * @return an enumeration of String objects representing the keys
    */

    DLL std::map<std::string, fObject*>::iterator getKeysAsStrings();

    /**
    * Retrieves a long[] from the properties
    *
    * @param key Name of the long[]
    * @param nLong length of the array
    * @return long[]
    */

    DLL longlong* getLongArray(const std::string& key, int& nLong);

    /**
    * Retrieves a short from the properties
    *
    * @param key name of the short
    * @return short value
    */

    DLL short getShort(const std::string& key);

    /**
    * Retrieves an array of shorts
    *
    * @param key name of the short array
    * @param nShort length of the array
    * @return short[]
    */

    DLL short* getShortArray(const std::string& key, int& nShort);

    /**
    * Return the number of properties held
    *
    * @return int size
    */

    DLL int getSize();

    /**
    * Adds the values from the supplied properties to this object. If this object already has keys with
    * the same name then the behaviour is driven by the bool overwrite.
    * @param *pProps The nEventProperties object to merge with this copy
    * @param overwrite If true then duplicate values will take the new value
    */

    DLL void merge(nEventProperties *pProps, bool overwrite);

    /**
    * Places a double[] into the properties
    *
    * @param key Name of the double[]
    * @param nValue length of the array
    * @param value double[]
    */

    DLL void put(const std::string& key, double* value, int nValue);

    /**
    * Puts a float[] into the properties
    *
    * @param key Name of the float[]
    * @param nValue length of the value array
    * @param value float[]
    */

    DLL void put(const std::string& key, float* value, int nValue);

    /**
    * Places a long[] into the properties
    *
    * @param key name of the long[]
    * @param value long[]
    * @param nValue length of the value array
    */

    DLL void put(const std::string& key, longlong* value, int nValue);

    /**
    * Places a int[] into the properties
    *
    * @param key Name of the key
    * @param value int[]
    * @param nValue length of the value array
    */

    DLL void put(const std::string& key, int* value, int nValue);

    /**
    * Places a bool[] into the properties
    *
    * @param key Name of the boolean[]
    * @param value bool[]
    * @param nValue length of the value array
    */

    DLL void put(const std::string& key, bool* value, int nValue);

    /**
    * Puts an array of chars into the properties
    *
    * @param key Name of the char[]
    * @param c char[]
    * @param nValue length of the c array
    */

    DLL void put(const std::string& key, char* c, int nValue);

    /**
    * Places a byte[] into the properties
    *
    * @param key name for the byte[]
    * @param b byte[]
    * @param nValue length of the b array
    */

    DLL void put(const std::string& key, unsigned char* b, int nValue);

    /**
    * Places an array of shorts into the properties
    *
    * @param key Name for the array
    * @param s short[]
    * @param nValue length of the s array
    */

    DLL void put(const std::string& key, short* s, int nValue);

    /**
    * Places a String[] into the properties
    *
    * @param key Name for the value
    * @param value String[]
    * @param nValue length of the value array
    */

    DLL void put(const std::string& key, std::string* value, int nValue);

    /**
    * Put an nEventProperties[] into this property to enable nested properties
    *
    * @param key Name to call this
    * @param value Array of nEventProperties
    * @param nValue length of the value array
    */

    DLL void put(const std::string& key, nEventProperties** value, int nValue);

    virtual int getType();
    void registerListener(nEventPropertyChangeListener *pUpdateListener);
    std::map<std::string, fObject*>::iterator getKeysEnd();

  protected:
    fEventDictionary *m_pDictionary;

  private:
    static const int KEY = 0;
    static const int SET = 2;
    static const int VAL = 1;
    nEventPropertyChangeListener *m_pListener;

    friend class nSession;
    friend class nChannelImpl;
    friend class nConsumeEventConverter;
    friend class nRegisteredEvent;

};

}
}
}
}
