// Original: client/ProjectG/GenericHTTPClient.h (JP 983 exe)
#ifndef PG_JP983_CLIENT_PROJECTG_GENERICHTTPCLIENT_H
#define PG_JP983_CLIENT_PROJECTG_GENERICHTTPCLIENT_H

#include <windows.h>
#include <wininet.h>
#include <vector>
#include "defines.h"
#include "padding.h"

#define __SIZE_HTTP_ARGUMENT_NAME 256
#define __SIZE_HTTP_ARGUMENT_VALUE 65536
#define __SIZE_HTTP_BUFFER 100000

// WinInet HTTP client (vtable 0xd29158, one slot: the scalar deleting
// destructor). Layout as in KR; the offsets are confirmed by the JP code
// (constructor 0x7d6fe0, accessors 0x7d5bb0-0x7d5bd0).
class GenericHTTPClient {
	LAYOUT_CHECK_FRIEND;
public:
	struct __GENERIC_HTTP_ARGUMENT {
		char szName[__SIZE_HTTP_ARGUMENT_NAME]; // 0x0
		char szValue[__SIZE_HTTP_ARGUMENT_VALUE]; // 0x100
		DWORD dwType; // 0x10100
	};

	enum enumRequestMethod {
		RequestUnknown = 0,
		RequestGetMethod = 1,
		RequestPostMethod = 2,
		RequestPostMethodMultiPartsFormData = 3
	};

	enum enumTypePostArgument {
		TypeUnknown = 0,
		TypeNormal = 1,
		TypeBinary = 2
	};

	GenericHTTPClient();
	virtual ~GenericHTTPClient();

	static enumRequestMethod GetMethod(int nMethod);
	static enumTypePostArgument GetPostArgumentType(int nType);

	BOOL Connect(LPCSTR szAddress, LPCSTR szAgent, unsigned short nPort, LPCSTR szUserAccount, LPCSTR szPassword);
	BOOL Close();
	VOID InitilizePostArguments();
	VOID AddPostArguments(LPCSTR szName, DWORD nValue);
	VOID AddPostArguments(LPCSTR szName, LPCSTR szValue, BOOL bBinary);
	BOOL Request(LPCSTR szURL, int nMethod, LPCSTR szAgent);
	BOOL RequestOfURI(LPCSTR szURI, int nMethod);
	BOOL Response(PBYTE pHeaderBuffer, DWORD dwHeaderBufferLength, PBYTE pBuffer, DWORD dwBufferLength, DWORD &dwResultSize);
	LPCSTR QueryHTTPResponse();
	LPCSTR QueryHTTPResponseHeader();
	DWORD GetLastError();
	LPCSTR GetContentType(LPCSTR szName);
	VOID ParseURL(LPCSTR szURL, LPSTR szProtocol, LPSTR szAddress, DWORD &dwPort, LPSTR szURI);

protected:
	BOOL RequestGet(LPCSTR szURI);
	BOOL RequestPost(LPCSTR szURI);
	BOOL RequestPostMultiPartsFormData(LPCSTR szURI);
	DWORD ResponseOfBytes(PBYTE pBuffer, DWORD dwSize);
	DWORD GetPostArguments(LPSTR szArguments, DWORD dwLength);
	DWORD AllocMultiPartsFormData(PBYTE &pInBuffer, LPCSTR szBoundary);
	VOID FreeMultiPartsFormData(PBYTE &pBuffer);
	DWORD GetMultiPartsFormDataLength();

	std::vector<__GENERIC_HTTP_ARGUMENT> _vArguments; // 0x4
	char _szHTTPResponseHTML[__SIZE_HTTP_BUFFER]; // 0x14
	char _szHTTPResponseHeader[__SIZE_HTTP_BUFFER]; // 0x186B4
	HINTERNET _hHTTPOpen; // 0x30D54
	HINTERNET _hHTTPConnection; // 0x30D58
	HINTERNET _hHTTPRequest; // 0x30D5C
	DWORD _dwError; // 0x30D60
	UNKNOWN(0x30D64, 0x30D6C);
	DWORD _dwRequestFlags; // 0x30D6C, INTERNET_FLAG_SECURE for port 443, ORed into HttpOpenRequest's flags
};

CHECK_SIZE(GenericHTTPClient::__GENERIC_HTTP_ARGUMENT, 0x10104);
BEGIN_LAYOUT_CHECK(GenericHTTPClient)
	CHECK_FIELD(GenericHTTPClient, _vArguments, 0x4);
	CHECK_FIELD(GenericHTTPClient, _szHTTPResponseHTML, 0x14);
	CHECK_FIELD(GenericHTTPClient, _szHTTPResponseHeader, 0x186B4);
	CHECK_FIELD(GenericHTTPClient, _hHTTPOpen, 0x30D54);
	CHECK_FIELD(GenericHTTPClient, _hHTTPConnection, 0x30D58);
	CHECK_FIELD(GenericHTTPClient, _hHTTPRequest, 0x30D5C);
	CHECK_FIELD(GenericHTTPClient, _dwError, 0x30D60);
	CHECK_FIELD(GenericHTTPClient, _dwRequestFlags, 0x30D6C);
END_LAYOUT_CHECK

#endif // PG_JP983_CLIENT_PROJECTG_GENERICHTTPCLIENT_H
