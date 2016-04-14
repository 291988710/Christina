//ImageConvert.cpp
/************************************************************************/
/*                       
	Created time: 2016/4/14
	Created author: llc
	Function: Image convertion function
*/
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
//Include file
//////////////////////////////////////////////////////////////////////////
#include "ImageConvert.h"

//////////////////////////////////////////////////////////////////////////
//Function implementation
//////////////////////////////////////////////////////////////////////////
IStream* initPng(LPTSTR res)
{
	HMODULE hInstance = ::GetModuleHandle(NULL);
	HRSRC hRsrc = ::FindResource(hInstance, res, "PNG");
	DWORD dwSize = ::SizeofResource(hInstance, hRsrc);
	LPBYTE lpRes = (LPBYTE)::LoadResource(hInstance, hRsrc);
	HGLOBAL hMem = ::GlobalAlloc(GMEM_FIXED, dwSize);
	LPBYTE pMem = (LPBYTE)::GlobalLock(hMem);
	memcpy(pMem, lpRes, dwSize);
	IStream* pStream = NULL;
	::CreateStreamOnHGlobal(hMem, FALSE, *pStream);
	return pStream;
}

void parsePng(CImage* pImg)
{
	unsigned char* pCol = 0;
	int iw = pImg->GetWidth();
	int ih = pImg->GetHeight();
	for (int y = 0; y < ih; y++)
	{
		for (int x = 0; x < iw; x++)
		{
			pCol = (unsigned char*)pImg->GetPixelAddress(x,y);
			unsigned char imgAlpha = pCol[3];
			if (imgAlpha < 255)
			{
				pCol[0] = ((pCol[0] * imgAlpha) + 127) / 255;
				pCol[1] = ((pCol[1] * imgAlpha) + 127) / 255;
				pCol[2] = ((pCol[2] * imgAlpha) + 127) / 255;
			}
		}
	}
}