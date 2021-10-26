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
#include <stdio.h>
#include <string>

namespace com {
namespace pcbsys {
namespace foundation {
namespace io {
class fEventInputStream;
}
namespace fbase {

using namespace io;

class fEventDictionary;

class fObject : public CountableObject {
  public:
    DLL fObject(void);
    DLL fObject(unsigned char val);
    DLL fObject(char val);
    DLL fObject(bool val);
    DLL fObject(short val);
    DLL fObject(int val);
    DLL fObject(longlong val);
    DLL fObject(float val);
    DLL fObject(double val);
    DLL fObject(const std::string& str);
    DLL fObject(fEventDictionary* pDict);
    DLL fObject(unsigned char* val, int size);
    DLL fObject(char* val, int size);
    DLL fObject(bool* val, int size);
    DLL fObject(short* val, int size);
    DLL fObject(int* val, int size);
    DLL fObject(longlong* val, int size);
    DLL fObject(float* val, int size);
    DLL fObject(double* val, int size);
    DLL fObject(std::string* val, int size);
    DLL fObject(fEventDictionary** val, int size);
	DLL operator fEventDictionary*() const;
	DLL operator fEventDictionary** () const;
    DLL virtual ~fObject(void);

	DLL int getUnsignedCharArraySize() const;
	DLL int getCharArraySize() const;
	DLL int getBoolArraySize() const;
	DLL int getShortArraySize() const;
	DLL int getIntArraySize() const;
	DLL int getLongLongArraySize() const;
	DLL int getFloatArraySize() const;
	DLL int getDoubleArraySize() const;
	DLL int getStringArraySize() const;
	DLL int getEventDictionaryArraySize() const;

    DLL int getType () const;
    DLL int getSize () const;
    DLL void toString (std::string& value);
    void read (fEventInputStream *pIstream);
    DLL const std::string getTypeString();

    DLL operator const std::string& () const;
    DLL operator longlong () const;
    DLL operator double () const;
    DLL operator float () const;
    DLL operator unsigned char () const;
    DLL operator char () const;
    DLL operator bool () const;
    DLL operator int () const;
    DLL operator short () const;
    DLL operator unsigned char* () const;
    DLL operator char* () const;
    DLL operator bool* () const;
    DLL operator short* () const;
    DLL operator int* () const;
    DLL operator longlong* () const;
    DLL operator double* () const;
    DLL operator float* () const;
    DLL operator std::string* () const;

    static const int STRING					= 1;
    static const int LONG					= 2;
    static const int INT					= 3;
    static const int BYTE					= 4;
    static const int BOOL					= 5;
    static const int STRINGARRAY			= 6;
    static const int LONGARRAY				= 7;
    static const int INTARRAY				= 8;
    static const int BYTEARRAY				= 9;
    static const int BOOLARRAY				= 10;
    static const int EVENTPROPERTIES		= 11;
    static const int EVENTPROPERTIESARRAY	= 12;
    static const int FLOAT					= 13;
    static const int DOUBLE					= 14;
    static const int EVENTDICTIONARY		= 15;
    static const int CHAR					= 16;
    static const int SHORT					= 17;
    static const int CHARARRAY				= 18;
    static const int SHORTARRAY				= 19;
    static const int FLOATARRAY				= 20;
    static const int DOUBLEARRAY			= 21;
    static const int EVENTDICTIONARYARRAY	= 22;

  protected:
	fObject *m_fromObject;

    int m_iValue;
    longlong m_lValue;
    float m_fValue;
    double m_dValue;
    char m_cValue;
    unsigned char m_ucValue;
    bool m_bValue;
    short m_sValue;
    std::string m_strValue;
    fEventDictionary *m_pDictValue;

	//m_npiValue(0), m_nplValue(0), m_npfValue(0), m_npdValue(0), m_npcValue(0), m_npucValue(0), m_npbValue(0), m_npsValue(0), m_npstrValue(0), m_nppDictValue(0)
    int *m_piValue;
	int m_npiValue;

    longlong *m_plValue;
	int m_nplValue;

    float *m_pfValue;
	int m_npfValue;

    double *m_pdValue;
	int m_npdValue;

    char *m_pcValue;
	int m_npcValue;

    unsigned char *m_pucValue;
	int m_npucValue;

    bool *m_pbValue;
	int m_npbValue;

    short *m_psValue;
	int m_npsValue;

    std::string *m_pstrValue;
	int m_npstrValue;

    fEventDictionary **m_ppDictValue;
	int m_nppDictValue;

    int m_size;
    int m_type;

    friend class fEventDictionary;
};

}
}
}
}

