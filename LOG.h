#include<afx.h>
#define LOGLEVELDEBUG 1
#define LOGLEVELINFO 2
#define LOGLEVELWARN 3
#define LOGLEVELERROR 4
 
#define LOGSAVEDAYS 10				//////日志保存天数
//////////////////////////////////////////////////////////////////
#pragma once
 
class LOG
{
public:
 
	//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
	static CString CreatLogFolder();
 
	////////获取日志文件名
	static CString GetLogFileName();
 
	//////获取当前时间
	static CString GetNowTime();
 
	////将日志写进log文件
	static BOOL WriteLog(CString m_strLogText);
	////调试日志
	//static BOOL D(CString m_strLogText, ...);
	////信息日志
	//static BOOL I(CString m_strLogText, ...);
	////警告日志
	//static BOOL W(CString m_strLogText, ...);
	////错误日志
	//static BOOL E(CString m_strLogText, ...);
 
	//删除过期日志文件
	static void DeleteLog();
};