#include<Windows.h>
#include<iostream>
#include<string.h>
#ifndef UNICODE
#define UNICODE
#endif

HKEY OpenRegistryKey(HKEY hRootKey, const wchar_t* strSubKey)
{
	HKEY hKey;
	LONG lError = RegOpenKeyEx(hRootKey, strSubKey, NULL, KEY_ALL_ACCESS, &hKey);
	if (ERROR_FILE_NOT_FOUND == lError)
	{
		//lError = RegCreateKeyEx(hRootKey, strSubKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	}
	if (lError != ERROR_SUCCESS)
	{
		std::cout << "Somethig is wrong. Cannot locate or open the key.";
		int i = GetLastError();
		return hKey;
	}
	return hKey;
}

void SetRegistryValues(HKEY hrootKey, LPCTSTR lpVal, LPCTSTR data)
{
	LONG nErr = RegSetValueEx(hrootKey, lpVal, NULL, REG_SZ, (LPBYTE)data, wcslen(data)*2 );
	if (nErr != ERROR_SUCCESS) 
	{
		std::cout << "Not able to set the value.";
		int i = GetLastError();
		return;
	}
	else {
		std::cout << "Value Added !";
	}
}

DWORD GetRegistryValue(HKEY hRootKey, LPCTSTR lpVal)
{
	DWORD data;
	DWORD dtype = REG_DWORD;
	DWORD dsize = sizeof(data);
	LONG lErr = RegQueryValueEx(hRootKey, lpVal, NULL, &dtype, (LPBYTE)& data, &dsize);

	if (ERROR_SUCCESS != lErr)
	{
		std::cout << "Could not obtain the Key Values";
	}
	return data;
}

int main() {

	HKEY hKey = OpenRegistryKey(HKEY_CURRENT_USER, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");

	//std::wstring keyname = "ProgramHello";
	//std::wstring value = "HEY THERE! WELCOME WELCOME :)";
	//LPCTSTR l1 = keyname.c_str();
	//LPCTSTR l2 = value.c_str();


	SetRegistryValues(hKey, L"ProgramHello", L"C:\\Users\\Harshini\\Desktop\\SpellSecurity\\MessageBox\\Debug\\MessageBox.exe");
	//SetRegistryValues(hKey, L"MyValue_2", 25);

	/*DWORD dMyValue1, dMyValue2;
	dMyValue1 = GetRegistryValue(hKey, L"MyValue_1");
	dMyValue2 = GetRegistryValue(hKey, L"MyValue_2");

	dMyValue1 += 5;
	dMyValue2 += 5;

	SetRegistryValues(hKey, L"MyValue_1", dMyValue1);
	SetRegistryValues(hKey, L"MyValue_2", dMyValue2);*/
	RegCloseKey(hKey);

	return 0;
}
