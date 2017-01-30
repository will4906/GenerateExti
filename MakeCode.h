// MakeCode.h: interface for the CMakeCode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAKECODE_H__D48D9699_0E5C_409B_BDF8_D22DA33A05FE__INCLUDED_)
#define AFX_MAKECODE_H__D48D9699_0E5C_409B_BDF8_D22DA33A05FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include "DataNode.h"

class CMakeCode  
{
public:
	CMakeCode(CList<CDataNode, CDataNode> *dataList);
	virtual ~CMakeCode();

private:
	CList<CDataNode, CDataNode> *dataList;

public:
	BOOL GeneratingCode();
private:
	BOOL NewFileExtiH();
	BOOL NewFileExtiC();
	void WriteFileDescription(CStdioFile &stFile, CString strFile);
};

#endif // !defined(AFX_MAKECODE_H__D48D9699_0E5C_409B_BDF8_D22DA33A05FE__INCLUDED_)
