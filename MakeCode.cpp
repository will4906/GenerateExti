// MakeCode.cpp: implementation of the CMakeCode class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Exti.h"
#include "MakeCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMakeCode::CMakeCode(CList<CDataNode, CDataNode> *dataList)
{
	this->dataList = dataList;
}

CMakeCode::~CMakeCode()
{

}

BOOL CMakeCode::GeneratingCode()
{
	NewFileExtiH();
	NewFileExtiC();
	
	return TRUE;
}

BOOL CMakeCode::NewFileExtiH()
{
	BOOL flag = TRUE;
	
	CStdioFile stFile;
	flag = stFile.Open("Exti.h",CFile::modeCreate|CFile::modeReadWrite);

	WriteFileDescription(stFile, "Exti.h");

	stFile.WriteString("#ifndef _EXTI_H_\n");
	stFile.WriteString("#define _EXTI_H_	\n");
	stFile.WriteString("\n");
	stFile.WriteString("#include \"stm32f10x.h\"\n");
	stFile.WriteString("\n");
	stFile.WriteString("\n");
	stFile.WriteString("\n");
	stFile.WriteString("void InitExtiCon(void);	\n");
	stFile.WriteString("\n");
	stFile.WriteString("#endif\n");
	stFile.WriteString("\n");
	stFile.WriteString("\n");
	stFile.WriteString("\n");
	stFile.WriteString("\n");
	stFile.Close();
	return flag;
}
BOOL CMakeCode::NewFileExtiC()
{
	BOOL flag = TRUE;
	CStdioFile stFile;
	flag = stFile.Open("Exti.c",CFile::modeCreate|CFile::modeReadWrite);
	
	WriteFileDescription(stFile, "Exti.c");
	
	stFile.WriteString("#include \"Exti.h\"\n");
	stFile.WriteString("\n");
	stFile.WriteString("/*********************************************************************\n");
	stFile.WriteString("* Static Function Declaration\n");
	stFile.WriteString("**********************************************************************/\n");
	stFile.WriteString("static void InitExti(void);\n");
	stFile.WriteString("static void InitNvic(void);\n");
	stFile.WriteString("static void InitGpio(void);\n");
	stFile.WriteString("\n");
	stFile.WriteString("/*********************************************************************\n");
	stFile.WriteString("* Function: Initialize all Exti config\n");
	stFile.WriteString("* Param: 		void\n");
	stFile.WriteString("* Return: 	void\n");
	stFile.WriteString("**********************************************************************/\n");
	stFile.WriteString("void InitExtiCon(void)\n");
	stFile.WriteString("{\n");
	stFile.WriteString("	InitGpio();\n");
	stFile.WriteString("	InitExti();\n");
	stFile.WriteString("	InitNvic();\n");
	stFile.WriteString("}\n");
	stFile.WriteString("\n");
	stFile.WriteString("/*********************************************************************\n");
	stFile.WriteString("* Function: Initialize the Gpio config\n");
	stFile.WriteString("* Param: 		void\n");
	stFile.WriteString("* Return: 	void\n");
	stFile.WriteString("**********************************************************************/\n");
	stFile.WriteString("static void InitGpio(void)\n");
	stFile.WriteString("{\n");
	stFile.WriteString("	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);\n");
	stFile.WriteString("	\n");

	CDataNode dataNode;
	int i;
	for (i = 0; i < dataList->GetCount(); i ++)
	{
		dataNode = dataList->GetAt(dataList->FindIndex(i));
		CString strGroup = dataNode.GetPinGroup();
		int pin = dataNode.GetPin();
		CString strPin;
		strPin.Format("%d", pin);
		stFile.WriteString("	GPIO_EXTILineConfig(GPIO_PortSourceGPIO" + strGroup + ", GPIO_PinSource" + strPin + ");\n");
	}
	
	stFile.WriteString("}\n");
	stFile.WriteString("\n");
	stFile.WriteString("/*********************************************************************\n");
	stFile.WriteString("* Function: Initialize the exti config\n");
	stFile.WriteString("* Param: 		void\n");
	stFile.WriteString("* Return: 	void\n");
	stFile.WriteString("**********************************************************************/\n");
	stFile.WriteString("static void InitExti(void)\n");
	stFile.WriteString("{\n");
	stFile.WriteString("	EXTI_InitTypeDef EXTI_InitStructure;\n");
	stFile.WriteString("	\n");

	for (i = 0; i < dataList->GetCount(); i ++)
	{
		dataNode = dataList->GetAt(dataList->FindIndex(i));
		int pin = dataNode.GetPin();
		CString strPin;
		strPin.Format("%d", pin);
		stFile.WriteString("	EXTI_InitStructure.EXTI_Line=EXTI_Line" + strPin + ";\n");
		stFile.WriteString("	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	\n");
		int trigger = dataNode.GetTrigger();
		CString strTri;
		switch (trigger)
		{
		case RISING:
			strTri = "Rising";
			break;
		case FALLING:
			strTri = "Falling";
			break;
		case RISING_FALLING:
			strTri = "Rising_Falling";
			break;
		default:
			return FALSE;
			break;
		}
		stFile.WriteString("	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_" + strTri + ";\n");
		stFile.WriteString("	EXTI_InitStructure.EXTI_LineCmd = ENABLE;\n");
		stFile.WriteString("	EXTI_Init(&EXTI_InitStructure);\n");
	}

	stFile.WriteString("}\n");
	stFile.WriteString("\n");
	stFile.WriteString("/*********************************************************************\n");
	stFile.WriteString("* Function: Initialize the Nvic config\n");
	stFile.WriteString("* Param: 		void\n");
	stFile.WriteString("* Return: 	void\n");
	stFile.WriteString("**********************************************************************/\n");
	stFile.WriteString("static void InitNvic(void)\n");
	stFile.WriteString("{\n");
	stFile.WriteString("	NVIC_InitTypeDef NVIC_InitStructure;\n");
	stFile.WriteString("	\n");

	for (i = 0; i < dataList->GetCount(); i ++)
	{
		dataNode = dataList->GetAt(dataList->FindIndex(i));
		int pin = dataNode.GetPin();
		CString strPin;
		if (pin >= 0 && pin <= 4)
		{
			strPin.Format("%d", pin);
		}
		else if (pin >= 5 && pin <= 9)
		{
			strPin = "9_5";
		}
		else
		{
			strPin = "15_10";
		}
		stFile.WriteString("	NVIC_InitStructure.NVIC_IRQChannel = EXTI" + strPin + "_IRQn;\n");
		int pre = dataNode.GetPrePri();
		CString strPre;
		strPre.Format("%d", pre);
		stFile.WriteString("	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = " + strPre + ";\n");
		int sub = dataNode.GetSubPri();
		CString strSub;
		strSub.Format("%d", sub);
		stFile.WriteString("	NVIC_InitStructure.NVIC_IRQChannelSubPriority = " + strSub + ";\n");
		stFile.WriteString("	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;\n");
		stFile.WriteString("	NVIC_Init(&NVIC_InitStructure);\n");
	}
	stFile.WriteString("}\n");
	stFile.WriteString("\n");

	CArray<int, int> fnArr;
	CArray<int, int> tfArr;
	CArray<int, int> zfArr;
	for (i = 0; i < dataList->GetCount(); i ++)
	{
		dataNode = dataList->GetAt(dataList->FindIndex(i));
		int pin = dataNode.GetPin();
		CString strPin;
		if (pin >= 0 && pin <= 4)
		{
			int j;
			BOOL hasPin = FALSE;
			for (j = 0; j < zfArr.GetSize(); j ++)
			{
				if (pin == zfArr.GetAt(j))
				{
					hasPin = TRUE;
					break;
				}
			}
			if (hasPin == FALSE)
			{
				strPin.Format("%d", pin);
				stFile.WriteString("/*********************************************************************\n");
				stFile.WriteString("* Function: The interrupt handler function of the exti" + strPin + "\n");
				stFile.WriteString("* Param: 		void\n");
				stFile.WriteString("* Return: 	void\n");
				stFile.WriteString("**********************************************************************/\n");
				stFile.WriteString("void EXTI" + strPin + "_IRQHandler(void)\n");
				stFile.WriteString("{\n");
				stFile.WriteString("	if (EXTI_GetITStatus(EXTI_Line" + strPin + ") == SET)\n");
				stFile.WriteString("	{\n");
				stFile.WriteString("		//Add Code Here\n");
				stFile.WriteString("		\n");
				stFile.WriteString("		EXTI_ClearITPendingBit(EXTI_Line" + strPin + ");\n");
				stFile.WriteString("	}\n");
				stFile.WriteString("}\n");
				stFile.WriteString("\n");
				zfArr.Add(pin);
			}
		}
		else if (pin >= 5 && pin <= 9)
		{
			fnArr.Add(pin);
		}
		else
		{
			tfArr.Add(pin);
		}
	}

	if (fnArr.GetSize() > 0)
	{
		stFile.WriteString("/*********************************************************************\n");//EXTI9_5_IRQHandler
		stFile.WriteString("* Function: The interrupt handler function of the exti 5~9\n");
		stFile.WriteString("* Param: 		void\n");
		stFile.WriteString("* Return: 	void\n");
		stFile.WriteString("**********************************************************************/\n");
		stFile.WriteString("void EXTI9_5_IRQHandler(void)\n");
		stFile.WriteString("{\n");
		for (i = 0; i < fnArr.GetSize(); i ++)
		{
			CString strPin;
			int pin = fnArr.GetAt(i);
			strPin.Format("%d", pin);
			
			stFile.WriteString("	if (EXTI_GetITStatus(EXTI_Line" + strPin + ") == SET)\n");
			stFile.WriteString("	{\n");
			stFile.WriteString("		//Add Code Here\n");
			stFile.WriteString("	\n");
			stFile.WriteString("		EXTI_ClearITPendingBit(EXTI_Line" + strPin + ");\n");
			stFile.WriteString("	}\n");
		}
		stFile.WriteString("}\n");
		stFile.WriteString("\n");
	}
	if (tfArr.GetSize() > 0)
	{
		stFile.WriteString("/*********************************************************************\n");//EXTI15_10_IRQHandler
		stFile.WriteString("* Function: The interrupt handler function of the exti 10~15\n");
		stFile.WriteString("* Param: 		void\n");
		stFile.WriteString("* Return: 	void\n");
		stFile.WriteString("**********************************************************************/\n");
		stFile.WriteString("void EXTI15_10_IRQHandler(void)\n");
		stFile.WriteString("{\n");
		for (i = 0; i < tfArr.GetSize(); i ++)
		{
			CString strPin;
			int pin = fnArr.GetAt(i);
			strPin.Format("%d", pin);
			
			stFile.WriteString("	if (EXTI_GetITStatus(EXTI_Line" + strPin + ") == SET)\n");
			stFile.WriteString("	{\n");
			stFile.WriteString("		//Add Code Here\n");
			stFile.WriteString("	\n");
			stFile.WriteString("		EXTI_ClearITPendingBit(EXTI_Line" + strPin + ");\n");
			stFile.WriteString("	}\n");
		}
		stFile.WriteString("}\n");
		stFile.WriteString("\n");
	}
	stFile.WriteString(" \n");
	stFile.WriteString(" \n");
	stFile.WriteString(" \n");
	stFile.Close();
	return flag;
}

