/********************************************************************
*�� �ļ�����RegOperator.cpp
*�� �ļ���������ͷ�ļ��ж�����ĳ�Ա����������ʵ��
*�� �����ˣ� RainLeaf, 2009��4��10��
*�� �汾�ţ�1.0
*�� �޸ļ�¼��
*********************************************************************/
#include "RegOperator.h"

/*============================================================
* �� �� ����CRegOperator
* �Ρ�������HKEY [IN] : Ĭ����HKEY_LOCAL_MACHINE
* �������������캯������ʼ������
* �� �� ֵ����
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

CRegOperator::CRegOperator( HKEY hKey )
{
	m_hKey = hKey;
}

/*============================================================
* �� �� ����~CRegOperator
* �Ρ�������NULL [IN]
* ���������������������رմ򿪵�ע�����
* �� �� ֵ����
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

CRegOperator::~CRegOperator()
{
	Close();
}

/*============================================================
* �� �� ����Close
* �Ρ�������NULL [IN]
* �����������رմ򿪼��ľ��
* �� �� ֵ��void
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

void CRegOperator::Close()
{
	if( m_hKey )
	{
		/* ����ǿս��йر� */
		RegCloseKey( m_hKey );
		m_hKey = NULL;
	}	
}

/*============================================================
* �� �� ����SetHKEY
* �Ρ�������LPCTSTR [IN] : ����ֵ
* �����������ɴ���ĸ����ַ������õ�ǰ�����ĸ�����ֵ
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::SetHKEY(const char* strKey )
{
	assert( m_hKey );
	assert( strKey );

	/* ������бȽ� */
	if( 0 == strcmp(strKey, ("HKEY_CLASSES_ROOT")) )
	{
		m_hKey = HKEY_CLASSES_ROOT;
		return TRUE;
	}
	if( 0 == strcmp(strKey, ("HKEY_CURRENT_USER")) )
	{
		m_hKey = HKEY_CURRENT_USER;
		return TRUE;
	}
	if( 0 == strcmp(strKey, ("HKEY_LOCAL_MACHINE")) )
	{
		m_hKey = HKEY_LOCAL_MACHINE;
		return TRUE;
	}
	if( 0 == strcmp(strKey, ("HKEY_USERS")) )
	{
		m_hKey = HKEY_USERS;
		return TRUE;
	}
	if( 0 == strcmp(strKey, ("HKEY_PERFORMANCE_DATA")) )
	{
		m_hKey = HKEY_PERFORMANCE_DATA;
		return TRUE;
	}
	if( 0 == strcmp(strKey, ("HKEY_PERFORMANCE_TEXT")) )
	{
		m_hKey = HKEY_PERFORMANCE_TEXT;
		return TRUE;
	}
	if( 0 == strcmp(strKey, ("HKEY_PERFORMANCE_NLSTEXT")) )
	{
		m_hKey = HKEY_PERFORMANCE_NLSTEXT;
		return TRUE;
	}
	/* �Բ���ϵͳ�汾���в��� */
#if(WINVER >= 0x0400)
	if( 0 == strcmp(strKey, ("HKEY_CURRENT_CONFIG")) )
	{
		m_hKey = HKEY_CURRENT_CONFIG;
		return TRUE;
	}
	if( 0 == strcmp(strKey, ("HKEY_DYN_DATA")) )
	{
		m_hKey = HKEY_DYN_DATA;
		return TRUE;
	}
#endif

	return FALSE;
}

