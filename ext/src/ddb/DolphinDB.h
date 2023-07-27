/*
 * DolphinDB.h
 *
 *  Created on: Sep 22, 2018
 *      Author: dzhou
 */

#ifndef DOLPHINDB_H_
#define DOLPHINDB_H_

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>
#include <deque>
#include <algorithm>
#include <memory>
#include <chrono>
#include <cstring>
#include <functional>

#include "Types.h"
#include "SmartPointer.h"
#include "Exceptions.h"
#include "SysIO.h"

#ifdef _MSC_VER
	#ifdef _DDBAPIDLL	
		#define EXPORT_DECL _declspec(dllexport)
	#else
		#define EXPORT_DECL __declspec(dllimport)
	#endif
#else
	#define EXPORT_DECL 
#endif
#if defined(__GNUC__) && __GNUC__ >= 4
#define LIKELY(x) (__builtin_expect((x), 1))
#define UNLIKELY(x) (__builtin_expect((x), 0))
#else
#define LIKELY(x) (x)
#define UNLIKELY(x) (x)
#endif

using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::set;
using std::deque;
using std::pair;

namespace dolphindb {

class Constant;
class Vector;
class Matrix;
class Table;
class Set;
class Dictionary;
class DFSChunkMeta;
class ConstantMarshall;
class ConstantUnmarshall;
class DBConnectionImpl;
class BlockReader;
class Domain; 
class DBConnectionPoolImpl;
class PartitionedTableAppender;
class SymbolBase;
class Mutex;

typedef SmartPointer<Constant> ConstantSP;
typedef SmartPointer<Vector> VectorSP;
typedef SmartPointer<Matrix> MatrixSP;
typedef SmartPointer<Table> TableSP;
typedef SmartPointer<Set> SetSP;
typedef SmartPointer<Dictionary> DictionarySP;
typedef SmartPointer<DFSChunkMeta> DFSChunkMetaSP;
typedef SmartPointer<ConstantMarshall> ConstantMarshallSP;
typedef SmartPointer<ConstantUnmarshall> ConstantUnmarshallSP;
typedef SmartPointer<BlockReader> BlockReaderSP;
typedef SmartPointer<Domain> DomainSP;
typedef SmartPointer<SymbolBase> SymbolBaseSP;

class EXPORT_DECL Guid {
public:
	Guid(bool newGuid = false);
	Guid(unsigned char* guid);
	Guid(const string& guid);
	Guid(const Guid& copy);
	Guid(unsigned long long high, unsigned long long low){
#ifndef BIGENDIANNESS
		memcpy((char*)uuid_, (char*)&low, 8);
		memcpy((char*)uuid_ + 8, (char*)&high, 8);
#else
		memcpy((char*)uuid_, (char*)&high, 8);
		memcpy((char*)uuid_ + 8, (char*)&low, 8);
#endif
	}
	inline bool operator==(const Guid &other) const {
		const unsigned char* a = (const unsigned char*)uuid_;
		const unsigned char* b = (const unsigned char*)other.uuid_;
		return (*(long long*)a) == (*(long long*)b) && (*(long long*)(a+8)) == (*(long long*)(b+8));
	}
	inline bool operator!=(const Guid &other) const {
		const unsigned char* a = (const unsigned char*)uuid_;
		const unsigned char* b = (const unsigned char*)other.uuid_;
		return (*(long long*)a) != (*(long long*)b) || (*(long long*)(a+8)) != (*(long long*)(b+8));
	}
	inline bool operator<(const Guid &other) const {
		const unsigned char* a = (const unsigned char*)uuid_;
		const unsigned char* b = (const unsigned char*)other.uuid_;
#ifndef BIGENDIANNESS
		return (*(unsigned long long*)(a+8)) < (*(unsigned long long*)(b+8)) || ((*(unsigned long long*)(a+8)) == (*(unsigned long long*)(b+8)) && (*(unsigned long long*)a) < (*(unsigned long long*)b));
#else
		return (*(unsigned long long*)a) < (*(unsigned long long*)b) || ((*(unsigned long long*)a) == (*(unsigned long long*)b) && (*(unsigned long long*)(a+8)) < (*(unsigned long long*)(b+8)));
#endif
	}
	inline bool operator>(const Guid &other) const {
		const unsigned char* a = (const unsigned char*)uuid_;
		const unsigned char* b = (const unsigned char*)other.uuid_;
#ifndef BIGENDIANNESS
		return (*(unsigned long long*)(a+8)) > (*(unsigned long long*)(b+8)) || ((*(unsigned long long*)(a+8)) == (*(unsigned long long*)(b+8)) && (*(unsigned long long*)a) > (*(unsigned long long*)b));
#else
		return (*(unsigned long long*)a) > (*(unsigned long long*)b) || ((*(unsigned long long*)a) == (*(unsigned long long*)b) && (*(unsigned long long*)(a+8)) > (*(unsigned long long*)(b+8)));
#endif
	}
	inline bool operator<=(const Guid &other) const {
		const unsigned char* a = (const unsigned char*)uuid_;
		const unsigned char* b = (const unsigned char*)other.uuid_;
#ifndef BIGENDIANNESS
		return (*(unsigned long long*)(a+8)) < (*(unsigned long long*)(b+8)) || ((*(unsigned long long*)(a+8)) == (*(unsigned long long*)(b+8)) && (*(unsigned long long*)a) <= (*(unsigned long long*)b));
#else
		return (*(unsigned long long*)a) < (*(unsigned long long*)b) || ((*(unsigned long long*)a) == (*(unsigned long long*)b) && (*(unsigned long long*)(a+8)) <= (*(unsigned long long*)(b+8)));
#endif
	}
	inline bool operator>=(const Guid &other) const {
		const unsigned char* a = (const unsigned char*)uuid_;
		const unsigned char* b = (const unsigned char*)other.uuid_;
#ifndef BIGENDIANNESS
		return (*(unsigned long long*)(a+8)) > (*(unsigned long long*)(b+8)) || ((*(unsigned long long*)(a+8)) == (*(unsigned long long*)(b+8)) && (*(unsigned long long*)a) >= (*(unsigned long long*)b));
#else
		return (*(unsigned long long*)a) > (*(unsigned long long*)b) || ((*(unsigned long long*)a) == (*(unsigned long long*)b) && (*(unsigned long long*)(a+8)) >= (*(unsigned long long*)(b+8)));
#endif
	}
	inline int compare(const Guid &other) const { return (*this < other) ? -1 : (*this > other ? 1 : 0);}
	inline unsigned char operator[](int i) const { return uuid_[i];}
	bool isZero() const;
	inline bool isNull() const {
		const unsigned char* a = (const unsigned char*)uuid_;
		return (*(long long*)a) == 0 && (*(long long*)(a+8)) == 0;
	}
	inline bool isValid() const {
		const unsigned char* a = (const unsigned char*)uuid_;
		return (*(long long*)a) != 0 || (*(long long*)(a+8)) != 0;
	}
    string getString() const;
    inline const unsigned char* bytes() const { return uuid_;}
    static string getString(const unsigned char* guid);

private:
	unsigned char uuid_[16];
};

struct GuidHash {
	uint64_t operator()(const Guid& guid) const;
};

class EXPORT_DECL Constant {
public:
	static string EMPTY;
	static string NULL_STR;
	static ConstantSP void_;
	static ConstantSP null_;
	static ConstantSP true_;
	static ConstantSP false_;
	static ConstantSP one_;