void CMakeCode::WriteFileDescription(CStdioFile &stFile, CString strFile)
{
	CTime time;  
	CString strTime;
	time=CTime::GetCurrentTime();//获得当前时间  
	strTime=time.Format("%Y/%m/%d");//将时间转化为字符串 

	stFile.WriteString("/*************************************************************************************\n");
	stFile.WriteString("* FileName: " + strFile + "\n");
	stFile.WriteString("* Author:		will4906\n");
	stFile.WriteString("* Email:		553105821@qq.com\n");
	stFile.WriteString("* Date:			" + strTime + "\n");
	stFile.WriteString("* Apache license:\n");
	stFile.WriteString("	Copyright 2017 will4906\n");
	stFile.WriteString("\n");
	stFile.WriteString("	Licensed under the Apache License, Version 2.0 (the \"License\");\n");
	stFile.WriteString("	you may not use this file except in compliance with the License.\n");
	stFile.WriteString("	You may obtain a copy of the License at\n");
	stFile.WriteString("\n");
	stFile.WriteString("		http://www.apache.org/licenses/LICENSE-2.0\n");
	stFile.WriteString("\n");
	stFile.WriteString("	Unless required by applicable law or agreed to in writing, software\n");
	stFile.WriteString("	distributed under the License is distributed on an \"AS IS\" BASIS,\n");
	stFile.WriteString("	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
	stFile.WriteString("	See the License for the specific language governing permissions and\n");
	stFile.WriteString("	limitations under the License.\n");
	stFile.WriteString("**************************************************************************************/\n");
}
