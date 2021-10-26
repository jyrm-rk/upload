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
#include "fBaseTransportObject.h"

#include <map>

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {

class fMissingKeyHandler;
class fObject;
class fDictionaryIterator;

class fEventDictionary :
    public fBaseTransportObject, public CountableObject {
  public:
    fEventDictionary(void);
    fEventDictionary(std::string& serialized);
    virtual ~fEventDictionary(void);

    virtual void readExternal(fEventInputStream *pEventInputStream);
    virtual void writeExternal(fEventOutputStream *pEventOutputStream);
    std::string getString(const std::string& key);
    longlong getLong(const std::string& key);
    longlong* getLongArray(const std::string& key, int& nLong);
    short getShort(const std::string& key);
    short* getShortArray(const std::string& key, int& nShort);
    int getInt(const std::string& key);
    int* getIntArray(const std::string& key, int& nInt);
    fObject* get(const std::string& key);
    fDictionaryIterator* getIterator ();
    void setSortOnWrite(bool flag);
    bool getSortOnWrite();
    void put(const std::string& key, const std::string& value);
    void put(const std::string& key, std::string* value, int nValue);
    void put(const std::string& key, int value);
    void put(const std::string& key, int* value, int nValue);
    void put(const std::string& key, longlong value);
    void put(const std::string& key, longlong* value, int nValue);
    void put(const std::string& key, short value);
    void put(const std::string& key, short* value, int nValue);
    void put(const std::string& key, bool value);
    void put(const std::string& key, bool* value, int nValue);
    void put(const std::string& key, float value);
    void put(const std::string& key, float* value, int nValue);
    void put(const std::string& key, double value);
    void put(const std::string& key, double* value, int nValue);
    void put(const std::string& key, char value);
    void put(const std::string& key, char* value, int nValue);
    void put(const std::string& key, unsigned char value);
    void put(const std::string& key, unsigned char* value, int nValue);
    void put(const std::string& key, fEventDictionary *pValue);
    void put(const std::string& key, fEventDictionary **pValue, int nValue);
    void put(const std::string& key, fObject *pObject);
    void copy(fEventDictionary *pDictionary, bool copyNew);
    void copy(fEventDictionary *pDictionary);
    void remove(const std::string& key);
    fEventDictionary* getDictionary(const std::string& key);
    fEventDictionary** getDictionaryArray(const std::string& key, int& nDict);
    bool containsKey(const std::string& key);
    std::string* getStringArray(const std::string& key, int& nString);
    bool getBoolean(const std::string& key);
    bool* getBooleanArray(const std::string& key, int& nBoolean);
    unsigned char getByte(const std::string& key);
    unsigned char* getByteArray(const std::string& key, int& nByte);
    char getChar(const std::string& key);
    char* getCharArray(const std::string& key, int& nChar);
    const std::string getClass(const std::string& key);
    std::map<std::string, fObject*>::iterator getKeyIterator();
    std::map<std::string, fObject*>::iterator getKeyEnd();
    double getDouble(const std::string& key);
    double* getDoubleArray(const std::string& key, int& nDouble);
    float getFloat(const std::string& key);
    float* getFloatArray(const std::string& key, int& nFloat);
    std::map<std::string, fObject*>& getEntrySet();
    int getSize();
    void merge(fEventDictionary *pDictionary, bool overwrite);

  protected:
    fObject* getObjectFromHash(const std::string& key);
    void writeItem(fEventOutputStream *pOstream, const std::string& key, fObject *pVal);
    void putObjectInHash(const std::string& key, fObject *val);
    fObject* removeObjectFromHash(const std::string& key);

    std::map<std::string, fObject*> m_hash;
    fMissingKeyHandler *m_pMissingHandler;

  private:
    void writeArray(fEventOutputStream *pOstream, fObject *pObj);
    fObject* readArray(fEventInputStream *pIstream);
    void deserialize(std::string& serialized);
    void extractKeyPair(std::string& keyPair);

    std::string m_lookup;
    bool m_bSortOnWrite;
    bool m_bIsValidDictionary;

    static const unsigned char c_String;
    static const unsigned char c_Long;
    static const unsigned char c_Double;
    static const unsigned char c_Boolean;
    static const unsigned char c_Integer;
    static const unsigned char c_Float;
    static const unsigned char c_Char;
    static const unsigned char c_Byte;
    static const unsigned char c_Short;
    static const unsigned char c_Dictionary;
    static const unsigned char c_Array;
    static const std::string s_delimiter;
};

}
}
}
}