	Constant() : flag_(3){}
	Constant(unsigned short flag) :  flag_(flag){}
	virtual ~Constant(){}
	virtual bool isLargeConstant() const {return false;}
	inline bool isTemporary() const {return flag_ & 1;}
	inline void setTemporary(bool val){ if(val) flag_ |= 1; else flag_ &= ~1;}
	inline bool isIndependent() const {return flag_ & 2;}
	inline void setIndependent(bool val){ if(val) flag_ |= 2; else flag_ &= ~2;}
	inline bool isReadOnly() const {return flag_ & 4;}
	inline void setReadOnly(bool val){ if(val) flag_ |= 4; else flag_ &= ~4;}
	inline bool isReadOnlyArgument() const {return flag_ & 8;}
	inline void setReadOnlyArgument(bool val){ if(val) flag_ |= 8; else flag_ &= ~8;}
	inline bool isNothing() const {return flag_ & 16;}
	inline void setNothing(bool val){ if(val) flag_ |= 16; else flag_ &= ~16;}
	inline bool isStatic() const {return flag_ & 32;}
	inline void setStatic(bool val){ if(val) flag_ |= 32; else flag_ &= ~32;}
	inline bool transferAsString() const {return flag_ & 64;}
	inline void transferAsString(bool val){ if(val) flag_ |= 64; else flag_ &= ~64;}
	inline DATA_FORM getForm() const {return DATA_FORM(flag_ >> 8);}
	inline void setForm(DATA_FORM df){ flag_ = (flag_ & 127) + (df << 8);}
	inline bool isScalar() const { return getForm()==DF_SCALAR;}
	inline bool isArray() const { return getForm()==DF_VECTOR;}
	inline bool isPair() const { return getForm()==DF_PAIR;}
	inline bool isMatrix() const {return getForm()==DF_MATRIX;}
	//a vector could be array, pair or matrix.
	inline bool isVector() const { return getForm()>=DF_VECTOR && getForm()<=DF_MATRIX;}
	inline bool isTable() const { return getForm()==DF_TABLE;}
	inline bool isSet() const {return getForm()==DF_SET;}
	inline bool isDictionary() const {return getForm()==DF_DICTIONARY;}
	inline bool isChunk() const {return getForm()==DF_CHUNK;}
	bool isTuple() const {return getForm()==DF_VECTOR && getType()==DT_ANY;}
	bool isNumber() const { DATA_CATEGORY cat = getCategory(); return cat == INTEGRAL || cat == FLOATING;}

	virtual bool isDatabase() const {return false;}
	virtual char getBool() const {throw RuntimeException("The object can't be converted to boolean scalar.");}
	virtual char getChar() const {throw RuntimeException("The object can't be converted to char scalar.");}
	virtual short getShort() const {throw RuntimeException("The object can't be converted to short scalar.");}
	virtual int getInt() const {throw RuntimeException("The object can't be converted to int scalar.");}
	virtual long long  getLong() const {throw RuntimeException("The object can't be converted to long scalar.");}
	virtual INDEX getIndex() const {throw RuntimeException("The object can't be converted to index scalar.");}
	virtual float getFloat() const {throw RuntimeException("The object can't be converted to float scalar.");}
	virtual double getDouble() const {throw RuntimeException("The object can't be converted to double scalar.");}
	virtual string getString() const {return "";}
	virtual string getScript() const { return getString();}
	virtual const string& getStringRef() const {return EMPTY;}
    virtual const Guid getUuid() const {return getInt128();}
    virtual const Guid getInt128() const {throw RuntimeException("The object can't be converted to uuid scalar.");}
    virtual const unsigned char* getBinary() const {throw RuntimeException("The object can't be converted to int128 scalar.");}
	virtual bool isNull() const {return false;}
	virtual int getHash(int buckets) const {return -1;}

	virtual void setBool(char val){}
	virtual void setChar(char val){}
	virtual void setShort(short val){}
	virtual void setInt(int val){}
	virtual void setLong(long long val){}
	virtual void setIndex(INDEX val){}
	virtual void setFloat(float val){}
	virtual void setDouble(double val){}
	virtual void setString(const string& val){}
	virtual void setBinary(const unsigned char* val, int unitLength){}
	virtual void setNull(){}

	virtual char getBool(INDEX index) const {return getBool();}
	virtual char getChar(INDEX index) const { return getChar();}
	virtual short getShort(INDEX index) const { return getShort();}
	virtual int getInt(INDEX index) const {return getInt();}
	virtual long long getLong(INDEX index) const {return getLong();}
	virtual INDEX getIndex(INDEX index) const {return getIndex();}
	virtual float getFloat(INDEX index) const {return getFloat();}
	virtual double getDouble(INDEX index) const {return getDouble();}
	virtual string getString(INDEX index) const {return getString();}
	virtual const string& getStringRef(INDEX index) const {return EMPTY;}
	virtual bool isNull(INDEX index) const {return isNull();}

