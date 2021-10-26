/*
 *
 *   Copyright (c) 1999 - 2011 my-Channels Ltd
 *   Copyright (c) 2012 - 2020 Software AG, Darmstadt, Germany and/or Software AG USA Inc., Reston, VA, USA, and/or its subsidiaries and/or its affiliates and/or their licensors.
 *
 *   Use, reproduction, transfer, publication or disclosure is prohibited except as specifically provided for in your License Agreement with Software AG.
 *
 */
#pragma once

#include "Poco/Exception.h"
#include <typeinfo>
#define API



namespace com {
namespace softwareag {
namespace umtransport {
POCO_DECLARE_EXCEPTION(API, IllegalArgumentException, Poco::Exception)
}
}
}
