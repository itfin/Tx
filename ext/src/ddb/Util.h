/*
 * Util.h
 *
 *  Created on: Sep 2, 2012
 *      Author: dzhou
 */

#ifndef UTIL_H_
#define UTIL_H_

#include <string.h>
#include <vector>
#include <unordered_set>
#include <ctime>
#include <cassert>
#ifdef _MSC_VER

#elif defined MAC
	#include <random>
#else
	#include <tr1/random>
#endif
#include <chrono>

#ifdef _MSC_VER
	#ifdef _DDBAPIDLL	
		#define EXPORT_DECL _declspec(dllexport)
	#else
		#define EXPORT_DECL __declspec(dllimport)
	#endif
#else
	#define EXPORT_DECL 
#endif

#include "DolphinDB.h"

namespace dolphindb {

class ConstantFactory;

class EXPORT_DECL Util {
public:
	static string VER;
	static int VERNUM;
	static string BUILD;
#ifdef _MSC_VER
	const static int BUF_SIZE = 1024;
#else
	const static int BUF_SIZE;
#endif
	static int DISPLAY_ROWS;
	static int DISPLAY_COLS;
	static int DISPLAY_WIDTH;
	static int CONST_VECTOR_MAX_SIZE;
	static int SEQUENCE_SEARCH_NUM_THRESHOLD;
	static double SEQUENCE_SEARCH_RATIO_THRESHOLD;
	static int MAX_LENGTH_FOR_ANY_VECTOR;
	static const bool LITTLE_ENDIAN_ORDER;

private:
	static int cumMonthDays[13];
	static int monthDays[12];
	static int cumLeapMonthDays[13];
	static int leapMonthDays[12];
	static char escapes[128];
	static string duSyms[10];
	static long long tmporalDurationRatioMatrix[9][10];
	static long long tmporalRatioMatrix[81];
	static long long tmporalUplimit[9];
	static SmartPointer<ConstantFactory> constFactory_;

public:
	static Constant* parseConstant(int type, const string& word);
	static Constant* createConstant(DATA_TYPE dataType, int extraParam = 0);
	static Constant* createNullConstant(DATA_TYPE dataType, int extraParam = 0);
	static Constant* createBool(char val);
	static Constant* createChar(char val);
	static Constant* createShort(short val);
	static Constant* createInt(int val);
	static Constant* createLong(long long val);
	static Constant* createFloat(float val);
	static Constant* createDouble(double val);
	static Constant* createString(const string& val);
	static Constant* createBlob(const string& val);
	static Constant* createDate(int year, int month, int day);
	static Constant* createDate(int days);
	static Constant* createMonth(int year, int month);
	static Constant* createMonth(int months);
	static Constant* createNanoTime(int hour, int minute, int second, int nanosecond);
	static Constant* createNanoTime(long long nanoseconds);
	static Constant* createTime(int hour, int minute, int second, int millisecond);
	static Constant* createTime(int milliseconds);
	static Constant* createSecond(int hour, int minute, int second);
	static Constant* createSecond(int seconds);
	static Constant* createMinute(int hour, int minute);
	static Constant* createMinute(int minutes);
	static Constant* createNanoTimestamp(int year, int month, int day, int hour, int minute, int second, int nanosecond);
	static Constant* createNanoTimestamp(long long nanoseconds);
	static Constant* createTimestamp(int year, int month, int day, int hour, int minute, int second, int millisecond);
	static Constant* createTimestamp(long long milliseconds);
	static Constant* createDateTime(int year, int month, int day, int hour, int minute, int second);
	static Constant* createDateTime(int seconds);
	static Constant* createDateHour(int hours);
	static Constant* createDateHour(int year, int month, int day, int hour);
	static Constant* createDecimal32(int scale, double value);
	static Constant* createDecimal64(int scale, double value);