	virtual ConstantSP get(INDEX index) const {return getValue();}
	virtual ConstantSP get(INDEX column, INDEX row) const {return get(row);}
	virtual ConstantSP get(const ConstantSP& index) const {return getValue();}
	virtual ConstantSP getColumn(INDEX index) const {return getValue();}
	virtual ConstantSP getRow(INDEX index) const {return get(index);}
	virtual ConstantSP getItem(INDEX index) const {return get(index);}
	virtual ConstantSP getWindow(INDEX colStart, int colLength, INDEX rowStart, int rowLength) const {return getValue();}
	virtual ConstantSP getRowLabel() const;
	virtual ConstantSP getColumnLabel() const;

	virtual bool isNull(INDEX start, int len, char* buf) const {return false;}
	virtual bool isValid(INDEX start, int len, char* buf) const {return false;}
	virtual bool getBool(INDEX start, int len, char* buf) const {return false;}
	virtual bool getChar(INDEX start, int len,char* buf) const {return false;}
	virtual bool getShort(INDEX start, int len, short* buf) const {return false;}
	virtual bool getInt(INDEX start, int len, int* buf) const {return false;}
	virtual bool getLong(INDEX start, int len, long long* buf) const {return false;}
	virtual bool getIndex(INDEX start, int len, INDEX* buf) const {return false;}
	virtual bool getFloat(INDEX start, int len, float* buf) const {return false;}
	virtual bool getDouble(INDEX start, int len, double* buf) const {return false;}
	virtual bool getSymbol(INDEX start, int len, int* buf, SymbolBase* symBase,bool insertIfNotThere) const {return false;}
	virtual bool getString(INDEX start, int len, string** buf) const {return false;}
	virtual bool getString(INDEX start, int len, char** buf) const {return false;}
	virtual bool getBinary(INDEX start, int len, int unitLength, unsigned char* buf) const {return false;}
	virtual bool getHash(INDEX start, int len, int buckets, int* buf) const {return false;}

	virtual const char* getBoolConst(INDEX start, int len, char* buf) const {throw RuntimeException("getBoolConst method not supported");}
	virtual const char* getCharConst(INDEX start, int len,char* buf) const {throw RuntimeException("getCharConst method not supported");}
	virtual const short* getShortConst(INDEX start, int len, short* buf) const {throw RuntimeException("getShortConst method not supported");}
	virtual const int* getIntConst(INDEX start, int len, int* buf) const {throw RuntimeException("getIntConst method not supported");}
	virtual const long long* getLongConst(INDEX start, int len, long long* buf) const {throw RuntimeException("getLongConst method not supported");}
	virtual const INDEX* getIndexConst(INDEX start, int len, INDEX* buf) const {throw RuntimeException("getIndexConst method not supported");}
	virtual const float* getFloatConst(INDEX start, int len, float* buf) const {throw RuntimeException("getFloatConst method not supported");}
	virtual const double* getDoubleConst(INDEX start, int len, double* buf) const {throw RuntimeException("getDoubleConst method not supported");}
	virtual const int* getSymbolConst(INDEX start, int len, int* buf, SymbolBase* symBase, bool insertIfNotThere) const {throw RuntimeException("getSymbolConst method not supported");}
	virtual string** getStringConst(INDEX start, int len, string** buf) const {throw RuntimeException("getStringConst method not supported");}
	virtual char** getStringConst(INDEX start, int len, char** buf) const {throw RuntimeException("getStringConst method not supported");}
	virtual const unsigned char* getBinaryConst(INDEX start, int len, int unitLength, unsigned char* buf) const {throw RuntimeException("getBinaryConst method not supported");}

	virtual char* getBoolBuffer(INDEX start, int len, char* buf) const {return buf;}
	virtual char* getCharBuffer(INDEX start, int len,char* buf) const {return buf;}
	virtual short* getShortBuffer(INDEX start, int len, short* buf) const {return buf;}
	virtual int* getIntBuffer(INDEX start, int len, int* buf) const {return NULL;}
	virtual long long* getLongBuffer(INDEX start, int len, long long* buf) const {return buf;}
	virtual INDEX* getIndexBuffer(INDEX start, int len, INDEX* buf) const {return buf;}
	virtual float* getFloatBuffer(INDEX start, int len, float* buf) const {return buf;}
	virtual double* getDoubleBuffer(INDEX start, int len, double* buf) const {return buf;}
	virtual unsigned char* getBinaryBuffer(INDEX start, int len, int unitLength, unsigned char* buf) const {return buf;}
	virtual void* getDataBuffer(INDEX start, int len, void* buf) const {return buf;}

	virtual int serialize(char* buf, int bufSize, INDEX indexStart, int offset, int cellCountToSerialize, int& numElement, int& partial) const;
    virtual int serialize(char* buf, int bufSize, INDEX indexStart, int offset, int& numElement, int& partial) const;
    virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);

	virtual void nullFill(const ConstantSP& val){}
	virtual void setBool(INDEX index,bool val){setBool(val);}
	virtual void setChar(INDEX index,char val){setChar(val);}
	virtual void setShort(INDEX index,short val){setShort(val);}
	virtual void setInt(INDEX index,int val){setInt(val);}
	virtual void setLong(INDEX index,long long val){setLong(val);}
	virtual void setIndex(INDEX index,INDEX val){setIndex(val);}
	virtual void setFloat(INDEX index,float val){setFloat(val);}
	virtual void setDouble(INDEX index, double val){setDouble(val);}
	virtual void setString(INDEX index, const string& val){setString(val);}
	virtual void setBinary(INDEX index, int unitLength, const unsigned char* val){setBinary(val, unitLength);}
	virtual void setNull(INDEX index){setNull();}

	virtual bool set(INDEX index, const ConstantSP& value){return false;}
	virtual bool set(INDEX column, INDEX row, const ConstantSP& value){return false;}
	virtual bool set(const ConstantSP& index, const ConstantSP& value) {return false;}
	virtual bool setItem(INDEX index, const ConstantSP& value){return set(index,value);}
	virtual bool setColumn(INDEX index, const ConstantSP& value){return assign(value);}
	virtual void setRowLabel(const ConstantSP& label){}
	virtual void setColumnLabel(const ConstantSP& label){}
	virtual bool reshape(INDEX cols, INDEX rows) {return false;}
	virtual bool assign(const ConstantSP& value){return false;}

