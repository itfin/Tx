#ifndef __JGDFDAPI_H__
#define __JGDFDAPI_H__

#if defined(WIN32) || defined(WIN64) || defined(_WINDOWS)
#ifdef COM_JGDFDAPI_EXPORT
#define COM_JGDFDAPI __declspec(dllexport)
#else
#define COM_JGDFDAPI __declspec(dllimport)
#endif
#else
#define COM_JGDFDAPI __attribute((visibility("default")))
#endif

#include "JGDFDApi_DataDef.h"

#ifdef __cplusplus
extern "C" {
#endif
	/*
	* ��������dump�ļ�.�粻��Ҫ�ù��ܣ��ɲ�����.
	*/
	COM_JGDFDAPI void DFDAPI_CreateDumpFile();

	/*
	* ��ȡ�ӿڰ汾��Ϣ
	*/
	COM_JGDFDAPI const char* DFDAPI_GetVersion();


	/*
	* ��ʼ������.
	* return �ɹ���DFDAPI_ERR_SUCCESS ʧ�ܣ�DFDAPI_ERR_UNINITIALIZE.
	*/
	COM_JGDFDAPI int DFDAPI_Init();


	/*
	* ���û������� һ��������������һ�Σ����Բ�����ʹ��Ĭ��ֵ��Ĭ��ֵ�ο�DFDAPI_EnvSet
	* @param[in] eSetEnv ��������������
	* @param[in] unEnvValue ������������ֵ
	* return �ɹ���DFDAPI_ERR_SUCCESS δ֪������DFDAPI_ERR_INVALID_PARAMS
	*/
	int COM_JGDFDAPI DFDAPI_SetEnv(const DFDAPI_SET_ENVIRONMENT &eSetEnv, const unsigned int &unEnvValue);


	/*
	* �򿪷�������
	* @param[in] pConnectSet ���Ӳ������ã��ڵ����ڼ��ͨ���ص��յ����ӵ�¼��ȡ���������Ϣ
	* ����Ͽ����ӻὫ���������pErrCode
	* @param[in] pErrCode ������ 
	* return �ɹ�����һ��ʵ����ʶ ���򷵻�NULL
	*/
	VHANDLE COM_JGDFDAPI DFDAPI_OpenConnect(DFDAPI_OPEN_CONNECT_SET *&pConnectSet, DFDAPI_ERR_CODE *pErrCode);


	/*
	* ͨ������򿪷�������[��ʱδʵ��]
	* @param[in] pConnectSet ���Ӳ������ã��ڵ����ڼ��ͨ���ص��յ����ӵ�¼��ȡ���������Ϣ
	* ����Ͽ����ӻὫ���������pErrCode
	* @param[in] pProxySet ��������
	* @param[in] pErrCode ������
	* return �ɹ�����һ��ʵ����ʶ
	*/
	VHANDLE COM_JGDFDAPI DFDAPI_OpenConnectByProxy(DFDAPI_OPEN_CONNECT_SET *&pConnectSet, DFDAPI_PROXY_SET *&pProxySet, DFDAPI_ERR_CODE *pErrCode);
		
	
	/*
	* ��ȡָ���г������
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy����ʵ����ʶ
	* @param[in] szMarket��ʽΪ��market-level-source(SHF-1-0)
	* @param[in|out] pCodeTable ���������
	* @param[in|out] pItems ���������
	* return DFDAPI_ERR_SUCCESS:�ɹ� ����:ʧ��
	*/	
	int COM_JGDFDAPI DFDAPI_GetCodeTable(VHANDLE vHandle, const char* szMarket, DFDAPI_CODEINFO* &pCodeTable, unsigned int &nItems);

	
	/*
	* ��ȡ��Ȩ������Ϣ
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy����ʵ����ʶ
	* @param[in|out] pBasicInfo ����
	* @param[in|out] pItems ����
	* return DFDAPI_ERR_SUCCESS:�ɹ� ����:ʧ��
	*/
	int COM_JGDFDAPI DFDAPI_GetOptionBasicInfoData(VHANDLE vHandle, const char* szMarket, DFDAPI_BASICINFO_OPTION* &pBasicInfo, unsigned int &nItems);

	/*
	* �ͷ��ڴ�
	*/
	void COM_JGDFDAPI DFDAPI_FreeArr(void *pArr);
	
	
	/*
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy����ʵ����ʶ
	* @param[in] szSubScriptions ���Ĵ��� nSubStyleΪȫ�г����Ŀɿ�
	* @param[in] szSubScriptions �������� 
	* return 0:���Ľӿڵ��óɹ� ����:ʧ��
	*/
	int COM_JGDFDAPI DFDAPI_SetSubscription(VHANDLE vHandle, const SUBSCRIPTION_STYLE& eSubStyle, const int& nItems, const DFDAPI_CODEINFO* pSubScriptions);
		
	
	/*
	* ��ȡETF�����嵥�ļ�.
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy����ʵ����ʶ
	* return 0:�ӿڵ��óɹ� ����:ʧ��
	*/
	int COM_JGDFDAPI DFDAPI_ReqETFListData(VHANDLE vHandle, DFDAPI_ETFLISTFILE** &ppETFListData, unsigned int* pItems);

	/*
	* �ͷ��ڴ�.
	* return 0:�ӿڵ��óɹ� ����:ʧ��
	*/
	int COM_JGDFDAPI DFDAPI_FreeETFListData(DFDAPI_ETFLISTFILE** ppETFListData, const unsigned int& nItems);

	/*
	* ��ȡ����ETF�嵥��Ϣ.��ȡ�ɹ�֮����Ҫ����DFDAPI_FreeArr()���ͷ�pBaseETF��pBaseETFComp.
	*/
	int COM_JGDFDAPI DFDAPI_GetSHETFInfo(VHANDLE vHandle, DFDAPI_SHBaseETF* &pBaseETF, unsigned int &nETFItems,
		DFDAPI_SHBaseETFComponent* &pBaseETFComp, unsigned int &nCompItems);

	/*
	* ��ȡ����ETF�嵥��Ϣ.��ȡ�ɹ�֮����Ҫ����DFDAPI_FreeArr()���ͷ�pBaseETF��pBaseETFComp.
	*/
	int COM_JGDFDAPI DFDAPI_GetSZETFInfo(VHANDLE vHandle, DFDAPI_SZBaseETF* &pBaseETF, unsigned int &nETFItems,
		DFDAPI_SZBaseETFComponent* &pBaseETFComp, unsigned int &nCompItems);

	/*
	* �ر�����,���˳��������.
	*/
	void COM_JGDFDAPI DFDAPI_Exit();

	/*
	* ��ȡ�۹ɻ�����Ϣ,�����DFDAPI_FreeArr�ͷ���Դ.
	* @param[in] vHandle DFDAPI_OpenConnect|DFDAPI_OpenConnectByProxy����ʵ����ʶ
	* @param[in|out] pBasicInfo ����
	* @param[in|out] pItems ����
	* return DFDAPI_ERR_SUCCESS:�ɹ� ����:ʧ��
	*/
	int COM_JGDFDAPI DFDAPI_GetHKexBasicInfoData(VHANDLE vHandle, DFDAPI_BASICINFO_HKEX* &pBasicInfo, unsigned int &nItems);
#ifdef __cplusplus
}
#endif // __cplusplus

#endif