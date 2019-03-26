/********************************************************************
*�� �ļ�����RegOperator.h
*�� �ļ���������ע���ĳ����������з�װ
*�� �����ˣ� RainLeaf, 2009��4��10��
*�� �汾�ţ�1.0
*�� �޸ļ�¼��
*********************************************************************/
#include <windows.h>
#include <assert.h>
#include <vector>

#ifndef REGOP_H
#define REGOP_H

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

class CRegOperator
{
private:
	HKEY m_hKey;													/* ���浱ǰ���������ľ��						*/

public:
	CRegOperator(HKEY hKey = HKEY_LOCAL_MACHINE);					/* ���캯����Ĭ�ϲ���Ϊ��HKEY_LOCAL_MACHINE		*/
	BOOL SetHKEY(const char* strKey);								/* ���õ�ǰ�����ĸ���							*/
	BOOL OpenKey(const char* lpSubKey, bool bX64 = false);			/* ��д����ʽ��ע���							*/
	void Close();													/* �رռ����									*/

	BOOL CreateKey(const char* lpSubKey);							/* ��������ʽ��ע���							*/
	BOOL DeleteKey(const char* lphKey, const char* lpSubKey);		/* ɾ����Ӧ���Ӽ����Ӽ�Ϊ�գ�					*/
	BOOL DeleteValue(const char* lpValueName);						/* ɾ���Ӽ�������Ӧ�ļ�ֵ						*/
	BOOL SaveKey(const char* lpFileName);							/* �ѵ�ǰ��ֵ���浽ָ���ļ�						*/
	BOOL RestoreKey(const char* lpFileName);						/* ��ָ��ע����ļ��лָ�						*/

	BOOL Read(const char* lpValueName, std::string& outVal);		/* ����REG_SZ���͵�ֵ							*/
	BOOL Read(const char* lpValueName, DWORD& dwVal);				/* ����DWORD���͵�ֵ							*/
	BOOL Read(const char* lpValueName, int& nVal);					/* ����INT���͵�ֵ								*/
	BOOL Write(const char* lpSubKey, const char* lpVal);			/* д��REG_SZ����ֵ								*/
	BOOL Write(const char* lpSubKey, DWORD dwVal);					/* д��DWORD����ֵ								*/
	BOOL Write(const char* lpSubKey, int nVal);						/* д��INT����ֵ								*/

	BOOL EnumSub(
		OUT std::vector<std::string>* subTreeNames = NULL,
		OUT std::vector<std::string>* subValueNames = NULL);		/* ö��											*/

	virtual ~CRegOperator();
};

#endif