/*============================================================
* �� �� ����OpenKey
* �Ρ�������LPCTSTR [IN] : �Ӽ��ַ���
* ����������ͨ�������Ӽ����ַ�����ע�����Ӧ��λ��
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::OpenKey(const char* lpSubKey, bool bX64/*=false*/  )
{
	assert( m_hKey );
	assert( lpSubKey );

	DWORD opt = KEY_ALL_ACCESS;
	if (bX64)
		opt |= KEY_WOW64_64KEY;

	HKEY hKey;
	long lReturn = RegOpenKeyExA( m_hKey, lpSubKey, 0L, opt, &hKey );

	if( ERROR_SUCCESS == lReturn )
	{
		/* �ɹ����򽫴򿪵ľ������ */
		m_hKey = hKey;

		return TRUE;
	}
	/* ��ʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����CreateKey
* �Ρ�������LPCTSTR [IN] : �Ӽ��ַ���
* ����������ͨ�������Ӽ����ַ����򿪣������Ӽ������ߴ������������Ӽ�����Ӧ���Ӽ�
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::CreateKey(const char* lpSubKey )
{
	assert( m_hKey );
	assert( lpSubKey );

	HKEY hKey;
	DWORD dw;
	long lReturn = RegCreateKeyExA( m_hKey, lpSubKey, 0L, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dw);

	if( ERROR_SUCCESS == lReturn )
	{
		/* �ɹ��򿪻��ߴ����򽫾������ */
		m_hKey = hKey;

		return TRUE;
	}
	/* �򿪻��ߴ���ʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����DeleteKey
* �Ρ�������LPCTSTR LPCTSTR [IN] : ����ֵ �Ӽ�ֵ
* ����������ͨ������ĸ������Ӽ������Ӽ�ɾ��ɾ�������ܰ����Ӽ�
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::DeleteKey(const char* lphKey, const char* lpSubKey )
{
	assert( lphKey );
	assert( lpSubKey );
	assert( m_hKey );

	SetHKEY( lphKey );
	long lReturn = RegDeleteValueA( m_hKey, lpSubKey );

	if( ERROR_SUCCESS == lReturn )
	{
		/* ɾ���ɹ� */
		return TRUE;
	}
	/* ɾ��ʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����DeleteValue
* �Ρ�������LPCTSTR [IN] : Ҫɾ����ֵ������
* ����������ͨ�������ֵ���ƣ�ɾ����Ӧ�ļ�ֵ
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::DeleteValue(const char* lpValueName )
{
	assert( m_hKey );
	assert( lpValueName );

	long lReturn = RegDeleteValueA( m_hKey, lpValueName );

	if( ERROR_SUCCESS == lReturn )
	{
		/* ɾ���ɹ� */
		return TRUE;
	}
	/* ɾ��ʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����SaveKey
* �Ρ�������LPCTSTR [IN] : ��������ļ���
* ����������ͨ��������ļ����ƣ������Ӧ���Ӽ�
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::SaveKey(const char* lpFileName )
{
	assert( m_hKey );
	assert( lpFileName );

	long lReturn = RegSaveKeyA( m_hKey, lpFileName, NULL );

	if( ERROR_SUCCESS == lReturn )
	{
		/* ����ɹ� */
		return TRUE;
	}
	/* ����ʧ�� */	
	return FALSE;
}

/*============================================================
* �� �� ����RestoreKey
* �Ρ�������LPCTSTR [IN] : ���ָ����ļ���
* ����������ͨ���ļ����ƣ������е���ע�����
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::RestoreKey(const char* lpFileName )
{
	assert( m_hKey );
	assert( lpFileName );

	long lReturn = RegRestoreKeyA( m_hKey, lpFileName, 0);

	if( ERROR_SUCCESS == lReturn )
	{
		/* ����ɹ� */
		return TRUE;
	}
	/* ����ʧ�� */
	return FALSE;
}