	virtual bool setBool(INDEX start, int len, const char* buf){return false;}
	virtual bool setChar(INDEX start, int len, const char* buf){return false;}
	virtual bool setShort(INDEX start, int len, const short* buf){return false;}
	virtual bool setInt(INDEX start, int len, const int* buf){return false;}
	virtual bool setLong(INDEX start, int len, const long long* buf){return false;}
	virtual bool setIndex(INDEX start, int len, const INDEX* buf){return false;}
	virtual bool setFloat(INDEX start, int len, const float* buf){return false;}
	virtual bool setDouble(INDEX start, int len, const double* buf){return false;}
	virtual bool setString(INDEX start, int len, const string* buf){return false;}
	virtual bool setString(INDEX start, int len, char** buf){return false;}
	virtual bool setBinary(INDEX start, int len, int unitLength, const unsigned char* buf){return false;}
	virtual bool setData(INDEX start, int len, void* buf) {return false;}

	virtual bool add(INDEX start, INDEX length, long long inc) { return false;}
	virtual bool add(INDEX start, INDEX length, double inc) { return false;}
	virtual void validate() {}

	virtual int compare(INDEX index, const ConstantSP& target) const {return 0;}

	virtual bool getNullFlag() const {return isNull();}
	virtual void setNullFlag(bool containNull){}
	virtual bool hasNull(){return  isNull();}
	virtual bool hasNull(INDEX start, INDEX length){return isNull();}
	virtual bool sizeable() const {return false;}
	virtual bool copyable() const {return true;}
	virtual INDEX size() const {return 1;}
	virtual INDEX itemCount() const {return getForm()==DF_MATRIX?columns():size();}
	virtual INDEX rows() const {return size();}
	virtual INDEX uncompressedRows() const {return size();}
	virtual INDEX columns() const {return 1;};
	virtual ConstantSP getMember(const ConstantSP& key) const { throw RuntimeException("getMember method not supported");}
	virtual ConstantSP keys() const {throw RuntimeException("keys method not supported");}
	virtual ConstantSP values() const {throw RuntimeException("values method not supported");}

	virtual long long releaseMemory(long long target, bool& satisfied) { satisfied = false; return 0;}
	virtual long long getAllocatedMemory() const {return 0;}
	virtual DATA_TYPE getType() const =0;
	virtual DATA_TYPE getRawType() const =0;
	virtual int getExtraParamForType() const { return 0;}
	virtual DATA_CATEGORY getCategory() const =0;

	virtual SymbolBaseSP getSymbolBase() const {return SymbolBaseSP();}
	virtual ConstantSP getInstance() const =0;
	virtual ConstantSP getValue() const =0;
	virtual OBJECT_TYPE getObjectType() const {return CONSTOBJ;}
	virtual bool isFastMode() const {return false;}
	virtual void* getDataArray() const {return 0;}
	virtual void** getDataSegment() const {return 0;}
	virtual bool isIndexArray() const { return false;}
	virtual INDEX* getIndexArray() const { return NULL;}
	virtual bool isHugeIndexArray() const { return false;}
	virtual INDEX** getHugeIndexArray() const { return NULL;}
	virtual int getSegmentSize() const { return 1;}
	virtual int getSegmentSizeInBit() const { return 0;}
	virtual bool containNotMarshallableObject() const {return false;}
	virtual ConstantSP castTemporal(DATA_TYPE expectType) { throw IncompatibleTypeException(getType(), expectType); }
private:
	unsigned short flag_;
};

class EXPORT_DECL Vector:public Constant{
public:
	Vector(): Constant(259){}
	virtual ~Vector(){}
	virtual ConstantSP getColumnLabel() const;
	const string& getName() const {return name_;}
	void setName(const string& name){name_=name;}
	virtual bool isLargeConstant() const { return isMatrix() || size()>1024; }
	virtual void initialize(){}
	virtual INDEX getCapacity() const = 0;
	virtual	INDEX reserve(INDEX capacity) {throw RuntimeException("Vector::reserve method not supported");}
	virtual	void resize(INDEX size) {throw RuntimeException("Vector::resize method not supported");}
	virtual INDEX getValueSize() const {throw RuntimeException("Vector::getValueSize method not supported"); return 0;}
	virtual short getUnitLength() const = 0;
	virtual void clear()=0;
	virtual bool remove(INDEX count){return false;}
	virtual bool remove(const ConstantSP& index){return false;}
	virtual bool append(const ConstantSP& value){return append(value, value->size());}
	virtual bool append(const ConstantSP& value, INDEX count){return false;}
	virtual bool append(const ConstantSP value, INDEX start, INDEX length){return false;}
	virtual bool appendBool(char* buf, int len){return false;}
	virtual bool appendChar(char* buf, int len){return false;}
	virtual bool appendShort(short* buf, int len){return false;}
	virtual bool appendInt(int* buf, int len){return false;}
	virtual bool appendLong(long long* buf, int len){return false;}
	virtual bool appendIndex(INDEX* buf, int len){return false;}
	virtual bool appendFloat(float* buf, int len){return false;}
	virtual bool appendDouble(double* buf, int len){return false;}
	virtual bool appendString(string* buf, int len){return false;}
	virtual bool appendString(char** buf, int len){return false;}
	virtual string getString() const;
	virtual string getScript() const;
	virtual string getString(INDEX index) const = 0;
	virtual VECTOR_TYPE getVectorType() const{return VECTOR_TYPE::ARRAY;}
	virtual bool isSorted(bool asc, bool strict = false) const {throw RuntimeException("Vector::isSorted method not supported"); return false;}
	virtual ConstantSP getInstance() const {return getInstance(size());}
	virtual ConstantSP getInstance(INDEX size) const = 0;
	virtual ConstantSP getValue(INDEX capacity) const {throw RuntimeException("Vector::getValue method not supported");}
	virtual ConstantSP get(INDEX column, INDEX rowStart,INDEX rowEnd) const {return getSubVector(column*rows()+rowStart,rowEnd-rowStart);}
	virtual ConstantSP get(INDEX index) const = 0;
	virtual ConstantSP getWindow(INDEX colStart, int colLength, INDEX rowStart, int rowLength) const {return getSubVector(rowStart,rowLength);}
	virtual ConstantSP getSubVector(INDEX start, INDEX length) const { throw RuntimeException("getSubVector method not supported");}
	virtual ConstantSP getSubVector(INDEX start, INDEX length, INDEX capacity) const { return getSubVector(start, length);}
	virtual void fill(INDEX start, INDEX length, const ConstantSP& value)=0;
	virtual void next(INDEX steps)=0;
	virtual void prev(INDEX steps)=0;
	virtual void reverse()=0;
	virtual void reverse(INDEX start, INDEX length)=0;
	virtual void replace(const ConstantSP& oldVal, const ConstantSP& newVal){}
	virtual bool validIndex(INDEX uplimit){return false;}
	virtual bool validIndex(INDEX start, INDEX length, INDEX uplimit){return false;}
	virtual void addIndex(INDEX start, INDEX length, INDEX offset){}
	virtual void neg()=0;
	virtual void upper(){throw RuntimeException("upper method not supported");}
	virtual void lower(){throw RuntimeException("lower method not supported");}
	virtual void trim(){throw RuntimeException("trim method not supported");}
	virtual void strip(){throw RuntimeException("strip method not supported");}
	virtual long long getAllocatedMemory(INDEX size) const {return Constant::getAllocatedMemory();}
	virtual int asof(const ConstantSP& value) const {throw RuntimeException("asof not supported.");}
	virtual ConstantSP castTemporal(DATA_TYPE expectType){throw RuntimeException("castTemporal not supported");}
private:
	string name_;
};

