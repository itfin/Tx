/*
 * ScalarImp.h
 *
 *  Created on: May 10, 2017
 *      Author: dzhou
 */

#ifndef SCALARIMP_H_
#define SCALARIMP_H_

#include <climits>

#include "DolphinDB.h"
#include "Util.h"

using std::ostringstream;

namespace dolphindb {

void initFormatters();
//-----------------------------------------------------------------------------
// MurmurHash2, by Austin Appleby

// Note - This code makes a few assumptions about how your machine behaves -

// 1. We can read a 4-byte value from any address without crashing
// 2. sizeof(int) == 4

// And it has a few limitations -

// 1. It will not work incrementally.
// 2. It will not produce the same results on little-endian and big-endian
//    machines.

static inline uint32_t murmur32 (const char *key, int len){
	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.

	const uint32_t m = 0x5bd1e995;
	const int r = 24;

	// Initialize the hash to a 'random' value
	uint32_t h = len;

	// Mix 4 bytes at a time into the hash

	const unsigned char *data = (const unsigned char *)key;

	while(len >= 4)
	{
		uint32_t k = *(uint32_t *)data;

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: h ^= data[2] << 16;
	/* no break */
	case 2: h ^= data[1] << 8;
	/* no break */
	case 1: h ^= data[0];
	        h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}

static inline uint32_t murmur32_16b (const unsigned char* key){
    const uint32_t m = 0x5bd1e995;
    const int r = 24;
    uint32_t h = 16;

    uint32_t k1 = *(uint32_t*)(key);
    uint32_t k2 = *(uint32_t*)(key + 4);
    uint32_t k3 = *(uint32_t*)(key + 8);
    uint32_t k4 = *(uint32_t*)(key + 12);

    k1 *= m;
    k1 ^= k1 >> r;
    k1 *= m;

    k2 *= m;
    k2 ^= k2 >> r;
    k2 *= m;

    k3 *= m;
    k3 ^= k3 >> r;
    k3 *= m;

    k4 *= m;
    k4 ^= k4 >> r;
    k4 *= m;

    // Mix 4 bytes at a time into the hash
    h *= m;
    h ^= k1;
    h *= m;
    h ^= k2;
    h *= m;
    h ^= k3;
    h *= m;
    h ^= k4;

    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.
    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

static inline uint32_t murmur32_8b (uint64_t key){
    // 'm' and 'r' are mixing constants generated offline.
    // They're not really 'magic', they just happen to work well.

    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    // Initialize the hash to a 'random' value
    uint32_t h = 8;

    uint32_t k1 = (uint32_t)(key >> 32);
    uint32_t k2 = (uint32_t)key;

    k1 *= m;
    k1 ^= k1 >> r;
    k1 *= m;

    k2 *= m;
    k2 ^= k2 >> r;
    k2 *= m;

    // Mix 4 bytes at a time into the hash

    h *= m;
    h ^= k1;
    h *= m;
    h ^= k2;

    // Do a few final mixes of the hash to ensure the last few
    // bytes are well-incorporated.

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

class Void: public Constant{
public:
	Void(bool explicitNull = false){setNothing(!explicitNull);}
	virtual ConstantSP getInstance() const {return ConstantSP(new Void(!isNothing()));}
	virtual ConstantSP getValue() const {return ConstantSP(new Void(!isNothing()));}
	virtual DATA_TYPE getType() const {return DT_VOID;}
	virtual DATA_TYPE getRawType() const { return DT_VOID;}
	virtual DATA_CATEGORY getCategory() const {return NOTHING;}
	virtual string getString() const {return Constant::EMPTY;}
	virtual string getScript() const {return isNothing() ? Constant::EMPTY : Constant::NULL_STR;}
	virtual const string& getStringRef() const {return Constant::EMPTY;}
	virtual char getBool() const {return CHAR_MIN;}
	virtual char getChar() const {return CHAR_MIN;}
	virtual short getShort() const {return SHRT_MIN;}
	virtual int getInt() const {return INT_MIN;}
	virtual long long  getLong() const {return LLONG_MIN;}
	virtual float getFloat() const {return FLT_NMIN;}
	virtual double getDouble() const {return DBL_NMIN;}
	virtual bool isNull() const {return true;}
	virtual void nullFill(const ConstantSP& val){}
	virtual bool isNull(INDEX start, int len, char* buf) const;
	virtual bool isValid(INDEX start, int len, char* buf) const;
	virtual bool getBool(INDEX start, int len, char* buf) const;
	virtual const char* getBoolConst(INDEX start, int len, char* buf) const;
	virtual bool getChar(INDEX start, int len, char* buf) const;
	virtual const char* getCharConst(INDEX start, int len, char* buf) const;
	virtual bool getShort(INDEX start, int len, short* buf) const;
	virtual const short* getShortConst(INDEX start, int len, short* buf) const;
	virtual bool getInt(INDEX start, int len, int* buf) const;
	virtual const int* getIntConst(INDEX start, int len, int* buf) const;
	virtual bool getLong(INDEX start, int len, long long* buf) const;
	virtual const long long* getLongConst(INDEX start, int len, long long* buf) const;
	virtual bool getIndex(INDEX start, int len, INDEX* buf) const;
	virtual const INDEX* getIndexConst(INDEX start, int len, INDEX* buf) const;
	virtual bool getFloat(INDEX start, int len, float* buf) const;
	virtual const float* getFloatConst(INDEX start, int len, float* buf) const;
	virtual bool getDouble(INDEX start, int len, double* buf) const;
	virtual const double* getDoubleConst(INDEX start, int len, double* buf) const;
	virtual bool getString(INDEX start, int len, string** buf) const;
	virtual string** getStringConst(INDEX start, int len, string** buf) const;
	virtual long long getAllocatedMemory() const;
	virtual int serialize(char* buf, int bufSize, INDEX indexStart, int offset, int& numElement, int& partial) const;
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	virtual int compare(INDEX index, const ConstantSP& target) const {return target->getType() == DT_VOID ? 0 : -1;}
};

class Int128: public Constant{
public:
	Int128();
	Int128(const unsigned char* data);
	virtual ~Int128(){}
	inline const unsigned char* bytes() const { return uuid_;}
	virtual string getString() const { return toString(uuid_);}
	virtual const Guid getInt128() const { return uuid_;}
	virtual const unsigned char* getBinary() const {return uuid_;}
	virtual bool isNull() const;
	virtual void setNull();
	virtual void nullFill(const ConstantSP& val){
		if(isNull())
			memcpy(uuid_, val->getInt128().bytes(), 16);
	}
	virtual bool isNull(INDEX start, int len, char* buf) const {
		char null=isNull();
		for(int i=0;i<len;++i)
			buf[i]=null;
		return true;
	}
	virtual bool isValid(INDEX start, int len, char* buf) const {
		char valid=!isNull();
		for(int i=0;i<len;++i)
			buf[i]=valid;
		return true;
	}
	virtual int compare(INDEX index, const ConstantSP& target) const;
	virtual void setBinary(const unsigned char* val, int unitLength);
	virtual bool getBinary(INDEX start, int len, int unitLenght, unsigned char* buf) const;
	virtual const unsigned char* getBinaryConst(INDEX start, int len, int unitLength, unsigned char* buf) const;
	virtual ConstantSP getInstance() const {return new Int128();}
	virtual ConstantSP getValue() const {return new Int128(uuid_);}
	virtual DATA_TYPE getType() const {return DT_INT128;}
	virtual DATA_TYPE getRawType() const { return DT_INT128;}
	virtual DATA_CATEGORY getCategory() const {return BINARY;}
	virtual long long getAllocatedMemory() const {return sizeof(Int128);}
	virtual int serialize(char* buf, int bufSize, INDEX indexStart, int offset, int& numElement, int& partial) const;
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	virtual int getHash(int buckets) const { return murmur32_16b(uuid_) % buckets;}
	static string toString(const unsigned char* data);
	static Int128* parseInt128(const char* str, int len);
	static bool parseInt128(const char* str, int len, unsigned char *buf);

protected:
	union{
		mutable unsigned char uuid_[16];
		Guid guid_;
	};
};

class Uuid : public Int128 {
public:
	Uuid(bool newUuid = false);
	Uuid(const unsigned char* uuid);
	Uuid(const char* uuid, int len);
	Uuid(const Uuid& copy);
	virtual ~Uuid(){}
	virtual ConstantSP getInstance() const {return new Uuid(false);}
	virtual ConstantSP getValue() const {return new Uuid(uuid_);}
	virtual DATA_TYPE getType() const {return DT_UUID;}
	virtual DATA_TYPE getRawType() const { return DT_INT128;}
	virtual string getString() const { return Guid::getString(uuid_);}
	static Uuid* parseUuid(const char* str, int len);
};

class IPAddr : public Int128 {
public:
	IPAddr();
	IPAddr(const char* ip, int len);
	IPAddr(const unsigned char* data);
	virtual ~IPAddr(){}
	virtual ConstantSP getInstance() const {return new IPAddr();}
	virtual ConstantSP getValue() const {return new IPAddr(uuid_);}
	virtual DATA_TYPE getType() const {return DT_IP;}
	virtual DATA_TYPE getRawType() const { return DT_INT128;}
	virtual string getString() const { return toString(uuid_);}
	static string toString(const unsigned char* data);
	static IPAddr* parseIPAddr(const char* str, int len);
	static bool parseIPAddr(const char* str, size_t len, unsigned char* buf);

private:
	static bool parseIP4(const char* str, size_t len, unsigned char* buf);
	static bool parseIP6(const char* str, size_t len, unsigned char* buf);
};

class String: public Constant{
public:
	String(string val="", bool blob=false):val_(val), blob_(blob){}
	virtual ~String(){}
	virtual char getBool() const {throw IncompatibleTypeException(DT_BOOL,DT_STRING);}
	virtual char getChar() const {throw IncompatibleTypeException(DT_CHAR,DT_STRING);}
	virtual short getShort() const {throw IncompatibleTypeException(DT_SHORT,DT_STRING);}
	virtual int getInt() const {throw IncompatibleTypeException(DT_INT,DT_STRING);}
	virtual long long getLong() const {throw IncompatibleTypeException(DT_LONG,DT_STRING);}
	virtual INDEX getIndex() const {throw IncompatibleTypeException(DT_INDEX,DT_STRING);}
	virtual float getFloat() const {throw IncompatibleTypeException(DT_FLOAT,DT_STRING);}
	virtual double getDouble() const {throw IncompatibleTypeException(DT_DOUBLE,DT_STRING);}
	virtual string getString() const {return val_;}
	virtual string getScript() const {return Util::literalConstant(val_);}
	virtual const string& getStringRef() const {return val_;}
	virtual const string& getStringRef(INDEX index) const {return val_;}
	virtual bool isNull() const {return val_.empty();}
	virtual void setString(const string& val) {val_=val;}
	virtual void setNull(){val_="";}
	virtual void nullFill(const ConstantSP& val){
		if(isNull())
			val_=val->getStringRef();
	}
	virtual bool isNull(INDEX start, int len, char* buf) const {
		char null=isNull();
		for(int i=0;i<len;++i)
			buf[i]=null;
		return true;
	}
	virtual bool isValid(INDEX start, int len, char* buf) const {
		char valid=!isNull();
		for(int i=0;i<len;++i)
			buf[i]=valid;
		return true;
	}
	virtual bool getString(INDEX start, int len, string** buf) const {
		for(int i=0;i<len;++i)
			buf[i]=&val_;
		return true;
	}
	virtual string** getStringConst(INDEX start, int len, string** buf) const {
		for(int i=0;i<len;++i)
			buf[i]=&val_;
		return buf;
	}
	virtual char** getStringConst(INDEX start, int len, char** buf) const {
		char* val = (char*)val_.c_str();
		for(int i=0;i<len;++i)
			buf[i]=val;
		return buf;
	}
	virtual ConstantSP getInstance() const {return ConstantSP(new String("", blob_));}
	virtual ConstantSP getValue() const {return ConstantSP(new String(val_, blob_));}
	virtual DATA_TYPE getType() const {return blob_ == false ? DT_STRING : DT_BLOB;}
	virtual DATA_TYPE getRawType() const {return blob_ == false ? DT_STRING : DT_BLOB;}
	virtual DATA_CATEGORY getCategory() const {return LITERAL;}
	virtual long long getAllocatedMemory() const {return sizeof(string)+val_.size();}
	virtual int serialize(char* buf, int bufSize, INDEX indexStart, int offset, int& numElement, int& partial) const;
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	virtual int compare(INDEX index, const ConstantSP& target) const {
		return val_.compare(target->getString());
	}
	virtual int getHash(int buckets) const { return murmur32(val_.data(), val_.size()) % buckets;}

private:
	mutable string val_;
    bool blob_;
};

template <class T>
class AbstractScalar: public Constant{
public:
	AbstractScalar(T val=0):val_(val){}
	virtual ~AbstractScalar(){}
	virtual char getBool() const {return isNull()?CHAR_MIN:(bool)val_;}
	virtual char getChar() const {return isNull()?CHAR_MIN:val_;}
	virtual short getShort() const {return isNull()?SHRT_MIN:val_;}
	virtual int getInt() const {return isNull()?INT_MIN:val_;}
	virtual long long getLong() const {return isNull()?LLONG_MIN:val_;}
	virtual INDEX getIndex() const {return isNull()?INDEX_MIN:val_;}
	virtual float getFloat() const {return isNull()?FLT_NMIN:val_;}
	virtual double getDouble() const {return isNull()?DBL_NMIN:val_;}

	virtual void setBool(char val){if(val != CHAR_MIN) val_=(T)val; else setNull();}
	virtual void setChar(char val){if(val != CHAR_MIN) val_=(T)val; else setNull();}
	virtual void setShort(short val){if(val != SHRT_MIN) val_=(T)val; else setNull();}
	virtual void setInt(int val){if(val != INT_MIN) val_=(T)val; else setNull();}
	virtual void setLong(long long val){if(val != LLONG_MIN) val_=(T)val; else setNull();}
	virtual void setIndex(INDEX val){if(val != INDEX_MIN) val_=(T)val; else setNull();}
	virtual void setFloat(float val){if(val != FLT_NMIN) val_=(T)val; else setNull();}
	virtual void setDouble(double val){if(val != DBL_NMIN) val_=(T)val; else setNull();}
	virtual void setString(const string& val){}
	virtual bool isNull() const = 0;
	virtual string getScript() const {
		if(isNull()){
			string str("00");
			return str.append(1, Util::getDataTypeSymbol(getType()));
		}
		else
			return getString();
	}

	virtual void nullFill(const ConstantSP& val){
		if(isNull()){
			if(val->getCategory()==FLOATING)
				val_=val->getDouble();
			else
				val_=val->getLong();
		}
	}
	virtual bool isNull(INDEX start, int len, char* buf) const {
		char null=isNull();
		for(int i=0;i<len;++i)
			buf[i]=null;
		return true;
	}
	virtual bool isValid(INDEX start, int len, char* buf) const {
		char valid=!isNull();
		for(int i=0;i<len;++i)
			buf[i]=valid;
		return true;
	}
	virtual bool getBool(INDEX start, int len, char* buf) const {
		char tmp=isNull()?CHAR_MIN:(bool)val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
	}
	virtual const char* getBoolConst(INDEX start, int len, char* buf) const {
		char tmp=isNull()?CHAR_MIN:(bool)val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
	}
	virtual bool getChar(INDEX start, int len, char* buf) const {
		char tmp=isNull()?CHAR_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
	}
	virtual const char* getCharConst(INDEX start, int len, char* buf) const {
		char tmp=isNull()?CHAR_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
	}
	virtual bool getShort(INDEX start, int len, short* buf) const {
		short tmp=isNull()?SHRT_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
	}
	virtual const short* getShortConst(INDEX start, int len, short* buf) const {
		short tmp=isNull()?SHRT_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
	}
	virtual bool getInt(INDEX start, int len, int* buf) const {
		int tmp=isNull()?INT_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
	}
	virtual const int* getIntConst(INDEX start, int len, int* buf) const {
		int tmp=isNull()?INT_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
	}
	virtual bool getLong(INDEX start, int len, long long* buf) const {
		long long tmp=isNull()?LLONG_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
	}
	virtual const long long* getLongConst(INDEX start, int len, long long* buf) const {
		long long tmp=isNull()?LLONG_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
	}
	virtual bool getIndex(INDEX start, int len, INDEX* buf) const {
		INDEX tmp=isNull()?INDEX_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
	}
	virtual const INDEX* getIndexConst(INDEX start, int len, INDEX* buf) const {
		INDEX tmp=isNull()?INDEX_MIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
	}
	virtual bool getFloat(INDEX start, int len, float* buf) const {
		float tmp=isNull()?FLT_NMIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
    }
	virtual const float* getFloatConst(INDEX start, int len, float* buf) const {
		float tmp=isNull()?FLT_NMIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
    }
	virtual bool getDouble(INDEX start, int len, double* buf) const {
		double tmp=isNull()?DBL_NMIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return true;
	}
	virtual const double* getDoubleConst(INDEX start, int len, double* buf) const {
		double tmp=isNull()?DBL_NMIN:val_;
		for(int i=0;i<len;++i)
			buf[i]=tmp;
		return buf;
	}
	virtual long long getAllocatedMemory() const {return sizeof(AbstractScalar);}
	virtual int serialize(char* buf, int bufSize, INDEX indexStart, int offset, int& numElement, int& partial) const {
		int len = sizeof(T)-offset;
		if(len < 0)
			return -1;
		else if(bufSize >= len){
			numElement = 1;
			partial = 0;
			memcpy(buf,((char*)&val_)+offset, len);
			return len;
		}
		else{
			len = bufSize;
			numElement = 0;
			partial = offset+bufSize;
			memcpy(buf,((char*)&val_)+offset, len);
			return len;
		}
	}

	virtual bool add(INDEX start, INDEX length, long long inc) {
		if(isNull())
			return false;
		val_ += inc;
		return true;
	}

	virtual bool add(INDEX start, INDEX length, double inc) {
		if(isNull())
			return false;
		val_ += inc;
		return true;
	}

	virtual int compare(INDEX index, const ConstantSP& target) const {
		if(getCategory() == FLOATING){
			T val= (T)target->getDouble();
			return val_==val?0:(val_<val?-1:1);
		}
		else{
			T val= (T)target->getLong();
			return val_==val?0:(val_<val?-1:1);
		}
	}

protected:
	T val_;
};

class Bool: public AbstractScalar<char>{
public:
	Bool(char val=0):AbstractScalar(val){}
	virtual ~Bool(){}
	virtual bool isNull() const {return val_==CHAR_MIN;}
	virtual void setNull(){val_= CHAR_MIN;}
	virtual void setBool(char val){ val_ = val;}
	virtual DATA_TYPE getType() const {return DT_BOOL;}
	virtual DATA_TYPE getRawType() const { return DT_BOOL;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Bool());}
	virtual ConstantSP getValue() const {return ConstantSP(new Bool(val_));}
	virtual DATA_CATEGORY getCategory() const {return LOGICAL;}
	virtual string getString() const { return toString(val_);}
	virtual bool add(INDEX start, INDEX length, long long inc) { return false;}
	virtual bool add(INDEX start, INDEX length, double inc) { return false;}
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	static Bool* parseBool(const string& str);
	static string toString(char val){
		if(val == CHAR_MIN)
			return "";
		else if(val)
			return "1";
		else
			return "0";
	}
};

class Char: public AbstractScalar<char>{
public:
	Char(char val=0):AbstractScalar(val){}
	virtual ~Char(){}
	virtual bool isNull() const {return val_==CHAR_MIN;}
	virtual void setNull(){val_=CHAR_MIN;}
	virtual void setChar(char val){ val_ = val;}
	virtual DATA_TYPE getType() const {return DT_CHAR;}
	virtual DATA_TYPE getRawType() const { return DT_CHAR;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Char());}
	virtual ConstantSP getValue() const {return ConstantSP(new Char(val_));}
	virtual DATA_CATEGORY getCategory() const {return INTEGRAL;}
	virtual string getString() const { return toString(val_);}
	virtual string getScript() const;
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	virtual int getHash(int buckets) const { return val_ == CHAR_MIN ? -1 : ((unsigned int)val_) % buckets;}
	static Char* parseChar(const string& str);
	static string toString(char val);
};

class Short: public AbstractScalar<short>{
public:
	Short(short val=0):AbstractScalar(val){}
	virtual ~Short(){}
	virtual bool isNull() const {return val_==SHRT_MIN;}
	virtual void setNull(){val_=SHRT_MIN;}
	virtual void setShort(short val){ val_ = val;}
	virtual DATA_TYPE getType() const {return DT_SHORT;}
	virtual DATA_TYPE getRawType() const { return DT_SHORT;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Short());}
	virtual ConstantSP getValue() const {return ConstantSP(new Short(val_));}
	virtual DATA_CATEGORY getCategory() const {return INTEGRAL;}
	virtual string getString() const { return toString(val_);}
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	virtual int getHash(int buckets) const { return val_ == SHRT_MIN ? -1 : ((unsigned int)val_) % buckets;}
	static Short* parseShort(const string& str);
	static string toString(short val);
};

class Int: public AbstractScalar<int>{
public:
	Int(int val=0):AbstractScalar(val){}
	virtual ~Int(){}
	virtual bool isNull() const {return val_==INT_MIN;}
	virtual void setNull(){val_=INT_MIN;}
	virtual void setInt(int val){ val_ = val;}
	virtual DATA_TYPE getType() const {return DT_INT;}
	virtual DATA_TYPE getRawType() const { return DT_INT;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Int());}
	virtual ConstantSP getValue() const {return ConstantSP(new Int(val_));}
	virtual DATA_CATEGORY getCategory() const {return INTEGRAL;}
	virtual string getString() const { return toString(val_);}
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	virtual int getHash(int buckets) const { return val_ == INT_MIN ? -1 : ((uint32_t)val_) % buckets;}
	static Int* parseInt(const string& str);
	static string toString(int val);
};