/*============================================================
* �� �� ����Read
* �Ρ�������LPCTSTR CString [IN] : ��ֵ ��ȡֵ��key����Ϊ���ַ���ʱ��ȡĬ��ֵ
* ������������ָ��λ�õ�CString���͵�ֵ����
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::Read(const char* lpValueName, std::string& outVal )
{
	assert( m_hKey );
	assert( lpValueName );

	DWORD dwType = 0;
	DWORD dwSize = 2047;
	char szString[2048];
	memset( szString, 0, 2048 * sizeof(TCHAR) );

	long lReturn = RegQueryValueExA( m_hKey, lpValueName, NULL, &dwType, (BYTE *)szString, &dwSize );

	if( ERROR_SUCCESS == lReturn )
	{
		/* ��ѯ�ɹ� */
		outVal = szString;

		return TRUE;
	}
	/* ��ѯʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����Read
* �Ρ�������LPCTSTR DWORD [IN] : ��ֵ ��ȡֵ��key����Ϊ���ַ���ʱ��ȡĬ��ֵ
* ������������ָ��λ��DWORD���͵�ֵ����
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::Read(const char* lpValueName, DWORD& dwVal )
{
	assert( m_hKey );
	assert( lpValueName );

	DWORD dwType;
	DWORD dwSize = sizeof(DWORD);
	DWORD dwDest;
	long lReturn = RegQueryValueExA( m_hKey, lpValueName, NULL, &dwType, (BYTE *)&dwDest, &dwSize );

	if( ERROR_SUCCESS == lReturn )
	{
		/* ��ѯ�ɹ� */
		dwVal = dwDest;

		return TRUE;
	}
	DWORD err = GetLastError();
	/* ��ѯʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����Read
* �Ρ�������LPCTSTR int [IN] : ��ֵ ��ȡֵ��key����Ϊ���ַ���ʱ��ȡĬ��ֵ
* ������������ָ��λ��int���͵�ֵ����
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::Read( const char* lpValueName, int& nVal)
{
	assert( m_hKey );
	assert( lpValueName );

	DWORD dwType;
	DWORD dwSize=sizeof(DWORD);
	DWORD dwDest;
	long lReturn = RegQueryValueExA( m_hKey, lpValueName, NULL, &dwType, (BYTE *)&dwDest, &dwSize );

	if( ERROR_SUCCESS == lReturn )
	{
		/* ��ѯ�ɹ� */
		nVal=(int)dwDest;

		return TRUE;
	}

	return FALSE;	
}

/*============================================================
* �� �� ����Write
* �Ρ�������LPCTSTR LPCTSTR [IN] : ��ֵ ��ȡֵ��key����Ϊ���ַ���ʱ��ȡĬ��ֵ
* ������������LPCTSTR���͵�ֵд��ָ��λ��
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::Write(const char* lpValueName, const char* lpValue )
{
	assert( m_hKey );
	assert( lpValueName );
	assert( lpValue );	

	long lReturn = RegSetValueExA( m_hKey, lpValueName, 0L, REG_SZ, (const BYTE *) lpValue, (DWORD)(strlen(lpValue)*sizeof(lpValue[0])) +1 );

	if( ERROR_SUCCESS == lReturn )
	{
		/* �ɹ�д�� */
		return TRUE;
	}
	/* д��ʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����Write
* �Ρ�������LPCTSTR DWORD [IN] : ��ֵ д��ֵ��key����Ϊ���ַ���ʱ��ȡĬ��ֵ
* ������������DWORD���͵�ֵд��ָ��λ��
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::Write(const char* lpSubKey, DWORD dwVal )
{
	assert( m_hKey );
	assert( lpSubKey );

	long lReturn = RegSetValueExA( m_hKey, lpSubKey, 0L, REG_DWORD, (const BYTE *) &dwVal, sizeof(DWORD) );

	if( ERROR_SUCCESS == lReturn )
	{
		/* �ɹ�д�� */
		return TRUE;
	}
	/* д��ʧ�� */
	return FALSE;	
}

/*============================================================
* �� �� ����Write
* �Ρ�������LPCTSTR int [IN] : ��ֵ д��ֵ��key����Ϊ���ַ���ʱ��ȡĬ��ֵ
* ������������������д��ָ��λ��
* �� �� ֵ��BOOL
* �׳��쳣��
* �������ߣ�RainLeaf, 2009��4��10��
*============================================================*/