	static bool isFlatDictionary(Dictionary* dict);
	static Table* createTable(Dictionary* dict, int size);
	static Table* createTable(const vector<string>& colNames, const vector<DATA_TYPE>& colTypes, INDEX size, INDEX capacity, const vector<int>& extraParams = {});
	static Table* createTable(const vector<string>& colNames, const vector<ConstantSP>& cols);
	static Set* createSet(DATA_TYPE keyType, INDEX capacity);
	static Dictionary* createDictionary(DATA_TYPE keyType, DATA_TYPE valueType);
	static Vector* createVector(DATA_TYPE type, INDEX size, INDEX capacity = 0, bool fast = true, int extraParam = 0, void* data = 0, bool containNull = false);
	static Vector* createArrayVector(VectorSP index, VectorSP value);
	static Vector* createArrayVector(DATA_TYPE type, INDEX size, INDEX capacity = 0, bool fast = true, int extraParam = 0, void *data = NULL, INDEX *pindex = NULL, bool containNull = false);
	static Vector* createMatrix(DATA_TYPE type, int cols, int rows, int colCapacity, int extraParam = 0, void* data = 0, bool containNull = false);
	static Vector* createDoubleMatrix(int cols, int rows);
	static Vector* createPair(DATA_TYPE type, int extraParam = 0) {
		if (type == DT_ANY) {
			return NULL;
		}
		Vector* pair = createVector(type, 2, 2, true, extraParam);
		if (pair == NULL)
			return NULL;
		pair->setForm(DF_PAIR);
		return pair;
	}
	static Vector* createIndexVector(INDEX start, INDEX length);
	static Vector* createIndexVector(INDEX length, bool arrayOnly, INDEX capacity = 0);

	/**
	* Convert unsigned byte sequences to hex string.
	*
	* littleEndian: if true, the first byte is the least significant and should be printed at the most right.
	* str: the length of buffer must be at least 2 * len.
	*/
	static void toHex(const unsigned char* data, int len, bool littleEndian, char* str);
	/**
	* Convert hex string to unsigned byte sequences.
	*
	* len: must be a positive even number.
	* littleEndian: if true, the first byte is the least significant, i.e. the leftmost characters would be converted to the rightmost byte.
	* data: the length of buffer must be at least len/2
	*/
	static bool fromHex(const char* str, int len, bool littleEndian, unsigned char* data);

	static void toGuid(const unsigned char*, char* str);
	static bool fromGuid(const char* str, unsigned char* data);

	static DATA_TYPE convertToIntegralDataType(DATA_TYPE type);
	static long long getTemporalConversionRatio(DATA_TYPE first, DATA_TYPE second);
	static char getDataTypeSymbol(DATA_TYPE type);
	static string getDataTypeString(DATA_TYPE type);
	static string getDataFormString(DATA_FORM form);
	static string getTableTypeString(TABLE_TYPE type);
	static DATA_TYPE getDataType(const string& typestr);
	static DATA_FORM getDataForm(const string& formstr);
	static int getDataTypeSize(DATA_TYPE type);
	static DATA_TYPE getDataType(char ch);
	static DATA_CATEGORY getCategory(DATA_TYPE type);
	static DURATION_UNIT getDurationUnit(const string& typestr);
	static long long getTemporalDurationConversionRatio(DATA_TYPE t, DURATION_UNIT du);
	static long long getTemporalUplimit(DATA_TYPE t);

	static bool equalIgnoreCase(const string& str1, const string& str2);
	static string lower(const string& str);
	static string upper(const string& str);
	static char toUpper(char ch);
	static char toLower(char ch);
	static string ltrim(const string& str);
	static string trim(const string& str);
	static string strip(const string& str);
	static int wc(const char* str);
	static bool endWith(const string& str, const string& end);
	static bool startWith(const string& str, const string& start);
	static bool strWildCmp(const char* wildstring, const char* matchstring);
	static bool strCaseInsensitiveWildCmp(const char* str, const char* pat);
	static string replace(const string& str, const string& pattern, const string& replacement);
	static string replace(const string& str, char pattern, char replacement);
	static string convert(int val);
	static string longToString(long long val);
	static string doubleToString(double val);
	static bool isVariableCandidate(const string& word);
	static string literalConstant(const string& str);
	static void split(const char* s, char delim, vector<string> &elems);
	static vector<string> split(const string &s, char delim);
	inline static bool isDigit(char ch) { return '0' <= ch && ch <= '9'; }
	inline static bool isDateDelimitor(char ch) { return ch == '.' || ch == '/' || ch == '-'; }
	inline static bool isLetter(char ch) { return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); }
	static char escape(char original);
	static void writeDoubleQuotedString(string& dest, const string& source);

