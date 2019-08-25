/********************************************************************
	company:    北京睿智融科控股有限公司
	fileName:	XtDef.h
	author:		xujun    
	created:	8:11:2013   15:38	
	purpose:	宏定义
*********************************************************************/
#ifndef XtDef_2013_11_8_H
#define XtDef_2013_11_8_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include <map>
#include <set>

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_XT_API_EXPORT
#define XT_API_EXPORT __declspec(dllexport)
#else
#define XT_API_EXPORT __declspec(dllimport)
#endif
#else
#define XT_API_EXPORT 
#endif

namespace xti
{

}


#endif