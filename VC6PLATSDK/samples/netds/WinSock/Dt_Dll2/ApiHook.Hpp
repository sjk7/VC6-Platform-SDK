// Filename  : APIHook.hpp
// Abstract  : This template class encapsulates API function return
//             information, invoking library information, and whether
//             a DT hook is a 'pre' or 'post' notification.  This class
//             really exists to make DTHandler.cpp less cluttered code.
// Author    : Jeffrey C. Venable, Sr.
// Copyright : THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT
//             WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,
//             INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
//             MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
//             Copyright (C) 1998 - 2001,  Microsoft Corporation.
//             All rights reserved.

#ifndef _APIHOOK_HPP
#define _APIHOOK_HPP

template<class T>
class APIHook {

    APIHook();

    const T *_rValue;
    const char *const _libName;
    const bool _preAPI;

public :

    APIHook(const T *returnValue, const char *const libraryName, const bool preAPI) :
            _rValue(returnValue), _libName(libraryName), _preAPI(preAPI) {}

    inline const T *
    rValue() { return (_rValue); }

    inline const char *const
    libName() { return (_libName); }

    inline const bool
    preAPI() { return (_preAPI); }

}; // class APIHook

#endif