class EnumInt : public Int {
public:
	EnumInt(const string& desc, int val):Int(val), desc_(desc){}
	virtual ~EnumInt(){}
	virtual string getScript() const {return desc_;}
	virtual ConstantSP getValue() const {return ConstantSP(new EnumInt(desc_, val_));}
	virtual ConstantSP getInstance() const {return ConstantSP(new EnumInt(desc_, val_));}
	virtual string getString() const {return desc_;}

private:
	string desc_;
};

class Long: public AbstractScalar<long long>{
public:
	Long(long long val=0):AbstractScalar(val){}
	virtual ~Long(){}
	virtual bool isNull() const {return val_==LLONG_MIN;}
	virtual void setNull(){val_=LLONG_MIN;}
	virtual void setLong(long long val){ val_ = val;}
	virtual DATA_TYPE getType() const {return DT_LONG;}
	virtual DATA_TYPE getRawType() const { return DT_LONG;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Long());}
	virtual ConstantSP getValue() const {return ConstantSP(new Long(val_));}
	virtual string getString() const { return toString(val_);}
	virtual DATA_CATEGORY getCategory() const {return INTEGRAL;}
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	virtual int getHash(int buckets) const { return val_ == LLONG_MIN ? -1 : ((uint64_t)val_) % buckets;}
	static Long* parseLong(const string& str);
	static string toString(long long val);
};

