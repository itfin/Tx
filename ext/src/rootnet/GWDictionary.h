// Dictionary.h: interface for the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICTIONARY_H__D4AF5746_B0F3_11D5_9118_000102981438__INCLUDED_)
#define AFX_DICTIONARY_H__D4AF5746_B0F3_11D5_9118_000102981438__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <map>
#include <iostream>  
#include <algorithm>  
#include <vector>  
#include <string>  
 using namespace std; 
 namespace GWDPApi
{
class CGWDictionary 
{
public:
	CGWDictionary();
	virtual ~CGWDictionary();

public:
	//是否加载数据字典
	bool IsLoadDict(){return m_bLoadFlag;}
	//加载数据字典
	 bool LoadDictionary();
	 void Clear();
	 
	 //本函数检查文本行内容，去掉注释和空行
	 int checktxt(char* buf,int len);

	 //字符串转大写
	 void upperstr(char *p);

	 //用字典ID查询字典项类型
	 short GetDictTypeByID(int Id);

	 //用字典ID查询字典项名称
	 string GetDictNameByID(int Id);

	 //用字典名称查询字典项类型
	 short GetDictTypeByName(string Name);

	 //用字典名称查询字典项ID
	 short GetDictItemIDByName(string Name);

	 //获取字典项
	 string GetNextToken(char* string);

protected:

	//字典结构（字典ID，字典Name,字典类型）
	typedef std::map<short/*DictId*/, std::pair <string/*DictName*/,short/*DictType*/> >  MAP_ID2FIELD;
	MAP_ID2FIELD m_mapId2Field;

	//字典结构（字典名称，字典项）
	typedef std::map<string/*DictName*/, std::pair <short/*DictIID*/, short/*DictType*/> >  MAP_FNAME2FIELD;
	MAP_FNAME2FIELD m_mapFName2Field;

	//是否加载字典
	bool m_bLoadFlag;
};
};
#endif // !defined(AFX_DICTIONARY_H__D4AF5746_B0F3_11D5_9118_000102981438__INCLUDED_)