class EXPORT_DECL Matrix{
public:
	Matrix(int cols, int rows);
	virtual ~Matrix(){}
	void setRowLabel(const ConstantSP& label);
	void setColumnLabel(const ConstantSP& label);
	bool reshape(INDEX cols, INDEX rows);
	string getString() const;
	string getString(INDEX index) const ;
	ConstantSP get(const ConstantSP& index) const ;
	bool set(const ConstantSP index, const ConstantSP& value);
	virtual string getString(int column, int row) const = 0;
	virtual ConstantSP getInstance(INDEX size) const = 0;
	virtual ConstantSP getColumn(INDEX index) const = 0;
	virtual bool setColumn(INDEX index, const ConstantSP& value)=0;
	virtual int asof(const ConstantSP& value) const {throw RuntimeException("asof not supported.");}
protected:
	int cols_;
	int rows_;
	ConstantSP rowLabel_;
	ConstantSP colLabel_;
};

class EXPORT_DECL Set: public Constant {
public:
	Set() : Constant(1027){}
	virtual ~Set() {}
	virtual void clear()=0;
	virtual bool remove(const ConstantSP& value) = 0;
	virtual bool append(const ConstantSP& value) = 0;
	virtual bool inverse(const ConstantSP& value) = 0;
	virtual void contain(const ConstantSP& target, const ConstantSP& resultSP) const = 0;
	virtual bool isSuperset(const ConstantSP& target) const = 0;
	virtual ConstantSP interaction(const ConstantSP& target) const = 0;
	virtual ConstantSP getSubVector(INDEX start, INDEX length) const = 0;
	virtual string getScript() const {return "set()";}
	virtual bool isLargeConstant() const {return true;}
};

class EXPORT_DECL Dictionary:public Constant{
public:
	Dictionary() : Constant(1283){}
	virtual ~Dictionary() {}
	virtual INDEX size() const = 0;
	virtual INDEX count() const = 0;
	virtual void clear()=0;
	virtual ConstantSP getMember(const ConstantSP& key) const =0;
	virtual ConstantSP getMember(const string& key) const {throw RuntimeException("String key not supported");}
	virtual ConstantSP get(INDEX column, INDEX row){throw RuntimeException("Dictionary does not support cell function");}
	virtual DATA_TYPE getKeyType() const = 0;
	virtual DATA_CATEGORY getKeyCategory() const = 0;
	virtual DATA_TYPE getType() const = 0;
	virtual DATA_CATEGORY getCategory() const = 0;
	virtual ConstantSP keys() const = 0;
	virtual ConstantSP values() const = 0;
	virtual string getString() const = 0;
	virtual string getScript() const {return "dict()";}
	virtual string getString(int index) const {throw RuntimeException("Dictionary::getString(int index) not supported");}
	virtual bool remove(const ConstantSP& key) = 0;
	virtual bool set(const ConstantSP& key, const ConstantSP& value)=0;
	virtual bool set(const string& key, const ConstantSP& value){throw RuntimeException("String key not supported");}
	virtual ConstantSP get(const ConstantSP& key) const {return getMember(key);}
	virtual void contain(const ConstantSP& target, const ConstantSP& resultSP) const = 0;
	virtual bool isLargeConstant() const {return true;}

};

