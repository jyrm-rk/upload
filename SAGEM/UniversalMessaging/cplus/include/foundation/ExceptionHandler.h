/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#ifndef EXCEPTIONHANDLER_H
#define	EXCEPTIONHANDLER_H

#include "Poco/ErrorHandler.h"
#include "Poco/Exception.h"

namespace com {
namespace pcbsys {
namespace foundation {
namespace fbase {
    
class ExceptionHandler : public Poco::ErrorHandler  {

public:
    ExceptionHandler();
    virtual ~ExceptionHandler();

    virtual void exception(const Poco::Exception& exc);
            /// Called when a Poco::Exception (or a subclass)
            /// caused the thread to terminate.
            ///
            /// This method should not throw any exception - it would
            /// be silently ignored.
            ///
            /// The default implementation just breaks into the debugger.

    virtual void exception(const std::exception& exc);
            /// Called when a std::exception (or a subclass)
            /// caused the thread to terminate.		
            ///
            /// This method should not throw any exception - it would
            /// be silently ignored.
            ///
            /// The default implementation just breaks into the debugger.

    virtual void exception();
            /// Called when an exception that is neither a
            /// Poco::Exception nor a std::exception caused
            /// the thread to terminate.
            ///
            /// This method should not throw any exception -    
    
private:
    ErrorHandler* m_pPreviousHandler;

};
}
}
}
}

#endif	/* EXCEPTIONHANDLER_H */

