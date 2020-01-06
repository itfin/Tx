
#ifndef __COMMONFUNCTION_H__
#define __COMMONFUNCTION_H__

#include <string>
#include <vector>
#include <time.h>

#include <chrono>
using namespace std::chrono;

#ifdef WIN32
#include <Windows.h>
#include <io.h>
#include <direct.h>
#pragma warning(disable:4996)
#else
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#endif

#include "JGDataTypesDef.h"


class CJGMDComFunc
{
public:
	/*inline static double get_memory_usage_of_process()
	{
		double dRet = 0;
		PROCESS_MEMORY_COUNTERS pmc;

		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof(statex);

		if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc)) && GlobalMemoryStatusEx(&statex))
			dRet = pmc.WorkingSetSize*1.0 / statex.ullTotalPhys;
		return dRet;
	}*/

	static  const std::string GBK;
	static  const std::string UTF8;

	inline static double get_memory_usage()
	{
		#ifdef _WIN32
		double dRet = 0;
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof(statex);

		if (GlobalMemoryStatusEx(&statex))
			dRet = statex.dwMemoryLoad * 0.01;
		return dRet;
        #else   
        return getMemoryInfo();
        #endif
		
	}

    static double getMemoryInfo()
    {
        FILE *fp = fopen("/proc/meminfo", "r");
        if (NULL == fp)
           return 0;

        char szTest[1000] = { 0 };
        char szBuffer[256] = { 0 };
        unsigned long total = 0;
        unsigned long available = 0;
        int i = 0;
        while (!feof(fp)){
            memset(szBuffer, sizeof(szBuffer), 0);
            fgets(szTest, sizeof(szTest) - 1, fp);
            if (i == 0) {
                sscanf(szTest, "%s%lu", szBuffer, &total);
            }
            if (i == 2) {
                sscanf(szTest, "%s%lu", szBuffer, &available);
                break;
            }
            i++;
        }
        fclose(fp);

        if (total == 0) {
            return 0;
        }
        double dRet = 0;
        dRet = double(total - available) / double(total);
        return dRet;
    }

	int static get_thread_amount();

	///< 获取当前系统错误信息.
	static std::string GetSysLastError();

	///< 创建多级目录.
	static bool create_multi_direct(const char *pDir);

	///< 获取当前程序运行目录.
	inline static std::string get_current_dir()
	{
		#ifdef _WIN32
		char szExePath[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szExePath, MAX_PATH);
		std::string strExeDir(szExePath);
		strExeDir = strExeDir.substr(0, strExeDir.find_last_of('\\'));
		return std::move(strExeDir);
		#else
		char pPath[256] = {0};
		getcwd(pPath, 256);
		return std::string(pPath);
		#endif
	}

	///< 获取当前运行程序名称.
	inline static std::string get_cur_app_exe()
	{
		#ifdef _WIN32
		char szAppExe[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szAppExe, MAX_PATH);
		return szAppExe;
		#else
		char pPath[256] = {0};
		int ret = readlink("/proc/self/exe", pPath, 256);
		pPath[ret] = '\0';
		return std::string(pPath);
		#endif
	}

	///< 删除指定目录下所有的文件.
	static std::string delete_all_file(const std::string& strPath);


	///< 字节转换函数
	static void convert_bytecode(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage);

	static void convert_bytecode(const char* inSet, const char* outSet, const char *inbuf, std::size_t inlen, char *outbuf, std::size_t outlen);

	///< 字节转换函数
	static void bytecode_gbk_to_utf8(const char *inbuf, std::size_t inlen, char *outbuf, std::size_t outlen);
	static void bytecode_utf8_to_gbk(const char *inbuf, std::size_t inlen, char *outbuf, std::size_t outlen);

	/*
	00——只检查文件是否存在
	02——写权限
	04——读权限
	06——读写权限
	*/
	inline static bool JustFileHasPermision(const std::string &file_name, unsigned int nMode)
	{
		if (file_name.empty()) return false;

		#if defined(_WIN32)  
		if (_access(file_name.c_str(), nMode) != -1)
		{
			return true;
		}
		#else
		if (0 == access(file_name.c_str(), nMode))
		{
			return true;
		}	
		#endif
		
		return false;
	}
	
	/************************************************************************/
	/* 日期相关的通用函数处理                                                   */
	/************************************************************************/
	//////////////////////////////////////////////////////////////////////////

    //获取当前时间的纳秒数(当前只在linux下实现，windows未实现)
    static int64_t GetCurNanSecond();

	///< 返回两个clock()的差值，精确到毫秒.
	static time_point<high_resolution_clock> GetClockValue();

	///< 返回两个clock()的差值，精确到毫秒.
	static T_I64 GetDiffClock(time_point<high_resolution_clock> begin_t, time_point<high_resolution_clock> end_t);

	///< 是否是闰年.
	inline static bool IsLeapYear(const int nYear)
	{
		return (((0 == nYear % 4) && (0 != nYear % 100)) || (0 == nYear % 400));
	}

	///< 获取系统日期时间，并转换成"YYYY-MM-DD HH:MM:SS.xxx”格式字符串.
	static std::string GetStringFromSysDateTime();

	///< 获取系统日期，并转换成"YYYY-MM-DD”格式字符串.
	static std::string GetStringFromSysDate();

	///< 获取系统时间，并转换成"HH:MM:SS”格式字符串.
	static std::string GetStringFromSysTime();

	///< 获取系统时间，并转换成"HH:MM:SS.xxx”格式字符串.
	static std::string GetStringFromSysTimeEx();

	///< 获取系统日期，并转换成int数据, YYYYMMDD.
	static int GetIntFromSysDate();

