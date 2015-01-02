#include "stdafx.h"
#include "ADOlib.h"


CADOlib::CADOlib(void)
{
	m_pConnection=NULL;
	CString user="doye";//user
	CString pwd="123" ;//password
	CString database="DoyeTank";//database name
	CString strip="192.168.200.133";


	CoInitialize(NULL);

	int ret =ConnectDataBase(strip,database,user,pwd);
	
}


CADOlib::~CADOlib(void)
{
	CoInitialize(NULL);
	m_pConnection=NULL;
}
/******************************************************
* ���� ���������ݿ�
* _ConnectionPtr& pConnection�����Ӷ���
* CString&        strIP      �����ӵķ�����ID
* CString&        strDatabase�����ӵ����ݿ�����
* CString&        strUserName���������ݿ���û���
* CString&        strPassword���������ݿ������
* ����ֵ��ִ�гɹ���TRUE����֮ΪFALSE
******************************************************/
bool CADOlib::ConnectDataBase(
	CString&strip,
	CString&strDataBase,
	CString&strUserName,
	CString& strPassword)

{

	try
	{
		if (m_pConnection&&m_pConnection->State==adStateOpen)
			m_pConnection->Close();
		m_pConnection.CreateInstance(L"ADODB.Connection");
		CString strFormatBuff;
		strFormatBuff.Format(L"Provider=SQLOLEDB;Server=%s;Database=%s;Uid=%s;Pwd=%s",
			strip,strDataBase,strUserName,strPassword);
		m_pConnection->Open(_bstr_t(strFormatBuff),_bstr_t(""),_bstr_t(""),adConnectUnspecified);

	}catch(_com_error e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}


/*****************************************************************
* ���� ��ʹ�� _CommandPtr���� ִ�� sql���
* _long&   lAffected ��������������ȡִ����sql���Ӱ��ĺ���
* CString&        strSql             ��ִ�е�sql���
* ����ֵ��ִ�гɹ���TRUE����֮ΪFALSE
*****************************************************************/
BOOL CADOlib::CommandExeSql(CString& strSql)
{
	bool ret=false;
	long lAffected=0;
	try
	{

		// 1. ���һ��ָ��Command�����ָ�룬����ʼ�������Ϣ
		_CommandPtr pCommand;
		pCommand.CreateInstance(__uuidof(Command));   // ����һ��Commandʵ��
		pCommand->ActiveConnection = m_pConnection;   // ָ�����ݿ����Ӷ���
		pCommand->CommandText      = (_bstr_t)strSql; // ָ����Ҫִ�е�SQL���

		// 2. ִ��SQL��䣬���ؼ�¼��
		m_pRecordset = pCommand->Execute( &m_varRecordsAffected, NULL, adCmdText );
		if ( (long)m_varRecordsAffected!=-1 )
		{
			lAffected = (long)m_varRecordsAffected;
		}
		// 3. �ͷ�pCommand
		pCommand.Release();
	}
	catch(_com_error e)
	{	
		AfxMessageBox(e.Description());
		return FALSE;
	}
	if(lAffected)
		goto exit0;
	ret=true;
exit0:
	return ret;
}


/*****************************************************************
* ���� ����ȡ��¼���е�����
* _RecordsetPtr&      pRecordset��ִ��sql��䷵�صļ�¼��
* vector<TABLE_INFO>& vecTables ��������������ȡ��¼���е�����
* ����ֵ��ִ�гɹ���TRUE����֮ΪFALSE
*****************************************************************/
BOOL  CADOlib::GetRecordsets(vector<TABLE_INFO>& vecTables)
{
	try
	{
		// 1. �õ���¼�����ֶμ��ϣ�����ȡ�������ֶε�����
		Fields* pFields = nullptr; // �ֶμ���ָ��
		long    lCount;            // �ֶ�����
		if( !SUCCEEDED(m_pRecordset->get_Fields(&pFields)) )  return FALSE;
		pFields->get_Count(&lCount);

		// 2. ��ȡÿһ�����ƣ��ֶ�����
		for (long i=0; i<lCount; i++)
		{
			BSTR       bstrColName = nullptr;
			TABLE_INFO stcInfo    ;
			pFields->Item[i]->get_Name(&bstrColName);
			stcInfo.strColName = bstrColName;
			vecTables.push_back(stcInfo);
		}

		// 3. �ͷ��ֶμ���
		pFields->Release();
		pFields = nullptr;

		// 4. ѭ����ȡ��¼����ÿһ������
		while ( !m_pRecordset->adoEOF && lCount )
		{
			for (long i=0; i<lCount; i++)
			{      
				CString    strCol = vecTables[i].strColName;                      // �ֶ���
				_variant_t var    = m_pRecordset->GetCollect( strCol.GetBuffer() ); // ͨ���ֶ�����ȡֵ
				CString    csItem = (LPCTSTR)_bstr_t(var);                        // ��ֵת��Ϊ�ַ���
				if( var.vt!=VT_NULL )  vecTables[i].vecstrItemName.push_back(csItem);
			}
			// ָ����һ������
			m_pRecordset->MoveNext();
		}
	}
	catch(_com_error e)
	{	
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return TRUE;
}

/*****************************************************************
* ���� ��ִ����� ɾ�� �޸� sql���
* long&   lAffected ��������������ȡִ����sql���Ӱ��ĺ���
* LPCTSTR pstrFormat����ʽ��sql����ַ���
* ...               ����ʽ���ַ����е�һ��%��Ĳ�����������������
* ...
* ����ֵ��ִ�гɹ���TRUE����֮ΪFALSE
*****************************************************************/
BOOL CADOlib::ExecModTableSql(long& lAffected, LPCTSTR pstrFormat, ...)
{
	BOOL bRet = FALSE;
	try
	{
		// 1. ���䳤������ʽ��Ϊ��ѯ���
		CString strSQL('\0',MAX_PATH);
		va_list arglist;
		va_start( arglist, pstrFormat );
		bRet  = _vsnwprintf_s_l( strSQL.GetBuffer(), MAX_PATH, MAX_PATH, pstrFormat, NULL, arglist);
		va_end( arglist );

		// 2. ִ��SQL��䣬���ؼ�¼��
		_RecordsetPtr pRecordset = NULL;
		_variant_t    varRecordsAffected;
		bRet = CommandExeSql(strSQL);
		if ( bRet && (long)varRecordsAffected!=-1 )
		{
			lAffected = (long)varRecordsAffected;
		}
	}
	catch(_com_error e)
	{	
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return bRet;
}
BOOL CADOlib::ExecSelTableSql2(CString strName)
{
	CString a("doye");
	CString b("moca");

	if (strName!=a && strName != b)
	{
		return FALSE;
	}
}

/*****************************************************************
* ���� ��ִ�в�ѯsql���
* vector<TABLE_INFO>& vecTables ��������������ȡ��ѯ���صļ�¼��
* LPCTSTR             pstrFormat����ʽ��sql����ַ���
* ...                           ����ʽ���ַ����е�һ��%��Ĳ���
* ...
* ����ֵ��ִ�гɹ���TRUE����֮ΪFALSE
*****************************************************************/
BOOL CADOlib::ExecSelTableSql(vector<TABLE_INFO>& vecTables, LPCTSTR pstrFormat, ...)
{
	BOOL bRet = FALSE;
	try
	{
		// 1. ���䳤������ʽ��Ϊ��ѯ���
		CString strSQL('\0',MAX_PATH);
		va_list arglist;
		va_start( arglist, pstrFormat );
		bRet = _vsnwprintf_s_l( strSQL.GetBuffer(), MAX_PATH, MAX_PATH, pstrFormat, NULL, arglist);
		va_end( arglist );

		// 2. ִ��SQL��䣬���ؼ�¼��
		_RecordsetPtr pRecordset = NULL;
		_variant_t    varRecordsAffected;
		bRet = CommandExeSql(strSQL);

		// 3. ִ�� ��ѯ��� ���ؼ�¼��
		if ( bRet && pRecordset && (long)varRecordsAffected==-1 )
		{
			GetRecordsets(vecTables);
			pRecordset->Close();
		}
	}
	catch(_com_error e)
	{	
		// ��ʾ������Ϣ
		AfxMessageBox(e.Description());
		return FALSE;
	}
	return bRet;
}



BOOL CADOlib::SelectAName(CString strName)
{
	
	vector<TABLE_INFO> vecTables;
	CString s;
	s.Format(_T("select * from users where name='%s'"),strName);
	ExecSelTableSql(vecTables, s);
	bool ret = ExecSelTableSql2(strName);
	/*if (vecTables[0].vecstrItemName.size()!=0)
		return TRUE;*/
	//if(vecTables.size()!= 0)
	//	return TRUE;
	//else
	//{
	//	return FALSE;
	//}
	return ret;
}