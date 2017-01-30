// DataNode.h: interface for the CDataNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATANODE_H__3E743CF5_646E_40E2_92CF_75FEC8804AC0__INCLUDED_)
#define AFX_DATANODE_H__3E743CF5_646E_40E2_92CF_75FEC8804AC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum{
	RISING,
	FALLING,
	RISING_FALLING
};

class CDataNode  
{
public:
	CDataNode();
	virtual ~CDataNode();

private:
	CString strPinGroup;
	int nPin;
	int nTrigger;
	int nPrePri;
	int nSubPri;
	
public:
	void SetPinGroup(CString strPinGroup);
	CString GetPinGroup();
	void SetPin(int nPin);
	int GetPin();
	void SetTrigger(int nMode);
	int GetTrigger();
	void SetPrePri(int nPrePri);
	int GetPrePri();
	void SetSubPri(int nSubPri);
	int GetSubPri();
};

#endif // !defined(AFX_DATANODE_H__3E743CF5_646E_40E2_92CF_75FEC8804AC0__INCLUDED_)