class Float: public AbstractScalar<float>{
public:
	Float(float val=0):AbstractScalar(val){}
	virtual ~Float(){}
	virtual bool isNull() const {return val_==FLT_NMIN;}
	virtual void setNull(){val_=FLT_NMIN;}
	virtual void setFloat(float val){ val_ = val;}
	virtual DATA_TYPE getType() const {return DT_FLOAT;}
	virtual DATA_TYPE getRawType() const { return DT_FLOAT;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Float());}
	virtual ConstantSP getValue() const {return ConstantSP(new Float(val_));}
	virtual DATA_CATEGORY getCategory() const {return FLOATING;}
	virtual char getChar() const {return isNull()?CHAR_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual short getShort() const {return isNull()?SHRT_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual int getInt() const {return isNull()?INT_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual long long  getLong() const {return isNull()?LLONG_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual bool getChar(INDEX start, int len, char* buf) const;
	virtual const char* getCharConst(INDEX start, int len, char* buf) const;
	virtual bool getShort(INDEX start, int len, short* buf) const;
	virtual const short* getShortConst(INDEX start, int len, short* buf) const;
	virtual bool getInt(INDEX start, int len, int* buf) const;
	virtual const int* getIntConst(INDEX start, int len, int* buf) const;
	virtual bool getLong(INDEX start, int len, long long* buf) const;
	virtual const long long* getLongConst(INDEX start, int len, long long* buf) const;
	virtual string getString() const { return toString(val_);}
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	static Float* parseFloat(const string& str);
	static string toString(float val);
};

class Double: public AbstractScalar<double>{
public:
	Double(double val=0):AbstractScalar(val){}
	virtual ~Double(){}
	virtual bool isNull() const {return val_==DBL_NMIN;}
	virtual void setNull(){val_=DBL_NMIN;}
	virtual void setDouble(double val){ val_ = val;}
	virtual DATA_TYPE getType() const {return DT_DOUBLE;}
	virtual DATA_TYPE getRawType() const { return DT_DOUBLE;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Double());}
	virtual ConstantSP getValue() const {return ConstantSP(new Double(val_));}
	virtual DATA_CATEGORY getCategory() const {return FLOATING;}
	virtual char getChar() const {return isNull()?CHAR_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual short getShort() const {return isNull()?SHRT_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual int getInt() const {return isNull()?INT_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual long long  getLong() const {return isNull()?LLONG_MIN:(val_<0?val_-0.5:val_+0.5);}
	virtual bool getChar(INDEX start, int len, char* buf) const;
	virtual const char* getCharConst(INDEX start, int len, char* buf) const;
	virtual bool getShort(INDEX start, int len, short* buf) const;
	virtual const short* getShortConst(INDEX start, int len, short* buf) const;
	virtual bool getInt(INDEX start, int len, int* buf) const;
	virtual const int* getIntConst(INDEX start, int len, int* buf) const;
	virtual bool getLong(INDEX start, int len, long long* buf) const;
	virtual const long long* getLongConst(INDEX start, int len, long long* buf) const;
	virtual string getString() const {return toString(val_);}
	virtual IO_ERR deserialize(DataInputStream* in, INDEX indexStart, INDEX targetNumElement, INDEX& numElement);
	static Double* parseDouble(const string& str);
	static string toString(double val);
};

class EnumDouble : public Double {
public:
	EnumDouble(const string& desc, double val):Double(val), desc_(desc){}
	virtual ~EnumDouble(){}
	virtual string getScript() const {return desc_;}
	virtual ConstantSP getValue() const {return ConstantSP(new EnumDouble(desc_, val_));}
	virtual ConstantSP getInstance() const {return ConstantSP(new EnumDouble(desc_, val_));}
	virtual string getString() const { return desc_;}

private:
	string desc_;
};

class TemporalScalar:public Int{
public:
	TemporalScalar(int val=0):Int(val){}
	virtual ~TemporalScalar(){}
	virtual DATA_CATEGORY getCategory() const {return TEMPORAL;}
};

class Date:public TemporalScalar{
public:
	Date(int val=0):TemporalScalar(val){}
	virtual ~Date(){}
	Date(int year, int month, int day):TemporalScalar(Util::countDays(year,month,day)){}
	virtual DATA_TYPE getType() const {return DT_DATE;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Date());}
	virtual ConstantSP getValue() const {return ConstantSP(new Date(val_));}
	virtual string getString() const { return toString(val_);}
	static Date* parseDate(const string& str);
	static string toString(int val);
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
};

class Month:public TemporalScalar{
public:
	Month():TemporalScalar(1999*12+11){}
	Month(int val):TemporalScalar(val){}
	Month(int year, int month):TemporalScalar(year*12+month-1){}
	virtual ~Month(){}
	virtual DATA_TYPE getType() const {return DT_MONTH;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Month());}
	virtual ConstantSP getValue() const {return ConstantSP(new Month(val_));}
	virtual string getString() const { return toString(val_);}
	static Month* parseMonth(const string& str);
	static string toString(int val);
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
};

class Time:public TemporalScalar{
public:
	Time(int val=0):TemporalScalar(val){}
	Time(int hour, int minute, int second, int milliSecond):TemporalScalar(((hour*60+minute)*60+second)*1000+milliSecond){}
	virtual ~Time(){}
	virtual DATA_TYPE getType() const {return DT_TIME;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Time());}
	virtual ConstantSP getValue() const {return ConstantSP(new Time(val_));}
	virtual string getString() const { return toString(val_);}
	virtual void validate();
	static Time* parseTime(const string& str);
	static string toString(int val);
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
};

class NanoTime:public Long{
public:
	NanoTime(long long val=0):Long(val){}
	NanoTime(int hour, int minute, int second, int nanoSecond):Long(((hour*60+minute)*60+second)*1000000000ll+ nanoSecond){}
	virtual ~NanoTime(){}
	virtual DATA_TYPE getType() const {return DT_NANOTIME;}
	virtual DATA_CATEGORY getCategory() const {return TEMPORAL;}
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
	virtual ConstantSP getInstance() const {return ConstantSP(new NanoTime());}
	virtual ConstantSP getValue() const {return ConstantSP(new NanoTime(val_));}
	virtual string getString() const { return toString(val_);}
	virtual void validate();
	static NanoTime* parseNanoTime(const string& str);
	static string toString(long long val);
};

class Timestamp:public Long{
public:
	Timestamp(long long val=0):Long(val){}
	Timestamp(int year, int month, int day,int hour, int minute, int second, int milliSecond);
	virtual ~Timestamp(){}
	virtual DATA_TYPE getType() const {return DT_TIMESTAMP;}
	virtual DATA_CATEGORY getCategory() const {return TEMPORAL;}
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
	virtual ConstantSP getInstance() const {return ConstantSP(new Timestamp());}
	virtual ConstantSP getValue() const {return ConstantSP(new Timestamp(val_));}
	virtual string getString() const { return toString(val_);}
	static Timestamp* parseTimestamp(const string& str);
	static string toString(long long val);
};

class NanoTimestamp:public Long{
public:
	NanoTimestamp(long long val=0):Long(val){}
	NanoTimestamp(int year, int month, int day,int hour, int minute, int second, int nanoSecond);
	virtual ~NanoTimestamp(){}
	virtual DATA_TYPE getType() const {return DT_NANOTIMESTAMP;}
	virtual DATA_CATEGORY getCategory() const {return TEMPORAL;}
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
	virtual ConstantSP getInstance() const {return ConstantSP(new NanoTimestamp());}
	virtual ConstantSP getValue() const {return ConstantSP(new NanoTimestamp(val_));}
	virtual string getString() const { return toString(val_);}
	static NanoTimestamp* parseNanoTimestamp(const string& str);
	static string toString(long long val);
};

class Minute:public TemporalScalar{
public:
	Minute(int val=0):TemporalScalar(val){}
	Minute(int hour, int minute):TemporalScalar(hour*60+minute){}
	virtual ~Minute(){}
	virtual DATA_TYPE getType() const {return DT_MINUTE;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Minute());}
	virtual ConstantSP getValue() const {return ConstantSP(new Minute(val_));}
	virtual string getString() const { return toString(val_);}
	virtual void validate();
	static Minute* parseMinute(const string& str);
	static string toString(int val);
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
};

class Second:public TemporalScalar{
public:
	Second(int val=0):TemporalScalar(val){}
	Second(int hour, int minute,int second):TemporalScalar((hour*60+minute)*60+second){}
	virtual ~Second(){}
	virtual DATA_TYPE getType() const {return DT_SECOND;}
	virtual ConstantSP getInstance() const {return ConstantSP(new Second());}
	virtual ConstantSP getValue() const {return ConstantSP(new Second(val_));}
	virtual string getString() const { return toString(val_);}
	virtual void validate();
	static Second* parseSecond(const string& str);
	static string toString(int val);
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
};

class DateTime:public TemporalScalar{
public:
	DateTime(int val=0):TemporalScalar(val){}
	DateTime(int year, int month, int day, int hour, int minute,int second);
	virtual ~DateTime(){}
	virtual DATA_TYPE getType() const {return DT_DATETIME;}
	virtual ConstantSP getInstance() const {return ConstantSP(new DateTime());}
	virtual ConstantSP getValue() const {return ConstantSP(new DateTime(val_));}
	virtual string getString() const { return toString(val_);}
	static DateTime* parseDateTime(const string& str);
	static string toString(int val);
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
};

class DateHour:public TemporalScalar{
public:
    DateHour(int val=0):TemporalScalar(val){}
    DateHour(int year, int month, int day, int hour);
    virtual ~DateHour(){}
    virtual DATA_TYPE getType() const {return DT_DATEHOUR;}
    virtual ConstantSP getInstance() const {return ConstantSP(new DateHour());}
    virtual ConstantSP getValue() const {return ConstantSP(new DateHour(val_));}
    virtual string getString() const { return toString(val_);}
    static DateHour* parseDateHour(const string& str);
    static string toString(int val);
	virtual ConstantSP castTemporal(DATA_TYPE expectType);
};

};
#endif /* SCALARIMP_H_ */