	///< 获取系统时间，并转换成int数据,HHMMSS.
	static int GetIntFromSysTime();

	///< 获取系统时间，并转换成int数据,HHMMSSxxx.
	static int GetIntFromSysTimeEx();

	///< 获取系统时间，并转换成YYYYMMDDHHMMSSxxx.
	static T_I64 GetI64FromSysDateTimeEx();

	///< 获取系统时间，并转换成毫秒.
	static int GetMillsecondsFromSysTime();

	///< 获取指定日期的前一天
	static int GetTheDayBefore(int nDate);

	///< 获取指定年的某月份的天数.
	static int GetTheMonthDays(const int& nYear, const int& nMonth);

	///< 将日期转换成天数.
	static long ConvertDateToDays(const int nBaseYear, const int nYear, const int nMonth, const int nDay);

	///< 获取连个日期之差.
	static int GetTwoDatesDiif(const int nDate1, const int nDate2);

	///< 转换日期为“YYYY-MM-DD”格式字符串.
	static std::string ConvertStringFromDate(int nDate);

	///< 转换时间为“HH:MM:SS”格式字符串.
	static std::string ConvertStringFromTime(int nTime);

	///< 转换时间为“HH:MM:SS.xxx”格式字符串.
	static std::string ConvertStringFromTimeEx(int nTime);

	///< 转换“YYYY-MM-DD”格式字符串为YYYYMMDD日期.
	static int ConvertIntDateFromString(const char* szDate);

	///< 转换“HH:MM:SS”格式字符串为HHMMSS时间.
	static int ConvertIntTimeFromString(const char* szTime);

	///< 将指定的秒数转换成"HH:MM:SS.xxx”格式字符串.
	static std::string ConvertStringFromMillseconds(int nMillseconds);

	///< 将指定的时间转换成毫秒.
	static int ConvertMillsecondsFromTime(int nTime);

	///< 将指定的日期对应的星期, 0、1、2、3、4、5、6 表示周日、周一、周二、周三、周四、周五、周六.
	static int ConvertWeeksFromDate(int nDate);

	///< 判断是否为股票开市时间.
	static bool IsStockMarketOptenTime(std::string& strOpenTime);
	//////////////////////////////////////////////////////////////////////////

	///< 获取一年内的两个日期段内的日期列表
	static int GetTwoDateMidDateList(int nStartDate, int nEndDate, std::vector<int>& vecDate);

	///< 是否等于0.
	static bool CompareDoubleData(const double dData);

	///< 是否大于0.
	static bool UnCompareDoubleData(const double dData);

	///< 累加和校验.
	static unsigned int GenerateCheckSum(char *buf, unsigned int bufLen);
	
	///< 去除字符串右边的空格.
	static void NullBlankspaceByLeft(char *szString, unsigned int nStrLen);

	static long long hton_int64(int val);

	static long long ntoh_int64(long long val);


	///< 生成Idnum.	///< 返回-1表示无效.
	inline static int set_idnum_info(const int& nIndex, const int& nMarketID, const int& nFlag)
	{
		if (0 <= nFlag && 10 > nFlag)
		{
			return (nIndex * 1000 + nFlag * 100 + nMarketID);
		}
		return -1;
	}

	///< 根据Idnum解析出nIdex,nMarketID,nFlag.
	inline static int get_idnum_info(const int& nIdNum, int& nMarketID, int& nFlag)
	{
		nMarketID = int(nIdNum % 100);
		nFlag = int(nIdNum % 1000 / 100);
		return (nIdNum / 1000);
	}
	
	///< 是否是指数证券代码.
	static bool IsIndexSecurityCode(int nType);

	static void replace_str(const std::string& old_str, std::string& new_str, std::string& src_str);


	//////////////////////////////////////////////////////////////////////////
	///< 返回硬件支持的高精度计数器的频率
	static long long get_qp_time_frequency();

	///< 返回硬件精确计算时间
	static long long get_qp_time_counter();

	///< 返回毫秒时间
	static double get_qp_time_millisecond(long long begin, long long end, long long freq);

	///< 返回微秒时间
	static double get_qp_time_microsecond(long long begin, long long end, long long freq);
	//////////////////////////////////////////////////////////////////////////

	///< 指定文件（目录）是否存在
	static bool is_file_exist(const char* file);

	inline static long long str_to_ll(const char* str)
	{
#ifdef WIN32
		return _atoi64(str);
#else
		return atoll(str);
#endif
	}



	inline static std::string try_out_i64(T_I64 t_value)
	{
		char tmp[64] = { 0 };
#if defined(_MSC_VER)
	_snprintf_s(tmp, 64, 64, "%I64d", t_value);
#else
#ifdef __x86_64__
		snprintf(tmp, 64, "%ld", t_value);
#elif __i386__
		snprintf(tmp, 64, "%lld", t_value);
#endif
#endif
		return std::string(tmp);
	}

	inline static std::string try_out_u64(T_U64 t_value)
	{
		char tmp[64] = { 0 };
#if defined(_MSC_VER)
		_snprintf_s(tmp, 64, "%I64u", t_value);
#else
#ifdef __x86_64__
		snprintf(tmp, 64, "%lu", t_value);
#elif __i386__
		snprintf(tmp, 64, "%llu", t_value);
#endif
#endif
		return std::string(tmp);
	}

	static int get_cur_work_date(const T_I32& nDate);



    private:
        //删除路径下的所有文件
        static std::string delete_all_file_windows(const std::string& strPath);
        static std::string delete_all_file_linux(const std::string& strPath);
};

#endif // !__COMMONFUNCTION_H__