class EXPORT_DECL Table: public Constant{
public:
	Table() : Constant(1539){}
	virtual ~Table(){}
	virtual string getScript() const {return getName();}
	virtual ConstantSP getColumn(const string& name) const = 0;
	virtual ConstantSP getColumn(const string& qualifier, const string& name) const = 0;
	virtual ConstantSP getColumn(INDEX index) const = 0;
	virtual ConstantSP getColumn(const string& name, const ConstantSP& rowFilter) const = 0;
	virtual ConstantSP getColumn(const string& qualifier, const string& name, const ConstantSP& rowFilter) const = 0;
	virtual ConstantSP getColumn(INDEX index, const ConstantSP& rowFilter) const = 0;
	virtual INDEX columns() const = 0;
	virtual const string& getColumnName(int index) const = 0;
	virtual const string& getColumnQualifier(int index) const = 0;
	virtual void setColumnName(int index, const string& name)=0;
	virtual int getColumnIndex(const string& name) const = 0;
	virtual DATA_TYPE getColumnType(int index) const = 0;
	virtual bool contain(const string& name) const = 0;
	virtual bool contain(const string& qualifier, const string& name) const = 0;
	virtual void setName(const string& name)=0;
	virtual const string& getName() const = 0;
	virtual ConstantSP get(INDEX index) const {return getColumn(index);}
	virtual ConstantSP get(const ConstantSP& index) const = 0;
	virtual ConstantSP getValue(INDEX capacity) const = 0;
	virtual ConstantSP getValue() const = 0;
	virtual ConstantSP getInstance(INDEX size) const = 0;
	virtual INDEX size() const = 0;
	virtual bool sizeable() const = 0;
	virtual string getString(INDEX index) const = 0;
	virtual string getString() const = 0;
	virtual ConstantSP getWindow(INDEX colStart, int colLength, INDEX rowStart, int rowLength) const = 0;
	virtual ConstantSP getMember(const ConstantSP& key) const = 0;
	virtual ConstantSP values() const = 0;
	virtual ConstantSP keys() const = 0;
	virtual TABLE_TYPE getTableType() const = 0;
	virtual void drop(vector<int>& columns) {throw RuntimeException("Table::drop() not supported");}
	virtual bool update(vector<ConstantSP>& values, const ConstantSP& indexSP, vector<string>& colNames, string& errMsg) = 0;
	virtual bool append(vector<ConstantSP>& values, INDEX& insertedRows, string& errMsg) = 0;
	virtual bool remove(const ConstantSP& indexSP, string& errMsg) = 0;
	virtual DATA_TYPE getType() const {return DT_DICTIONARY;}
	virtual DATA_TYPE getRawType() const {return DT_DICTIONARY;}
	virtual DATA_CATEGORY getCategory() const {return MIXED;}
	virtual bool isLargeConstant() const {return true;}
	virtual void release() const {}
	virtual void checkout() const {}
	virtual long long getAllocatedMemory() const = 0;
	virtual ConstantSP getSubTable(vector<int> indices) const = 0;
	virtual COMPRESS_METHOD getColumnCompressMethod(INDEX index) = 0;
	virtual void setColumnCompressMethods(const vector<COMPRESS_METHOD> &methods) = 0;
};

class EXPORT_DECL DFSChunkMeta : public Constant{
public:
	DFSChunkMeta(const string& path, const Guid& id, int version, int size, CHUNK_TYPE chunkType, const vector<string>& sites, long long cid);
	DFSChunkMeta(const string& path, const Guid& id, int version, int size, CHUNK_TYPE chunkType, const string* sites, int siteCount, long long cid);
	DFSChunkMeta(const DataInputStreamSP& in);
	virtual ~DFSChunkMeta();
	virtual int size() const {return size_;}
	virtual string getString() const;
	virtual long long getAllocatedMemory() const;
	virtual ConstantSP getMember(const ConstantSP& key) const;
	virtual ConstantSP get(const ConstantSP& index) const {return getMember(index);}
	virtual ConstantSP keys() const;
	virtual ConstantSP values() const;
	virtual DATA_TYPE getType() const {return DT_DICTIONARY;}
	virtual DATA_TYPE getRawType() const {return DT_DICTIONARY;}
	virtual DATA_CATEGORY getCategory() const {return MIXED;}
	virtual ConstantSP getInstance() const {return getValue();}
	virtual ConstantSP getValue() const {return new DFSChunkMeta(path_, id_, version_, size_, (CHUNK_TYPE)type_, sites_, replicaCount_, cid_);}
	inline const string& getPath() const {return path_;}
	inline const Guid& getId() const {return id_;}
	inline long long getCommitId() const {return cid_;}
	inline void setCommitId(long long cid) { cid_ = cid;}
	inline int getVersion() const {return version_;}
	inline void setVersion(int version){version_ = version;}
	inline void setSize(int size){size_ = size;}
	inline int getCopyCount() const {return replicaCount_;}
	inline const string& getCopySite(int index) const {return sites_[index];}
	inline bool isTablet() const { return type_ == TABLET_CHUNK;}
	inline bool isFileBlock() const { return type_ == FILE_CHUNK;}
	inline bool isSplittable() const { return type_ == SPLIT_TABLET_CHUNK;}
	inline bool isSmallFileBlock() const {return type_ == SMALLFILE_CHUNK;}
	inline CHUNK_TYPE getChunkType() const {return (CHUNK_TYPE)type_;}

protected:
	ConstantSP getAttribute(const string& attr) const;
	ConstantSP getSiteVector() const;

private:
	char type_;
	char replicaCount_;
	int version_;
	int size_;
	string* sites_;
	string path_;
	long long cid_;
	Guid id_;
};

class EXPORT_DECL ConstantMarshall {
public:
	virtual ~ConstantMarshall(){}
	virtual bool start(const ConstantSP& target, bool blocking, bool compress, IO_ERR& ret)=0;
	virtual bool start(const char* requestHeader, size_t headerSize, const ConstantSP& target, bool blocking, bool compress, IO_ERR& ret)=0;
	virtual void reset() = 0;
	virtual IO_ERR flush() = 0;
};

class EXPORT_DECL ConstantUnmarshall{
public:
	virtual ~ConstantUnmarshall(){}
	virtual bool start(short flag, bool blocking, IO_ERR& ret)=0;
	virtual void reset() = 0;
	ConstantSP getConstant(){return obj_;}
	
protected:
	ConstantSP obj_;
};

class EXPORT_DECL Domain{
public:
	Domain(PARTITION_TYPE partitionType, DATA_TYPE partitionColType);
	virtual ~Domain(){}
	virtual vector<int> getPartitionKeys(const ConstantSP& partitionCol) const = 0;
	virtual PARTITION_TYPE getPartitionType(){
		return partitionType_;
	}
protected:
	PARTITION_TYPE partitionType_;
	DATA_TYPE partitionColType_;
	DATA_CATEGORY partitionColCategory_;
};

class EXPORT_DECL SymbolBase{
public:
	SymbolBase(int id):id_(id){}

	SymbolBase(const DataInputStreamSP& in, IO_ERR& ret);

	SymbolBase(int id, const DataInputStreamSP& in, IO_ERR& ret);

