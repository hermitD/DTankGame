#pragma once
#include "stdafx.h"
#include <string>



#include <vector>
using namespace std;

#import "C:\\Program Files\\Common Files\\System\\ado\\msado15.dll" no_namespace rename("EOF", "adoEOF")
class CADOlib
{
public:
	CADOlib(void);
	~CADOlib(void);
	typedef struct _TABLE_INFO
	{
		CString       strColName;     // ×Ö¶ÎÃû
		vector<CString>   vecstrItemName; // ÏîÃû³Æ
	}TABLE_INFO, *PTABLE_INFO;

	bool ConnectDataBase(
		CString&strip,
		CString&strDataBase,
		CString&strUserName,
		CString& strPassword);
	BOOL CommandExeSql( CString& strSql);
	BOOL GetRecordsets(vector<TABLE_INFO>& vecTables);
	BOOL SelectAName(CString strName);
	BOOL ExecModTableSql(long& lAffected, LPCTSTR pstrFormat, ...);
	BOOL ExecSelTableSql(vector<TABLE_INFO>& vecTables, LPCTSTR pstrFormat, ...);
	BOOL ExecSelTableSql2(CString strName);
private:
	_ConnectionPtr  m_pConnection;
	_RecordsetPtr   m_pRecordset;
	_variant_t      m_varRecordsAffected;

};

