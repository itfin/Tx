#ifndef __KDENCODECLI_H__
#define __KDENCODECLI_H__

/*************************************
Version : 1.1.0.1
*************************************/

#define KDCOMPLEX_ENCODE 6

#ifdef _WIN32
	#define DLL_EXPORT __declspec(dllexport)
#else
	#define DLL_EXPORT __attribute__((visibility("default")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

	//DLL_EXPORT int PasswordCheck_SW(unsigned char *pSrcData, int nSrcDataLen,
	//	int nEncode_Level, void *pKey, int nKeyLen,
	//	void *pCustID, int nCustIDLen,
	//	unsigned char *pSWPassword, int nSWPasswordLen);

	DLL_EXPORT int KDEncode(int nEncode_Level,
		unsigned char *pSrcData, int nSrcDataLen,
		unsigned char *pDestData, int nDestDataBufLen,
		void *pKey, int nKeyLen);

	DLL_EXPORT int KDReEncode(unsigned char *pSrcData, int nSrcDataLen, 
		unsigned char *pDestData, int nDestDataBufLen, 
		int nOldEncode_Level, void *pOldKey, int nOldKeyLen, 
		int nNewEncode_Level, void *pNewKey, int nNewKeyLen);
#ifdef __cplusplus
}
#endif

#endif