	const string& getSymbol(int index) const { return syms_[index];}

	int serialize(char* buf, int bufSize, INDEX indexStart, int offset, int& numElement, int& partial) const;
	
	int find(const string& symbol);

	int findAndInsert(const string& symbol);

	int size() const {return  symMap_.size();}

	const int& getID(){return id_;}
private:
	int id_;
	unordered_map<string, int> symMap_;
	vector<string> syms_;
};

class EXPORT_DECL DBConnection {
public:
	DBConnection(bool enableSSL = false, bool asyncTask = false, int keepAliveTime = 7200, bool compress = false, bool python = false, bool isReverseStreaming = false);
	~DBConnection();
	DBConnection(DBConnection&& oth);
	DBConnection& operator=(DBConnection&& oth);

	/**
	 * Connect to the specified DolphinDB server. If userId and password are specified, authentication
	 * will be performed along with connecting. If one would send userId and password in encrypted mode,
	 * please use the login function for authentication separately.
	 */
	bool connect(const string& hostName, int port, const string& userId = "", const string& password = "", const string& initialScript = "",
		bool highAvailability = false, const vector<string>& highAvailabilitySites = vector<string>(), int keepAliveTime=7200, bool reconnect = false);

	/**
	 * Log onto the DolphinDB server using the given userId and password. If the parameter enableEncryption
	 * is true, the client obtains a public key from the server and then encrypts the userId and password
	 * using the public key. If the parameter enableEncryption is false, userId and password are communicated
	 * in plain text.
	 */
	void login(const string& userId, const string& password, bool enableEncryption);

	/**
	 * Run the script on the DolphinDB server and return the result to the client.If nothing returns,
	 * the function returns a void object. If error is raised on the server, the function throws an
	 * exception.
	 */
	ConstantSP run(const string& script, int priority=4, int parallelism=2, int fetchSize=0, bool clearMemory = false);

	/**
	 * Run the given function on the DolphinDB server using the local objects as the arguments
	 * for the function and return the result to the client. If nothing returns, the function
	 * returns a void object. If error is raised on the server, the function throws an exception.
	 */
	ConstantSP run(const string& funcName, vector<ConstantSP>& args, int priority=4, int parallelism=2, int fetchSize=0, bool clearMemory = false);

	/**
	 * upload a local object to the DolphinDB server and assign the given name in the session.
	 */
	ConstantSP upload(const string& name, const ConstantSP& obj);

	/**
	 * upload multiple local objects to the DolphinDB server and assign each object the given
	 * name in the session.
	 */
	ConstantSP upload(vector<string>& names, vector<ConstantSP>& objs);

	/**
	 * Close the current session and release all resources.
	 */
	void close();

	/**
	 * It is required to call initialize function below before one uses the DolphinDB API.
	 */
	static void initialize(){}

	void setInitScript(const string& script);

	const string& getInitScript() const;
	SocketSP getSocket();
private:
    DBConnection(DBConnection& oth); // = delete
    DBConnection& operator=(DBConnection& oth); // = delete

private:
	enum ExceptionType {
		ET_IGNORE = 0,
		ET_UNKNOW = 1,
		ET_NEWLEADER = 2,
		ET_NODENOTAVAIL = 3,
	};
    void switchDataNode(const string &host = "", int port = -1);
	bool connectNode(string hostName, int port, int keepAliveTime = -1);
    bool connected();
	//0 - ignored exception, eg : other data node not avail;
	//1 - throw exception;
	//2 - new leader, host&port is valid
	//3 - this data node not avail
	ExceptionType parseException(const string &msg, string &host, int &port);

private:
	struct Node{
		string hostName;
		int port;
		double load;//DBL_MAX : unknow

		bool isEqual(const Node &node) {
			return hostName.compare(node.hostName) == 0 && port == node.port;
		}
		Node(){}
		Node(const string &hostName, int port, double load = DBL_MAX): hostName(hostName), port(port), load(load){}
		Node(const string &ipport, double loadValue = DBL_MAX);
	};
	static void parseIpPort(const string &ipport, string &ip, int &port);

    std::unique_ptr<DBConnectionImpl> conn_;
    string uid_;
    string pwd_;
    string initialScript_;
    bool ha_;
	bool enableSSL_;
    bool asynTask_;
    bool compress_;
	vector<Node> nodes_;
	int lastConnNodeIndex_;
	bool enablePickle_, python_;
	bool reconnect_, closed_;
	static const int maxRerunCnt_ = 30;
};

class EXPORT_DECL BlockReader : public Constant{
public:
    BlockReader(const DataInputStreamSP& in );
	virtual ~BlockReader();
    ConstantSP read();
    void skipAll();
    bool hasNext() const {return currentIndex_ < total_;}
    virtual DATA_TYPE getType() const {return DT_ANY;}
    virtual DATA_TYPE getRawType() const {return DT_ANY;}
    virtual DATA_CATEGORY getCategory() const {return MIXED;}
    virtual ConstantSP getInstance() const {return nullptr;}
    virtual ConstantSP getValue() const {return nullptr;}
private:
    DataInputStreamSP in_;
    int total_;
    int currentIndex_;
};


class EXPORT_DECL DBConnectionPool{
public:
    DBConnectionPool(const string& hostName, int port, int threadNum = 10, const string& userId = "", const string& password = "",
		bool loadBalance = false, bool highAvailability = false, bool compress = false, bool reConnect = false, bool python = false);
	~DBConnectionPool();
	void run(const string& script, int identity, int priority=4, int parallelism=2, int fetchSize=0, bool clearMemory = false);
	
	void run(const string& functionName, const vector<ConstantSP>& args, int identity, int priority=4, int parallelism=2, int fetchSize=0, bool clearMemory = false);
    
	bool isFinished(int identity);

    ConstantSP getData(int identity);
	
    void shutDown();

    bool isShutDown();

	int getConnectionCount();
private:
	SmartPointer<DBConnectionPoolImpl> pool_;
	friend class PartitionedTableAppender; 

};

class EXPORT_DECL PartitionedTableAppender {
public:
	PartitionedTableAppender(string dbUrl, string tableName, string partitionColName, DBConnectionPool& pool);

