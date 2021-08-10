#ifndef _stdafx_h_
#define _stdafx_h_

#ifndef STRICT
#define STRICT
#endif

#include <crtdbg.h>

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define MY_DEBUG_NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new MY_DEBUG_NEW
#endif

#include <windows.h>
#include <tchar.h>
#include <malloc.h>
#include "AgtSvr.h"
#include "AgtErr.h"


#endif
