#include<afx.h>
#define LOGLEVELDEBUG 1
#define LOGLEVELINFO 2
#define LOGLEVELWARN 3
#define LOGLEVELERROR 4
 
#define LOGSAVEDAYS 10				//////��־��������
//////////////////////////////////////////////////////////////////
#pragma once
 
class LOG
{
public:
 
	//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
	static CString CreatLogFolder();
 
	////////��ȡ��־�ļ���
	static CString GetLogFileName();
 
	//////��ȡ��ǰʱ��
	static CString GetNowTime();
 
	////����־д��log�ļ�
	static BOOL WriteLog(CString m_strLogText);
	////������־
	//static BOOL D(CString m_strLogText, ...);
	////��Ϣ��־
	//static BOOL I(CString m_strLogText, ...);
	////������־
	//static BOOL W(CString m_strLogText, ...);
	////������־
	//static BOOL E(CString m_strLogText, ...);
 
	//ɾ��������־�ļ�
	static void DeleteLog();
};