#include "stdafx.h"
#include "LOG.h"
 
//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
CString LOG::CreatLogFolder()
{
	CString m_strFilePath;
	GetModuleFileName(NULL, m_strFilePath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	m_strFilePath.ReleaseBuffer();
	int m_iPosIndex = m_strFilePath.ReverseFind(L'\\');
	m_strFilePath = m_strFilePath.Left(m_iPosIndex) + L"\\Log";
	CFileFind m_FileFind;
	if (!m_FileFind.FindFile(m_strFilePath))
		CreateDirectory(m_strFilePath, NULL);
 
	return m_strFilePath;
}
 
 
//////获取日志文件名
CString LOG::GetLogFileName()
{
	CString m_strFileName;
	m_strFileName = CTime::GetCurrentTime().Format(L"%Y-%m-%d") + L".log";
	return m_strFileName;
}
 
//////获取当前时间
CString LOG::GetNowTime()
{
	SYSTEMTIME st;
	CString m_strTime;
	GetLocalTime(&st);
	m_strTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return m_strTime;
}
 
////将日志写进log文件
BOOL LOG::WriteLog(CString m_strLogText)
{
	try
	{
		//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
		CString m_sLogFolderPath = CreatLogFolder();
		//////获取日志文件名
		CString m_sLogFileName = GetLogFileName();
		/////日志文件路径
		CString m_sLogFilePath = m_sLogFolderPath + L"\\" + m_sLogFileName;
		////文件操作
		CStdioFile m_SFile;
		if (!m_SFile.Open(m_sLogFilePath, CFile::modeReadWrite))
		{
			m_SFile.Open(m_sLogFilePath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText);
		}
 
		/////获取当前时间
		CString m_strTime = GetNowTime();
		//////日志 时间   ++   等级  ++ 内容
		CString m_sErrorMessage;
		////////日志---时间
		m_sErrorMessage = L"[" + m_strTime + L"] ";
		////////日志----等级
		/*switch (LOGLEVEL)
		{
		case LOGLEVELDEBUG:
			m_sErrorMessage += L"[ DEBUG ] ";
			break;
		case LOGLEVELINFO:
			m_sErrorMessage += L"[ INFO  ] ";
			break;
		case LOGLEVELWARN:
			m_sErrorMessage += L"[ WARN ] ";
			break;
		case LOGLEVELERROR:
			m_sErrorMessage += L"[ ERROR ] ";
			break;
		}*/
		////////日志----内容
		m_sErrorMessage += m_strLogText + L"\r\n";
		//////写日志文件
		m_SFile.SeekToEnd();
	

		int n = m_sErrorMessage.GetLength();
		int len = WideCharToMultiByte(CP_ACP,0,m_sErrorMessage,m_sErrorMessage.GetLength(),NULL,0,NULL,NULL);
		char * m_szMessage = new char[len+1]; //以字节为单位
		WideCharToMultiByte(CP_ACP,0,m_sErrorMessage,m_sErrorMessage.GetLength(),m_szMessage,len,NULL,NULL);
		m_SFile.Write(m_szMessage, strlen(m_szMessage));
		m_SFile.Close();
	}
	catch (CFileException fileException)
	{
		return false;
	}
	return true;
}
 
//删除过期日志文件
void LOG::DeleteLog()
{
 
	//获取应用程序所在路径  创建log文件夹  获取log文件夹路径
	CString m_sLogFolderPath = CreatLogFolder();
	////日志文件路径
	CString strLogFile;
	strLogFile.Format(L"%s\\*.log", m_sLogFolderPath);
	CFileFind finder;
 
	BOOL bWorking = finder.FindFile(strLogFile);
 
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
 
		CTime currentTime = CTime::GetCurrentTime();
		CTime timeFile;
		finder.GetLastAccessTime(timeFile);
		CTimeSpan ts = currentTime - timeFile;
		int nSecond = (int)ts.GetTotalSeconds();
 
		if (nSecond > LOGSAVEDAYS * 24 * 60 * 60)//超时，过期
		{
			CString strFile;
			strFile.Format(L"%s\\%s", m_sLogFolderPath, finder.GetFileName());
			DeleteFile(strFile);
		}
	}
}