BOOL CRegOperator::Write(const char* lpSubKey, int nVal )
{
	assert( m_hKey );
	assert( lpSubKey );

	DWORD dwValue;
	dwValue=(DWORD)nVal;

	long lReturn = RegSetValueExA( m_hKey, lpSubKey, 0L, REG_DWORD, (const BYTE *) &dwValue, sizeof(DWORD) );

	if( ERROR_SUCCESS == lReturn )
	{
		/* �ɹ�д�� */
		return TRUE;
	}
	/* д��ʧ�� */
	return FALSE;	
}

BOOL CRegOperator::EnumSub(OUT std::vector<std::string>* subTreeNames/*=NULL*/, OUT std::vector<std::string>* subValueNames/*=NULL*/)
{
	char     achKey[MAX_KEY_LENGTH];   // buffer for subkey name  
	char	 achValue[MAX_VALUE_NAME];   
	DWORD	 cchValue = MAX_VALUE_NAME;
	DWORD    cbName;                   // size of name string   
	char     achClass[MAX_PATH] = ("");  // buffer for class name   
	DWORD    cchClassName = MAX_PATH;  // size of class string   
	DWORD    cSubKeys=0;               // number of subkeys
	DWORD    cValues;              // number of values for key   
	DWORD    cbMaxSubKey;              // longest subkey size   
	DWORD    cchMaxClass;              // longest class string
	DWORD    cchMaxValue;          // longest value name   
	DWORD    cbMaxValueData;       // longest value data   
	DWORD    cbSecurityDescriptor; // size of security descriptor   
	FILETIME ftLastWriteTime;      // last write time   

	DWORD i, retCode;   

	 

	// Get the class name and the value count.   
	retCode = RegQueryInfoKeyA(  
		m_hKey,                    // key handle   
		achClass,                // buffer for class name   
		&cchClassName,           // size of class string   
		NULL,                    // reserved   
		&cSubKeys,               // number of subkeys   
		&cbMaxSubKey,            // longest subkey size   
		&cchMaxClass,            // longest class string   
		&cValues,                // number of values for this key   
		&cchMaxValue,            // longest value name   
		&cbMaxValueData,         // longest value data   
		&cbSecurityDescriptor,   // security descriptor   
		&ftLastWriteTime);       // last write time   

	if (retCode != ERROR_SUCCESS)
		return FALSE;

	// Enumerate the subkeys, until RegEnumKeyEx fails.  
	if (cSubKeys && subTreeNames)  
	{  
		//printf( "\nNumber of subkeys: %d\n", cSubKeys);  

		for (i=0; i<cSubKeys; i++)   
		{   
			cbName = MAX_KEY_LENGTH;
			achKey[0] = '\0';
			retCode = RegEnumKeyExA(m_hKey, i,  
				achKey,   
				&cbName,   
				NULL,   
				NULL,   
				NULL,   
				&ftLastWriteTime);   
			if (retCode == ERROR_SUCCESS)   
			{  
				//_tprintf(TEXT("(%d) %s\n"), i+1, achKey);  
				subTreeNames->push_back(achKey);
			}  
		}  
	}   

	// Enumerate the key values.   
	if (cValues && subValueNames)
	{  
		printf( "\nNumber of values: %d\n", cValues);

		for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
		{
			cchValue = MAX_VALUE_NAME;
			achValue[0] = '\0';   
			retCode = RegEnumValueA(m_hKey, i,   
				achValue,   
				&cchValue,   
				NULL,   
				NULL,  
				NULL,  
				NULL);  

			if (retCode == ERROR_SUCCESS )   
			{   
				//_tprintf(TEXT("(%d) %s\n"), i+1, achValue);   
				subValueNames->push_back(achValue);
			}   
		}  
	}

	return TRUE;
}
