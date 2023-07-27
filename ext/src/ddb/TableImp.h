/*
 * Table.h
 *
 *  Created on: Nov 3, 2012
 *      Author: dzhou
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <atomic>

#include "DolphinDB.h"

namespace dolphindb {

class BasicTable;

typedef SmartPointer<BasicTable> BasicTableSP;

class AbstractTable : public Table {
public:
	AbstractTable(const SmartPointer<vector<string>>& colNames);
	AbstractTable(const SmartPointer<vector<string>>& colNames, SmartPointer<unordered_map<string,int>> colMap);
	virtual ~AbstractTable(){}
	virtual ConstantSP getColumn(const string& name) const;
	virtual ConstantSP getColumn(const string& qualifier, const string& name) const;
	virtual ConstantSP getColumn(const string& name, const ConstantSP& rowFilter) const;
	virtual ConstantSP getColumn(const string& qualifier, const string& name, const ConstantSP& rowFilter) const;
	virtual ConstantSP getColumn(INDEX index, const ConstantSP& rowFilter) const;
	virtual ConstantSP getColumn(INDEX index) const = 0;
	virtual ConstantSP get(INDEX col, INDEX row) const = 0;
	virtual INDEX columns() const {return colNames_->size();}
	virtual const string& getColumnName(int index) const {return colNames_->at(index);}
	virtual const string& getColumnQualifier(int index) const {return name_;}
	virtual void setColumnName(int index, const string& name);
	virtual int getColumnIndex(const string& name) const;
	virtual bool contain(const string& name) const;
	virtual bool contain(const string& qualifier, const string& name) const;
	virtual ConstantSP getColumnLabel() const;
	virtual ConstantSP values() const;
	virtual ConstantSP keys() const { return getColumnLabel();}
	virtual void setName(const string& name){name_=name;}
	virtual const string& getName() const { return name_;}
	virtual bool isTemporary() const {return false;}
	virtual void setTemporary(bool temp){}
	virtual bool sizeable() const {return false;}
	virtual string getString(INDEX index) const;
	virtual string getString() const;
	virtual ConstantSP get(INDEX index) const { return getInternal(index);}
	virtual bool set(INDEX index, const ConstantSP& value);
	virtual ConstantSP get(const ConstantSP& index) const { return getInternal(index);}
	virtual ConstantSP getWindow(int colStart, int colLength, int rowStart, int rowLength) const {return getWindowInternal(colStart, colLength, rowStart, rowLength);}
	virtual ConstantSP getMember(const ConstantSP& key) const { return getMemberInternal(key);}
	virtual ConstantSP getInstance() const {return getInstance(0);}
	virtual ConstantSP getInstance(int size) const;
	virtual ConstantSP getValue() const;
	virtual ConstantSP getValue(INDEX capacity) const;
	virtual bool append(vector<ConstantSP>& values, INDEX& insertedRows, string& errMsg);
	virtual bool update(vector<ConstantSP>& values, const ConstantSP& indexSP, vector<string>& colNames, string& errMsg);
	virtual bool remove(const ConstantSP& indexSP, string& errMsg);
	virtual ConstantSP getSubTable(vector<int> indices) const = 0;
	virtual COMPRESS_METHOD getColumnCompressMethod(INDEX index);
	virtual void setColumnCompressMethods(const vector<COMPRESS_METHOD> &methods);

protected:
	ConstantSP getInternal(INDEX index) const;
	ConstantSP getInternal(const ConstantSP& index) const;
	ConstantSP getWindowInternal(int colStart, int colLength, int rowStart, int rowLength) const;
	ConstantSP getMemberInternal(const ConstantSP& key) const;

private:
	string getTableClassName() const;
	string getTableTypeName() const;

protected:
	SmartPointer<vector<string>> colNames_;
	SmartPointer<unordered_map<string,int>> colMap_;
	string name_;
	vector<COMPRESS_METHOD> colCompresses_;
};


class BasicTable: public AbstractTable{
public:
	BasicTable(const vector<ConstantSP>& cols, const vector<string>& colNames, const vector<int>& keys);
	BasicTable(const vector<ConstantSP>& cols, const vector<string>& colNames);
	virtual ~BasicTable();
	virtual bool isBasicTable() const {return true;}
	virtual ConstantSP getColumn(INDEX index) const;
	virtual ConstantSP get(INDEX col, INDEX row) const {return cols_[col]->get(row);}
	virtual DATA_TYPE getColumnType(const int index) const { return cols_[index]->getType();}
	virtual void setColumnName(int index, const string& name);
	virtual INDEX size() const {return size_;}
	virtual bool sizeable() const {return isReadOnly()==false;}
	virtual bool set(INDEX index, const ConstantSP& value);
	virtual ConstantSP get(INDEX index) const;
	virtual ConstantSP get(const ConstantSP& index) const;
	virtual ConstantSP getWindow(INDEX colStart, int colLength, INDEX rowStart, int rowLength) const;
	virtual ConstantSP getMember(const ConstantSP& key) const;
	virtual ConstantSP getInstance(int size) const;
	virtual ConstantSP getValue() const;
	virtual ConstantSP getValue(INDEX capacity) const;
	virtual bool append(vector<ConstantSP>& values, INDEX& insertedRows, string& errMsg);
	virtual bool update(vector<ConstantSP>& values, const ConstantSP& indexSP, vector<string>& colNames, string& errMsg);
	virtual bool remove(const ConstantSP& indexSP, string& errMsg);
	virtual long long getAllocatedMemory() const;
	virtual TABLE_TYPE getTableType() const {return BASICTBL;}
	virtual void drop(vector<int>& columns);
	bool join(vector<ConstantSP>& columns);
	bool clear();
	void updateSize();
	virtual ConstantSP getSubTable(vector<int> indices) const;

private:
	bool increaseCapacity(long long newCapacity, string& errMsg);
	void initData(const vector<ConstantSP>& cols, const vector<string>& colNames);
	//bool internalAppend(vector<ConstantSP>& values, string& errMsg);
	bool internalRemove(const ConstantSP& indexSP, string& errMsg);
	void internalDrop(vector<int>& columns);
	bool internalUpdate(vector<ConstantSP>& values, const ConstantSP& indexSP, vector<string>& colNames, string& errMsg);

private:
	vector<ConstantSP> cols_;
	//bool readOnly_;
	INDEX size_;
	INDEX capacity_;
};

};

#endif /* TABLE_H_ */