	static int countDays(int year, int month, int day);
	static int parseYear(int days);
	static void parseDate(int days, int& year, int& month, int& day);
	static int getMonthEnd(int days);
	static int getMonthStart(int days);
	static long long getNanoBenchmark();
	static long long getEpochTime();
	static long long getNanoEpochTime();
	static bool getLocalTime(struct tm& result);
	static bool getLocalTime(time_t t, struct tm& result);
	static int toLocalDateTime(int epochTime);
	static int* toLocalDateTime(int* epochTimes, int n);
	static long long toLocalTimestamp(long long epochTime);
	static long long* toLocalTimestamp(long long* epochTimes, int n);
	static long long toLocalNanoTimestamp(long long epochNanoTime);
	static long long* toLocalNanoTimestamp(long long* epochNanoTimes, int n);
	static string toMicroTimestampStr(std::chrono::system_clock::time_point& tp, bool printDate = false);

	static char* allocateMemory(INDEX size, bool throwIfFail = true);
	static bool isLittleEndian() { int x = 1; return *(char *)&x == 1; }
	static bool is64BIT() { return sizeof(char*) == 8; }
	static bool isWindows();
	static int getCoreCount();
	static long long getPhysicalMemorySize();
	static void sleep(int milliSeconds);
	static int getLastErrorCode();
	static string getLastErrorMessage();
	static string getErrorMessage(int errCode);
	static string getPartitionTypeString(PARTITION_TYPE type);
	static Domain* createDomain(PARTITION_TYPE type, DATA_TYPE partitionColType, const ConstantSP& partitionSchema);
	static Vector* createSubVector(const VectorSP& source, vector<int> indices);
	static string getCategoryString(DATA_CATEGORY type);
	static Vector* createSymbolVector(const SymbolBaseSP& symbolBase, INDEX size, INDEX capacity = 0, bool fast = true,
		void* data = 0, void** dataSegment = 0, int segmentSizeInBit = 0, bool containNull = false);

