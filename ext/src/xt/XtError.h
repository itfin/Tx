/********************************************************************
	company:    北京睿智融科控股有限公司
	fileName:	XtError.h
	author:		xujun    
	created:	11:11:2013   9:51	
	purpose:	错误
*********************************************************************/
#ifndef XtError_2013_11_11_H
#define XtError_2013_11_11_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XtDef.h"

namespace xti
{
    class XT_API_EXPORT XtError
    {
    public:
        XtError();
        XtError(int errorID);
        XtError(int errorID, const std::string& msg);
        ~XtError();

        void setErrorId(int id);
        void setErrorMsg(const std::string& msg);

        bool isSuccess() const;

        int errorID() const;
        const char* errorMsg() const;

        bool operator!() const;  // true if no error

    private:
        int m_nErrorID;
        std::string m_strErrorMsg;
    };
}

#endif