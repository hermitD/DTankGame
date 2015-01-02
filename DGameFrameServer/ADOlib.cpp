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
* 功能 ：连接数据库
* _ConnectionPtr& pConnection：连接对象
* CString&        strIP      ：连接的服务器ID
* CString&        strDatabase：连接的数据库名称
* CString&        strUserName：连接数据库的用户名
* CString&        strPassword：连接数据库的密码
* 返回值：执行成功用TRUE，反之为FALSE
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
* 功能 ：使用 _CommandPtr对象 执行 sql语句
* _long&   lAffected ：传出参数，获取执行完sql语句影响的函数
* CString&        strSql             ：执行的sql语句
* 返回值：执行成功用TRUE，反之为FALSE
*****************************************************************/
BOOL CADOlib::CommandExeSql(CString& strSql)
{
	bool ret=false;
	long lAffected=0;
	try
	{

		// 1. 添加一个指向Command对象的指针，并初始化相关信息
		_CommandPtr pCommand;
		pCommand.CreateInstance(__uuidof(Command));   // 创建一个Command实例
		pCommand->ActiveConnection = m_pConnection;   // 指定数据库连接对象
		pCommand->CommandText      = (_bstr_t)strSql; // 指定需要执行的SQL语句

		// 2. 执行SQL语句，返回记录集
		m_pRecordset = pCommand->Execute( &m_varRecordsAffected, NULL, adCmdText );
		if ( (long)m_varRecordsAffected!=-1 )
		{
			lAffected = (long)m_varRecordsAffected;
		}
		// 3. 释放pCommand
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
* 功能 ：获取记录集中的数据
* _RecordsetPtr&      pRecordset：执行sql语句返回的记录集
* vector<TABLE_INFO>& vecTables ：传出参数，获取记录集中的数据
* 返回值：执行成功用TRUE，反之为FALSE
*****************************************************************/
BOOL  CADOlib::GetRecordsets(vector<TABLE_INFO>& vecTables)
{
	try
	{
		// 1. 得到记录集的字段集合，并获取集合中字段的数量
		Fields* pFields = nullptr; // 字段集合指针
		long    lCount;            // 字段数量
		if( !SUCCEEDED(m_pRecordset->get_Fields(&pFields)) )  return FALSE;
		pFields->get_Count(&lCount);

		// 2. 获取每一列名称（字段名）
		for (long i=0; i<lCount; i++)
		{
			BSTR       bstrColName = nullptr;
			TABLE_INFO stcInfo    ;
			pFields->Item[i]->get_Name(&bstrColName);
			stcInfo.strColName = bstrColName;
			vecTables.push_back(stcInfo);
		}

		// 3. 释放字段集合
		pFields->Release();
		pFields = nullptr;

		// 4. 循环获取记录集中每一条数据
		while ( !m_pRecordset->adoEOF && lCount )
		{
			for (long i=0; i<lCount; i++)
			{      
				CString    strCol = vecTables[i].strColName;                      // 字段名
				_variant_t var    = m_pRecordset->GetCollect( strCol.GetBuffer() ); // 通过字段名获取值
				CString    csItem = (LPCTSTR)_bstr_t(var);                        // 将值转换为字符串
				if( var.vt!=VT_NULL )  vecTables[i].vecstrItemName.push_back(csItem);
			}
			// 指向下一条数据
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
* 功能 ：执行添加 删除 修改 sql语句
* long&   lAffected ：传出参数，获取执行完sql语句影响的函数
* LPCTSTR pstrFormat：格式化sql语句字符串
* ...               ：格式化字符串中第一个%后的参数，后面依此类推
* ...
* 返回值：执行成功用TRUE，反之为FALSE
*****************************************************************/
BOOL CADOlib::ExecModTableSql(long& lAffected, LPCTSTR pstrFormat, ...)
{
	BOOL bRet = FALSE;
	try
	{
		// 1. 将变长参数格式化为查询语句
		CString strSQL('\0',MAX_PATH);
		va_list arglist;
		va_start( arglist, pstrFormat );
		bRet  = _vsnwprintf_s_l( strSQL.GetBuffer(), MAX_PATH, MAX_PATH, pstrFormat, NULL, arglist);
		va_end( arglist );

		// 2. 执行SQL语句，返回记录集
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
* 功能 ：执行查询sql语句
* vector<TABLE_INFO>& vecTables ：传出参数，获取查询返回的记录集
* LPCTSTR             pstrFormat：格式化sql语句字符串
* ...                           ：格式化字符串中第一个%后的参数
* ...
* 返回值：执行成功用TRUE，反之为FALSE
*****************************************************************/
BOOL CADOlib::ExecSelTableSql(vector<TABLE_INFO>& vecTables, LPCTSTR pstrFormat, ...)
{
	BOOL bRet = FALSE;
	try
	{
		// 1. 将变长参数格式化为查询语句
		CString strSQL('\0',MAX_PATH);
		va_list arglist;
		va_start( arglist, pstrFormat );
		bRet = _vsnwprintf_s_l( strSQL.GetBuffer(), MAX_PATH, MAX_PATH, pstrFormat, NULL, arglist);
		va_end( arglist );

		// 2. 执行SQL语句，返回记录集
		_RecordsetPtr pRecordset = NULL;
		_variant_t    varRecordsAffected;
		bRet = CommandExeSql(strSQL);

		// 3. 执行 查询语句 返回记录集
		if ( bRet && pRecordset && (long)varRecordsAffected==-1 )
		{
			GetRecordsets(vecTables);
			pRecordset->Close();
		}
	}
	catch(_com_error e)
	{	
		// 显示错误信息
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