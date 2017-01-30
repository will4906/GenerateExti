// DataNode.cpp: implementation of the CDataNode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Exti.h"
#include "DataNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDataNode::CDataNode()
{
	this->nPin = 0;
	this->nPrePri = 0;
	this->nSubPri = 0;
	this->strPinGroup = "A";
}

CDataNode::~CDataNode()
{

}

void CDataNode::SetPinGroup(CString strPinGroup)
{
	this->strPinGroup = strPinGroup;
}
CString CDataNode::GetPinGroup()
{
	return strPinGroup;
}
void CDataNode::SetPin(int nPin)
{
	this->nPin = nPin;
}
int CDataNode::GetPin()
{
	return nPin;
}
void CDataNode::SetTrigger(int nTrigger)
{
	this->nTrigger = nTrigger;
}
int CDataNode::GetTrigger()
{
	return nTrigger;
}
void CDataNode::SetPrePri(int nPrePri)
{
	this->nPrePri = nPrePri;
}
int CDataNode::GetPrePri()
{
	return nPrePri;
}
void CDataNode::SetSubPri(int nSubPri)
{
	this->nSubPri = nSubPri;
}
int CDataNode::GetSubPri()
{
	return nSubPri;
}