	PartitionedTableAppender(string dbUrl, string tableName, string partitionColName, string appendFunction, DBConnectionPool& pool);
	~PartitionedTableAppender();
	int append(TableSP table);

private:
 	void init(string dbUrl, string tableName, string partitionColName, string appendFunction);

	void checkColumnType(int col, DATA_CATEGORY category, DATA_TYPE type);

private:
	SmartPointer<DBConnectionPoolImpl> pool_;
	string appendScript_;
	int threadCount_;
    DictionarySP tableInfo_;
	int partitionColumnIdx_;
	int cols_;
    DomainSP domain_;
    vector<DATA_CATEGORY> columnCategories_;
 	vector<DATA_TYPE> columnTypes_;
	int identity_ = -1;
    vector<vector<int>> chunkIndices_;
};


class EXPORT_DECL AutoFitTableAppender {
public:
	AutoFitTableAppender(string dbUrl, string tableName, DBConnection& conn);

	int append(TableSP table);

private:
	void checkColumnType(int col, DATA_CATEGORY category, DATA_TYPE type);

private:
    DBConnection& conn_;
	string appendScript_;
	int cols_;
    vector<DATA_CATEGORY> columnCategories_;
 	vector<DATA_TYPE> columnTypes_;
	vector<string> columnNames_;
};

class EXPORT_DECL AutoFitTableUpsert {
public:
	AutoFitTableUpsert(string dbUrl, string tableName, DBConnection& conn,bool ignoreNull=false,
                                        vector<string> *pkeyColNames=nullptr,vector<string> *psortColumns=nullptr);

	int upsert(TableSP table);

private:
	void checkColumnType(int col, DATA_CATEGORY category, DATA_TYPE type);

private:
    DBConnection& conn_;
	string upsertScript_;
	int cols_;
    vector<DATA_CATEGORY> columnCategories_;
 	vector<DATA_TYPE> columnTypes_;
	vector<string> columnNames_;
};

class EXPORT_DECL ErrorCodeInfo {
public:
	enum ErrorCode {
		EC_None = 0,
		EC_InvalidObject=1,
		EC_InvalidParameter=2,
		EC_InvalidTable=3,
		EC_InvalidColumnType=4,
		EC_Server=5,
		EC_UserBreak=6,
		EC_DestroyedObject=7,
		EC_Other=8,
	};
	ErrorCodeInfo() {
	}
	void clearError(){
		errorCode.clear();
	}
	bool hasError(){
		return errorCode.empty() == false;
	}
	bool succeed() {
		return errorCode.empty();
	}
	static string formatApiCode(int code){
		if(code != EC_None)
			return "A" + std::to_string(code);
		else
			return "";
	}
	void set(int apiCode, const string &info);
	void set(const string &code, const string &info);
	void set(const ErrorCodeInfo &src);
	string errorCode;
	string errorInfo;
};


class EXPORT_DECL RecordTime {
public:
	RecordTime(const string &name);
	~RecordTime();
	static std::string printAllTime();
private:
	const string name_;
	long recordOrder_;
	long long startTime_;
	struct Node {
		string name;
		long minOrder;
		std::vector<long long> costTime;//ns
	};
	static long lastRecordOrder_;
	static Mutex mapMutex_;
	static std::unordered_map<std::string, RecordTime::Node*> codeMap_;
};

class EXPORT_DECL DLogger {
public:
	enum Level {
		LevelDebug,
		LevelInfo,
		LevelWarn,
		LevelError,
		LevelCount,
	};
	template<typename... TArgs>
	static bool Info(TArgs... args) {
		std::string text;
		return Write(text, LevelInfo, 0, args...);
	}
	template<typename... TArgs>
	static bool Debug(TArgs... args) {
		std::string text;
		return Write(text, LevelDebug, 0, args...);
	}
	template<typename... TArgs>
	static bool Warn(TArgs... args) {
		std::string text;
		return Write(text, LevelWarn, 0, args...);
	}
	template<typename... TArgs>
	static bool Error(TArgs... args) {
		std::string text;
		return Write(text, LevelError, 0, args...);
	}
	static void SetLogFilePath(const std::string &filepath){ logFilePath_=filepath; }
	static void SetMinLevel(Level level);
	static Level GetMinLevel(){ return minLevel_; }
private:
	static Level minLevel_;
	static std::string logFilePath_;
	static std::string levelText_[LevelCount];
	static bool FormatFirst(std::string &text, Level level);
	static bool WriteLog(std::string &text);
	template<typename TA, typename... TArgs>
	static bool Write(std::string &text, Level level, int deepth, TA first, TArgs... args) {
		if (deepth == 0) {
			if (FormatFirst(text, level) == false)
				return false;
		}
		text += " " + Create(first);
		return Write(text, level, deepth + 1, args...);
	}
	template<typename TA>
	static bool Write(std::string &text, Level level, int deepth, TA first) {
		if (deepth == 0) {
			if (FormatFirst(text, level) == false)
				return false;
		}
		text += " " + Create(first);
		return WriteLog(text);
	}
	static std::string Create(const char *value) {
		std::string str(value);
		return str;
	}
	static std::string Create(const void *value) {
		return Create((unsigned long long)value);
	}
	static std::string Create(std::string str) {
		return str;
	}
	static std::string Create(int value) {
		return std::to_string(value);
	}
	static std::string Create(char value) {
		return std::string(&value, 1);
	}
	static std::string Create(unsigned value) {
		return std::to_string(value);
	}
	static std::string Create(long value) {
		return std::to_string(value);
	}
	static std::string Create(unsigned long value) {
		return std::to_string(value);
	}
	static std::string Create(long long value) {
		return std::to_string(value);
	}
	static std::string Create(unsigned long long value) {
		return std::to_string(value);
	}
	static std::string Create(float value) {
		return std::to_string(value);
	}
	static std::string Create(double value) {
		return std::to_string(value);
	}
	static std::string Create(long double value) {
		return std::to_string(value);
	}
};
}

namespace std {
template<>
struct hash<dolphindb::Guid> {
	size_t operator()(const dolphindb::Guid& val) const;
};

}


#endif /* DOLPHINDB_H_ */
