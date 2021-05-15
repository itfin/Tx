
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

	///< ��ȡ��ǰϵͳ������Ϣ.
	static std::string GetSysLastError();

	///< �����༶Ŀ¼.
	static bool create_multi_direct(const char *pDir);

	///< ��ȡ��ǰ��������Ŀ¼.
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

	///< ��ȡ��ǰ���г�������.
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

	///< ɾ��ָ��Ŀ¼�����е��ļ�.
	static std::string delete_all_file(const std::string& strPath);


	///< �ֽ�ת������
	static void convert_bytecode(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage);

	static void convert_bytecode(const char* inSet, const char* outSet, const char *inbuf, std::size_t inlen, char *outbuf, std::size_t outlen);

	///< �ֽ�ת������
	static void bytecode_gbk_to_utf8(const char *inbuf, std::size_t inlen, char *outbuf, std::size_t outlen);
	static void bytecode_utf8_to_gbk(const char *inbuf, std::size_t inlen, char *outbuf, std::size_t outlen);

	/*
	00����ֻ����ļ��Ƿ����
	02����дȨ��
	04������Ȩ��
	06������дȨ��
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
	/* ������ص�ͨ�ú�������                                                   */
	/************************************************************************/
	//////////////////////////////////////////////////////////////////////////

    //��ȡ��ǰʱ���������(��ǰֻ��linux��ʵ�֣�windowsδʵ��)
    static int64_t GetCurNanSecond();

	///< ��������clock()�Ĳ�ֵ����ȷ������.
	static time_point<high_resolution_clock> GetClockValue();

	///< ��������clock()�Ĳ�ֵ����ȷ������.
	static T_I64 GetDiffClock(time_point<high_resolution_clock> begin_t, time_point<high_resolution_clock> end_t);

	///< �Ƿ�������.
	inline static bool IsLeapYear(const int nYear)
	{
		return (((0 == nYear % 4) && (0 != nYear % 100)) || (0 == nYear % 400));
	}

	///< ��ȡϵͳ����ʱ�䣬��ת����"YYYY-MM-DD HH:MM:SS.xxx����ʽ�ַ���.
	static std::string GetStringFromSysDateTime();

	///< ��ȡϵͳ���ڣ���ת����"YYYY-MM-DD����ʽ�ַ���.
	static std::string GetStringFromSysDate();

	///< ��ȡϵͳʱ�䣬��ת����"HH:MM:SS����ʽ�ַ���.
	static std::string GetStringFromSysTime();

	///< ��ȡϵͳʱ�䣬��ת����"HH:MM:SS.xxx����ʽ�ַ���.
	static std::string GetStringFromSysTimeEx();

	///< ��ȡϵͳ���ڣ���ת����int����, YYYYMMDD.
	static int GetIntFromSysDate();

	///< ��ȡϵͳʱ�䣬��ת����int����,HHMMSS.
	static int GetIntFromSysTime();

	///< ��ȡϵͳʱ�䣬��ת����int����,HHMMSSxxx.
	static int GetIntFromSysTimeEx();

	///< ��ȡϵͳʱ�䣬��ת����YYYYMMDDHHMMSSxxx.
	static T_I64 GetI64FromSysDateTimeEx();

	///< ��ȡϵͳʱ�䣬��ת���ɺ���.
	static int GetMillsecondsFromSysTime();

	///< ��ȡָ�����ڵ�ǰһ��
	static int GetTheDayBefore(int nDate);

	///< ��ȡָ�����ĳ�·ݵ�����.
	static int GetTheMonthDays(const int& nYear, const int& nMonth);

	///< ������ת��������.
	static long ConvertDateToDays(const int nBaseYear, const int nYear, const int nMonth, const int nDay);

	///< ��ȡ��������֮��.
	static int GetTwoDatesDiif(const int nDate1, const int nDate2);

	///< ת������Ϊ��YYYY-MM-DD����ʽ�ַ���.
	static std::string ConvertStringFromDate(int nDate);

	///< ת��ʱ��Ϊ��HH:MM:SS����ʽ�ַ���.
	static std::string ConvertStringFromTime(int nTime);

	///< ת��ʱ��Ϊ��HH:MM:SS.xxx����ʽ�ַ���.
	static std::string ConvertStringFromTimeEx(int nTime);

	///< ת����YYYY-MM-DD����ʽ�ַ���ΪYYYYMMDD����.
	static int ConvertIntDateFromString(const char* szDate);

	///< ת����HH:MM:SS����ʽ�ַ���ΪHHMMSSʱ��.
	static int ConvertIntTimeFromString(const char* szTime);

	///< ��ָ��������ת����"HH:MM:SS.xxx����ʽ�ַ���.
	static std::string ConvertStringFromMillseconds(int nMillseconds);

	///< ��ָ����ʱ��ת���ɺ���.
	static int ConvertMillsecondsFromTime(int nTime);

	///< ��ָ�������ڶ�Ӧ������, 0��1��2��3��4��5��6 ��ʾ���ա���һ���ܶ������������ġ����塢����.
	static int ConvertWeeksFromDate(int nDate);

	///< �ж��Ƿ�Ϊ��Ʊ����ʱ��.
	static bool IsStockMarketOptenTime(std::string& strOpenTime);
	//////////////////////////////////////////////////////////////////////////

	///< ��ȡһ���ڵ��������ڶ��ڵ������б�
	static int GetTwoDateMidDateList(int nStartDate, int nEndDate, std::vector<int>& vecDate);

	///< �Ƿ����0.
	static bool CompareDoubleData(const double dData);

	///< �Ƿ����0.
	static bool UnCompareDoubleData(const double dData);

	///< �ۼӺ�У��.
	static unsigned int GenerateCheckSum(char *buf, unsigned int bufLen);
	
	///< ȥ���ַ����ұߵĿո�.
	static void NullBlankspaceByLeft(char *szString, unsigned int nStrLen);

	static long long hton_int64(int val);

	static long long ntoh_int64(long long val);


	///< ����Idnum.	///< ����-1��ʾ��Ч.
	inline static int set_idnum_info(const int& nIndex, const int& nMarketID, const int& nFlag)
	{
		if (0 <= nFlag && 10 > nFlag)
		{
			return (nIndex * 1000 + nFlag * 100 + nMarketID);
		}
		return -1;
	}

	///< ����Idnum������nIdex,nMarketID,nFlag.
	inline static int get_idnum_info(const int& nIdNum, int& nMarketID, int& nFlag)
	{
		nMarketID = int(nIdNum % 100);
		nFlag = int(nIdNum % 1000 / 100);
		return (nIdNum / 1000);
	}
	
	///< �Ƿ���ָ��֤ȯ����.
	static bool IsIndexSecurityCode(int nType);

	static void replace_str(const std::string& old_str, std::string& new_str, std::string& src_str);


	//////////////////////////////////////////////////////////////////////////
	///< ����Ӳ��֧�ֵĸ߾��ȼ�������Ƶ��
	static long long get_qp_time_frequency();

	///< ����Ӳ����ȷ����ʱ��
	static long long get_qp_time_counter();

	///< ���غ���ʱ��
	static double get_qp_time_millisecond(long long begin, long long end, long long freq);

	///< ����΢��ʱ��
	static double get_qp_time_microsecond(long long begin, long long end, long long freq);
	//////////////////////////////////////////////////////////////////////////

	///< ָ���ļ���Ŀ¼���Ƿ����
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
        //ɾ��·���µ������ļ�
        static std::string delete_all_file_windows(const std::string& strPath);
        static std::string delete_all_file_linux(const std::string& strPath);
};

#endif // !__COMMONFUNCTION_H__