	static void SetOrThrowErrorInfo(ErrorCodeInfo *errorCodeInfo, int errorCode, const string &errorInfo);
	template<typename T>
	static ConstantSP createObject(DATA_TYPE dataType, T val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0) {
		SetOrThrowErrorInfo(errorCodeInfo, ErrorCodeInfo::EC_InvalidObject, "It cannot be converted to " + getDataTypeString(dataType));
		return NULL;
	}
	static ConstantSP createObject(DATA_TYPE dataType, std::nullptr_t val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, Constant* val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, ConstantSP val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, bool val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, char val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, short val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, const char* val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::string val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, const unsigned char* val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, unsigned char val[], ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, long long val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, long int val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, int val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, float val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, double val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, const void* val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	/*
	template<typename T>
	static bool appendVector(DATA_TYPE dataType, VectorSP &vec, const T *val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL) {
		SetOrThrowErrorInfo(errorCodeInfo, ErrorCodeInfo::EC_InvalidObject, "It cannot be converted to " + getDataTypeString(dataType));
		return false;
	}
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const std::nullptr_t* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const Constant** val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const ConstantSP* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const bool* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const char* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const short* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const char* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const std::string* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const unsigned char** val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const long long* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const long int* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const int* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const float* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const double* val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	static bool appendVector(DATA_TYPE dataType, VectorSP& vec, const const void** val, int valSize, ErrorCodeInfo* errorCodeInfo = NULL);
	*/
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<std::nullptr_t> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<Constant*> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<ConstantSP> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<bool> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<char> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<short> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<const char*> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<std::string> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<const unsigned char*> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<long long> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<long int> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<int> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<float> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<double> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createObject(DATA_TYPE dataType, std::vector<const void*> val, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static ConstantSP createValue(DATA_TYPE dataType, long long val, const char *pTypeName, ErrorCodeInfo *errorCodeInfo = NULL, int extraParam = 0);
	static bool checkColDataType(DATA_TYPE colDataType, bool isColTemporal, ConstantSP &constsp);
	static unsigned long getCurThreadId();
	static void writeFile(const char *pfilepath, const void *pbytes, int bytelen);

	static void enumBoolVector(const VectorSP &pVector, std::function<bool(const char *pbuf, INDEX startIndex, INDEX size)> func, INDEX offset = 0) {
		enumDdbVector<char>(pVector, &Vector::getBoolConst, func, offset);
	}
	static void enumIntVector(const VectorSP &pVector, std::function<bool(const int *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumDdbVector<int>(pVector, &Vector::getIntConst, func, offset);
	}
	static void enumShortVector(const VectorSP &pVector, std::function<bool(const short *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumDdbVector<short>(pVector, &Vector::getShortConst, func, offset);
	}
	static void enumCharVector(const VectorSP &pVector, std::function<bool(const char *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumDdbVector<char>(pVector, &Vector::getCharConst, func, offset);
	}
	static void enumLongVector(const VectorSP &pVector, std::function<bool(const long long *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumDdbVector<long long>(pVector, &Vector::getLongConst, func, offset);
	}
	static void enumFloatVector(const VectorSP &pVector, std::function<bool(const float *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumDdbVector<float>(pVector, &Vector::getFloatConst, func, offset);
	}
	static void enumDoubleVector(const VectorSP &pVector, std::function<bool(const double *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumDdbVector<double>(pVector, &Vector::getDoubleConst, func, offset);
	}
	static void enumStringVector(const VectorSP &pVector, std::function<bool(string **pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		string* buffer[Util::BUF_SIZE];
		string** pbuf;
		INDEX startIndex = offset;
		int size;
		INDEX leftSize = pVector->size() - startIndex;
		while (leftSize > 0) {
			size = leftSize;
			if (size > Util::BUF_SIZE)
				size = Util::BUF_SIZE;
			pbuf = pVector->getStringConst(startIndex, size, buffer);
			if (func(pbuf, startIndex, size) == false)
				break;
			leftSize -= size;
			startIndex += size;
		}
	}
	static void enumInt128Vector(const VectorSP &pVector, std::function<bool(const Guid *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumBinaryVector<Guid>(pVector, func, offset);
	}
	static void enumDecimal32Vector(const VectorSP &pVector, std::function<bool(const int32_t *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumBinaryVector<int32_t>(pVector, func, offset);
	}
	static void enumDecimal64Vector(const VectorSP &pVector, std::function<bool(const int64_t *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		enumBinaryVector<int64_t>(pVector, func, offset);
	}
private:
	template <class T>
	static void enumBinaryVector(const VectorSP &pVector, std::function<bool(const T *pbuf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		vector<T> buffer(Util::BUF_SIZE);
		const T* pbuf;
		INDEX startIndex = offset;
		int size;
		INDEX leftSize = pVector->size() - startIndex;
		while (leftSize > 0) {
			size = leftSize;
			if (size > Util::BUF_SIZE)
				size = Util::BUF_SIZE;
			pbuf = (const T*)pVector->getBinaryConst(startIndex, size, sizeof(T), (unsigned char*)buffer.data());
			if (func(pbuf, startIndex, size) == false)
				break;
			leftSize -= size;
			startIndex += size;
		}
	}
	template <class T>
	static void enumDdbVector(const VectorSP &pVector,
		const T* (Vector::*getConst)(INDEX, int, T*) const,
		std::function<bool(const T *buf, INDEX startIndex, int length)> func, INDEX offset = 0) {
		T buffer[Util::BUF_SIZE];
		const T *pbuf;
		INDEX startIndex = offset;
		int size;
		INDEX leftSize = pVector->size() - startIndex;
		while (leftSize > 0) {
			size = leftSize;
			if (size > Util::BUF_SIZE)
				size = Util::BUF_SIZE;
			pbuf = (pVector.get()->*getConst)(startIndex, size, buffer);
			if (func(pbuf, startIndex, size) == false)
				break;
			leftSize -= size;
			startIndex += size;
		}
	}
};

template <typename T>
inline T getNullValue();
template <>
inline char getNullValue<char>() { return CHAR_MIN; }
template <>
inline short getNullValue<short>() { return SHRT_MIN; }
template <>
inline int getNullValue<int>() { return INT_MIN; }
template <>
inline long int getNullValue<long int>() { return LONG_MIN; }
template <>
inline long long getNullValue<long long>() { return LLONG_MIN; }
template <>
inline float getNullValue<float>() { return FLT_NMIN; }
template <>
inline double getNullValue<double>() { return DBL_NMIN; }
template <>
inline string getNullValue<string>() { return ""; }
template <>
inline Guid getNullValue<Guid>() { return Guid(); }

class ResultSet {
public:
	ResultSet(const TableSP &table)
		: table_(table), position_(0)
	{
		rows_ = table_->rows();
		cols_ = table_->columns();
		column_ = new ColumnPointer[cols_];
		for (int i = 0; i < cols_; i++) {
			column_[i].pVector = table_->getColumn(i);
			VectorSP &pVector = column_[i].pVector;
			DATA_TYPE type = pVector->getRawType();
			switch (type) {
			case DT_BOOL:
				column_[i].charCol = new Column<char>(pVector, [=](const VectorSP &pVector, INDEX position, int len, char *buf) {
					return pVector->getBoolConst(position, len, buf);
				});
				break;
			case DT_CHAR:
				column_[i].charCol = new Column<char>(pVector, [=](const VectorSP &pVector, INDEX position, int len, char *buf) {
					return pVector->getCharConst(position, len, buf);
				});
				break;
			case DT_SHORT:
				column_[i].shortCol = new Column<short>(pVector, [=](const VectorSP &pVector, INDEX position, int len, short *buf) {
					return pVector->getShortConst(position, len, buf);
				});
				break;
			case DT_INT:
				if (pVector->getType() == DT_SYMBOL) {
					column_[i].stringCol = new Column<string*>(pVector, [=](const VectorSP &pVector, INDEX position, int len, string** buf) {
						return pVector->getStringConst(position, len, buf);
					});
				}
				else {
					column_[i].intCol = new Column<int>(pVector, [=](const VectorSP &pVector, INDEX position, int len, int *buf) {
						return pVector->getIntConst(position, len, buf);
					});
				}
				break;
			case DT_LONG:
				column_[i].longCol = new Column<long long>(pVector, [=](const VectorSP &pVector, INDEX position, int len, long long *buf) {
					return pVector->getLongConst(position, len, buf);
				});
				break;
			case DT_FLOAT:
				column_[i].floatCol = new Column<float>(pVector, [=](const VectorSP &pVector, INDEX position, int len, float *buf) {
					return pVector->getFloatConst(position, len, buf);
				});
				break;
			case DT_DOUBLE:
				column_[i].doubleCol = new Column<double>(pVector, [=](const VectorSP &pVector, INDEX position, int len, double *buf) {
					return pVector->getDoubleConst(position, len, buf);
				});
				break;
			case DT_BLOB:
			case DT_STRING:
				column_[i].stringCol = new Column<string*>(pVector, [=](const VectorSP &pVector, INDEX position, int len, string** buf) {
					return pVector->getStringConst(position, len, buf);
				});
				break;
			case DT_INT128:
				column_[i].int128Col = new Column<Guid>(pVector, [=](const VectorSP &pVector, INDEX position, int len, Guid *buf) {
					return (const Guid*)pVector->getBinaryConst(position, len, sizeof(Guid), (unsigned char*)buf);
				});
				break;
			case DT_DECIMAL32:
				column_[i].decimal32Col = new Column<int32_t>(pVector, [=](const VectorSP &pVector, INDEX position, int len, int32_t *buf) {
					return (const int32_t*)pVector->getBinaryConst(position, len, sizeof(int32_t), (unsigned char*)buf);
				});
				break;
			case DT_DECIMAL64:
				column_[i].decimal64Col = new Column<int64_t>(pVector, [=](const VectorSP &pVector, INDEX position, int len, int64_t *buf) {
					return (const int64_t*)pVector->getBinaryConst(position, len, sizeof(int64_t), (unsigned char*)buf);
				});
				break;
			default:
				throw RuntimeException("ResultSet doesn't support data type " + Util::getDataTypeString(pVector->getType()));
				break;
			}
		}
	}
	~ResultSet() {
		delete[] column_;
	}
	INDEX position() {
		return position_;
	}
	void position(INDEX position) {
		if (position >= rows_ || position < 0) {
			throw RuntimeException("Position exceed row limit.");
		}
		position_ = position;
	}
	bool next() {
		if (position_ < rows_) {
			position_++;
			return true;
		}
		return false;
	}
	bool first() {
		if (rows_ > 0) {
			position_ = 0;
			return true;
		}
		return false;
	}
	bool isFirst() {
		return position_ == 0;
	}
	bool last() {
		if (rows_ > 0) {
			position_ = rows_ - 1;
			return true;
		}
		return false;
	}
	bool isLast() {
		return position_ + 1 == rows_;
	}
	bool isAfterLast() {
		return position_ >= rows_;
	}
	bool isBeforeFirst() {
		return position_ < 0;
	}
	DATA_TYPE getDataType(int col) {
		return table_->getColumnType(col);
	}
	char getBool(int col) {
		assert(column_[col].charCol != nullptr);
		return column_[col].charCol->getValue(position_);
	}
	char getChar(int col) {
		assert(column_[col].charCol != nullptr);
		return column_[col].charCol->getValue(position_);
	}
	short getShort(int col) {
		assert(column_[col].shortCol != nullptr);
		return column_[col].shortCol->getValue(position_);
	}
	int getInt(int col) {
		assert(column_[col].intCol != nullptr);
		return column_[col].intCol->getValue(position_);
	}
	long long getLong(int col) {
		assert(column_[col].longCol != nullptr);
		return column_[col].longCol->getValue(position_);
	}
	float getFloat(int col) {
		assert(column_[col].floatCol != nullptr);
		return column_[col].floatCol->getValue(position_);
	}
	double getDouble(int col) {
		assert(column_[col].doubleCol != nullptr);
		return column_[col].doubleCol->getValue(position_);
	}
	const string& getString(int col) const {
		assert(column_[col].stringCol != nullptr);
		return *column_[col].stringCol->getValue(position_);
	}
	const unsigned char* getBinary(int col) const {
		ColumnPointer &column = column_[col];
		if(column.charCol!=nullptr)
			return (unsigned char*)&column.charCol->getValue(position_);
		else if (column.shortCol != nullptr)
			return (unsigned char*)&column.shortCol->getValue(position_);
		else if (column.intCol != nullptr)
			return (unsigned char*)&column.intCol->getValue(position_);
		else if (column.longCol != nullptr)
			return (unsigned char*)&column.longCol->getValue(position_);
		else if (column.floatCol != nullptr)
			return (unsigned char*)&column.floatCol->getValue(position_);
		else if (column.doubleCol != nullptr)
			return (unsigned char*)&column.doubleCol->getValue(position_);
		else if (column.stringCol != nullptr)
			return (unsigned char*)column.stringCol->getValue(position_)->data();
		else if(column.int128Col != nullptr)
			return (unsigned char*)&column.int128Col->getValue(position_);
		else if (column.decimal32Col != nullptr)
			return (unsigned char*)&column.decimal32Col->getValue(position_);
		else if (column.decimal64Col != nullptr)
			return (unsigned char*)&column.decimal64Col->getValue(position_);
		else {
			throw RuntimeException("This instance doesn't support getBinary.");
		}
	}
	ConstantSP getObject(int col) const {
		return column_[col].pVector->get(position_);
	}
private:
	template <class T>
	class Column {
	public:
		Column(const VectorSP &vector,
			std::function<const T*(const VectorSP &pVector, INDEX position,int len, T *buf)> getBufConst)
			: pVector_(vector), getBufConst_(getBufConst),
				constRefBegin_(0), constRefEnd_(0) {
			rows_ = pVector_->rows();
			buffer_=new T[Util::BUF_SIZE];
		}
		~Column() {
			delete[] buffer_;
		}
		const T& getValue(INDEX position) {
			int offset = offsetConst(position);
			return constRef_[offset];
		}
	private:
		VectorSP pVector_;
		std::function<const T*(const VectorSP &pVector, INDEX position, int len, T *buf)> getBufConst_;
		T *buffer_;
		const T *constRef_;
		INDEX constRefBegin_, constRefEnd_;
		INDEX rows_;
		int offsetConst(INDEX position) {
			if (position >= constRefBegin_ && position < constRefEnd_) {
				return position - constRefBegin_;
			}
			if (position < 0 || position >= rows_) {
				throw RuntimeException("Position is out of range.");
			}
			int size = std::min(Util::BUF_SIZE, rows_ - position);
			constRef_ = getBufConst_(pVector_, position, size, buffer_);
			constRefBegin_ = position;
			constRefEnd_ = position + size;
			return 0;
		}
	};
	struct ColumnPointer {
		VectorSP pVector;
		Column<char> *charCol = nullptr;
		Column<short> *shortCol = nullptr;
		Column<int> *intCol = nullptr;
		Column<long long> *longCol = nullptr;
		Column<float> *floatCol = nullptr;
		Column<double> *doubleCol = nullptr;
		Column<string*> *stringCol = nullptr;
		Column<Guid> *int128Col = nullptr;
		Column<int32_t> *decimal32Col = nullptr;
		Column<int64_t> *decimal64Col = nullptr;
		~ColumnPointer() {
			delete charCol;
			delete shortCol;
			delete intCol;
			delete longCol;
			delete floatCol;
			delete doubleCol;
			delete stringCol;
			delete int128Col;
			delete decimal32Col;
			delete decimal64Col;
		}
	};
	TableSP table_;
	long position_;
	int rows_, cols_;
	ColumnPointer *column_;
};

template <class T>
class DdbVector {
public:
	DdbVector(int size, int capacity = 0) : size_(size), capacity_(capacity), dataNeedRelease_(true), containNull_(false){
		if (capacity_ < size_)
			capacity_ = size_;
		if (capacity_ < 1) {
			throw RuntimeException("can't create empty DdbVector.");
		}
		data_ = new T[capacity_];
	}
	//DdbVector own data and it will be released, don't delete data in the future.
	DdbVector(T *data, int size, int capacity = 0) : data_(data), size_(size), capacity_(capacity), dataNeedRelease_(true), containNull_(false) {
		if (capacity_ < size_)
			capacity_ = size_;
	}
	DdbVector(const DdbVector &src) = delete;
	~DdbVector() {
		if (dataNeedRelease_) {
			delete[] data_;
		}
	}
	int size() const {
		return size_;
	}
	const T* data() const {
		assert(dataNeedRelease_);
		return data_;
	}
	T* data() {
		assert(dataNeedRelease_);
		return data_;
	}
	void addNull() {
		add(getNullValue<T>());
		containNull_ = true;
	}
	void add(const T& value) {
		assert(dataNeedRelease_);
		assert(size_  < capacity_);
		if(containNull_ == false && value == getNullValue<T>()){
			containNull_ = true;
		}
		data_[size_++] = value;
	}
	void add(T&& value) {
		assert(dataNeedRelease_);
		assert(size_  < capacity_);
		if (containNull_ == false && value == getNullValue<T>()) {
			containNull_ = true;
		}
		data_[size_++] = std::move(value);
	}
	void appendString(const string *buf, int len) {
		assert(dataNeedRelease_);
		assert(size_ + len <= capacity_);
		for (auto i = 0; i < len; i++) {
			if (containNull_ == false && buf[i] == getNullValue<T>()) {
				containNull_ = true;
			}
			data_[size_++] = std::move(buf[i]);
		}
	}
	void appendString(string *buf, int len) {
		assert(dataNeedRelease_);
		assert(size_ + len <= capacity_);
		for (auto i = 0; i < len; i++) {
			if (containNull_ == false && buf[i] == getNullValue<T>()) {
				containNull_ = true;
			}
			data_[size_++] = std::move(buf[i]);
		}
	}
	//This function is invalid for string DdbVector, please use appendString instead.
	void append(const T *buf, int len) {
		assert(dataNeedRelease_);
		assert(size_ + len <= capacity_);
		if (containNull_ == false) {
			for (auto i = 0; i < len; i++) {
				if (buf[i] == getNullValue<T>()) {
					containNull_ = true;
					break;
				}
			}
		}
		memcpy(data_ + size_, buf, len * sizeof(T));
		size_ += len;
	}
	void setNull(int index) {
		set(index, getNullValue<T>());
		containNull_ = true;
	}
	void set(int index, const T& value) {
		assert(dataNeedRelease_);
		assert(index < size_);
		if (containNull_ == false && value == getNullValue<T>()) {
			containNull_ = true;
		}
		data_[index] = value;
	}
	void set(int index, T&& value) {
		assert(dataNeedRelease_);
		assert(index < size_);
		if (containNull_ == false && value == getNullValue<T>()) {
			containNull_ = true;
		}
		data_[index] = std::move(value);
	}
	void setString(int start, int len, const string *buf) {
		assert(dataNeedRelease_);
		assert(start < size_);
		assert(start + len <= size_);
		for (auto i = 0, index = start; i < len; i++, index++) {
			if (containNull_ == false && buf[i] == getNullValue<T>()) {
				containNull_ = true;
			}
			data_[index] = std::move(buf[i]);
		}
	}
	void setString(int start, int len, string *buf) {
		assert(dataNeedRelease_);
		assert(start < size_);
		assert(start + len <= size_);
		for (auto i = 0, index = start; i < len; i++, index++) {
			if (containNull_ == false && buf[i] == getNullValue<T>()) {
				containNull_ = true;
			}
			data_[index] = std::move(buf[i]);
		}
	}
	//This function is invalid for string DdbVector, please use appendString instead.
	void set(int start, int len, const T *buf) {
		assert(dataNeedRelease_);
		assert(start < size_);
		assert(start + len <= size_);
		if (containNull_ == false) {
			for (auto i = 0; i < len; i++) {
				if (buf[i] == getNullValue<T>()) {
					containNull_ = true;
					break;
				}
			}
		}
		memcpy(data_ + start, buf, len * sizeof(T));
	}
	Vector* createVector(DATA_TYPE type, int extraParam = 0) {
		if (dataNeedRelease_ == false) {
			throw RuntimeException(Util::getDataTypeString(type) + "'s createVector can only be called once.");
		}
		if (type != DT_STRING && type != DT_BLOB && type != DT_SYMBOL) {
			assert(Util::getDataTypeSize(type) == sizeof(T));
			Vector* pVector;
			pVector = Util::createVector(type, size_, size_, true, extraParam, data_, containNull_);
			dataNeedRelease_ = false;
			return pVector;
		}
		else {
			Vector* pVector = Util::createVector(type, 0, size_, true, extraParam);
			pVector->appendString((string*)data_, size_);
			return pVector;
		}
	}
private:
	T * data_;
	int size_;
	int capacity_;
	bool dataNeedRelease_, containNull_;
};

};

#endif /* UTIL_H_ */
