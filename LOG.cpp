#include "stdafx.h"
#include "LOG.h"
 
//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
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
 
 
//////��ȡ��־�ļ���
CString LOG::GetLogFileName()
{
	CString m_strFileName;
	m_strFileName = CTime::GetCurrentTime().Format(L"%Y-%m-%d") + L".log";
	return m_strFileName;
}
 
//////��ȡ��ǰʱ��
CString LOG::GetNowTime()
{
	SYSTEMTIME st;
	CString m_strTime;
	GetLocalTime(&st);
	m_strTime.Format(L"%04d-%02d-%02d %02d:%02d:%02d.%03d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	return m_strTime;
}
 
////����־д��log�ļ�
BOOL LOG::WriteLog(CString m_strLogText)
{
	try
	{
		//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
		CString m_sLogFolderPath = CreatLogFolder();
		//////��ȡ��־�ļ���
		CString m_sLogFileName = GetLogFileName();
		/////��־�ļ�·��
		CString m_sLogFilePath = m_sLogFolderPath + L"\\" + m_sLogFileName;
		////�ļ�����
		CStdioFile m_SFile;
		if (!m_SFile.Open(m_sLogFilePath, CFile::modeReadWrite))
		{
			m_SFile.Open(m_sLogFilePath, CFile::modeCreate | CFile::modeReadWrite | CFile::typeText);
		}
 
		/////��ȡ��ǰʱ��
		CString m_strTime = GetNowTime();
		//////��־ ʱ��   ++   �ȼ�  ++ ����
		CString m_sErrorMessage;
		////////��־---ʱ��
		m_sErrorMessage = L"[" + m_strTime + L"] ";
		////////��־----�ȼ�
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
		////////��־----����
		m_sErrorMessage += m_strLogText + L"\r\n";
		//////д��־�ļ�
		m_SFile.SeekToEnd();
	

		int n = m_sErrorMessage.GetLength();
		int len = WideCharToMultiByte(CP_ACP,0,m_sErrorMessage,m_sErrorMessage.GetLength(),NULL,0,NULL,NULL);
		char * m_szMessage = new char[len+1]; //���ֽ�Ϊ��λ
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
 
//ɾ��������־�ļ�
void LOG::DeleteLog()
{
 
	//��ȡӦ�ó�������·��  ����log�ļ���  ��ȡlog�ļ���·��
	CString m_sLogFolderPath = CreatLogFolder();
	////��־�ļ�·��
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
 
		if (nSecond > LOGSAVEDAYS * 24 * 60 * 60)//��ʱ������
		{
			CString strFile;
			strFile.Format(L"%s\\%s", m_sLogFolderPath, finder.GetFileName());
			DeleteFile(strFile);
		}
	}
}