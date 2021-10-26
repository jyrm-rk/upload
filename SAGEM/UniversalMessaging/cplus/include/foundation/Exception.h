/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef EXCEPTION_H
#define	EXCEPTION_H
#include "fBase.h"
#include "Poco/Exception.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
class Exception :
    public Poco::Exception {

  public:

    DLL Exception(const std::string& msg, int code = 0);
    /// Creates an exception.

    DLL Exception(const std::string& msg, const std::string& arg, int code = 0);
    /// Creates an exception.

    DLL Exception(const std::string& msg, const Exception& nested, int code = 0);
    /// Creates an exception and stores a clone
    /// of the nested exception.
        
    DLL Exception(const std::string& msg, const Poco::Exception& nested, int code = 0);
    /// Creates an exception and stores a clone
    /// of the nested exception.
    
    DLL Exception(const Exception& exc);
    /// Copy constructor.
    
    DLL virtual ~Exception() throw() {};
    /// Destroys the exception and deletes the nested exception.
};

}
}
}
}


#endif	/* EXCEPTION_H */

