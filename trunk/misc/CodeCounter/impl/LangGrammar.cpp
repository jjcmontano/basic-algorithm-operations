#include "stdafx.h"
#include "LangGrammar.h"
#include "SingleLangGrammar.h"
#include "MultiLangGrammar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int GetLength(const LG_STRING& str)
{
#if defined(STRING_USE_STL)
	return str.length();
#else
	return str.GetLength();
#endif
}

char GetAt(const LG_STRING& str, int nIndex)
{
#if defined(STRING_USE_STL)
	return str.at(nIndex);
#else
	return str.GetAt(nIndex);
#endif
}

CSingleLineComment::CSingleLineComment(LPCTSTR lpszCommentStr, int nColumn)
{
	if(lpszCommentStr != NULL)
	{
		m_szTag = lpszCommentStr;
	}
	m_nStartCol = nColumn;
}

CPair::CPair()
{
}
CPair::CPair(LPCTSTR lpszStart, LPCTSTR lpszEnd) : m_szStart(lpszStart), m_szEnd(lpszEnd)
{
}

BOOL ILangGrammar::IsStartsWith(const CString& sSrc, const LG_STRING& sPrefix, int nBeginIndex)
{
	int nPrefixLen = GetLength(sPrefix);
	if( (nPrefixLen <= 0) || ((nBeginIndex + nPrefixLen) > sSrc.GetLength()) )
	{
		return FALSE;
	}
	for(int i = 0; i < nPrefixLen; i++)
	{
		if(GetAt(sPrefix, i) != sSrc.GetAt(nBeginIndex + i))
		{
			return FALSE;
		}
	}
	return TRUE;
}

BOOL ILangGrammar::IsSingleComment(const CSingleLineComment& sComment, const CString& sLine, int nBeginIndex)
{
	if(sComment.m_szTag.IsEmpty())
	{
		return FALSE;
	}
	//SOL
	if(sComment.m_nStartCol == START_COLUMN_SOL && nBeginIndex != 0)
	{
		return FALSE;
	}
	
	//TODO: concern about the case "singleComment.m_nStartCol > 0"
	if(IsStartsWith(sLine, sComment.m_szTag, nBeginIndex))
	{
		return TRUE;
	}
	return FALSE;
}


CLangGrammarBuilder::CLangGrammarBuilder(int type /* = LG_TYPE_SINGLE */)
 : m_pSingleLangGrammar(NULL), m_pMultiLangGrammar(NULL)
{
	if(type == LG_TYPE_MULTI)
	{
		m_pMultiLangGrammar = new CMultiLangGrammar();
	}
	else
	{
		m_pSingleLangGrammar = new CSingleLangGrammar();
	}
}

ILangGrammar* CLangGrammarBuilder::GetResult()
{
	if(m_pSingleLangGrammar != NULL)
	{
		return m_pSingleLangGrammar;
	}
	else
	{
		return m_pMultiLangGrammar;
	}
}

void CLangGrammarBuilder::AddSingleComment(const char* lpszCommentStr, int nColumn /* = START_COLUMN_ANY */)
{
	if(m_pSingleLangGrammar != NULL)
	{
		if(GetLength(m_pSingleLangGrammar->m_singleComment.m_szTag) <= 0)
		{
			m_pSingleLangGrammar->m_singleComment.m_szTag = lpszCommentStr;
			m_pSingleLangGrammar->m_singleComment.m_nStartCol = nColumn;
			return;
		}
		//Change to multi
		delete m_pSingleLangGrammar;
		m_pSingleLangGrammar = NULL;
	}
	CSingleLineComment sComment(lpszCommentStr, nColumn);
	m_pMultiLangGrammar->m_singleCommentArray.Add(sComment);
}

void CLangGrammarBuilder::AddMultiComment(const char* lpszStart, const char* lpszEnd)
{
	if(m_pSingleLangGrammar != NULL)
	{
		if(GetLength(m_pSingleLangGrammar->m_multiComment.m_szStart) <= 0)
		{
			m_pSingleLangGrammar->m_multiComment.m_szStart = lpszStart;
			m_pSingleLangGrammar->m_multiComment.m_szEnd = lpszEnd;
			return;
		}
		//Change to multi
		delete m_pSingleLangGrammar;
		m_pSingleLangGrammar = NULL;
	}
	CMultiLineComment mComment(lpszStart, lpszEnd);
	m_pMultiLangGrammar->m_multiCommentArray.Add(mComment);
}

void CLangGrammarBuilder::AddStringMark(const char* lpszStart, const char* lpszEnd)
{
	if(m_pSingleLangGrammar != NULL)
	{
		if(GetLength(m_pSingleLangGrammar->m_stringMark.m_szStart) <= 0)
		{
			m_pSingleLangGrammar->m_stringMark.m_szStart = lpszStart;
			m_pSingleLangGrammar->m_stringMark.m_szEnd = lpszEnd;
			return;
		}
		//Change to multi
		delete m_pSingleLangGrammar;
		m_pSingleLangGrammar = NULL;
	}
	CPair stringMark(lpszStart, lpszEnd);
	m_pMultiLangGrammar->m_stringMarkArray.Add(stringMark);
}

void CLangGrammarBuilder::AddCharMark(const char* lpszStart, const char* lpszEnd)
{
	if(m_pSingleLangGrammar != NULL)
	{
		if(GetLength(m_pSingleLangGrammar->m_charMark.m_szStart) <= 0)
		{
			m_pSingleLangGrammar->m_charMark.m_szStart = lpszStart;
			m_pSingleLangGrammar->m_charMark.m_szEnd = lpszEnd;
			return;
		}
		//Change to multi
		delete m_pSingleLangGrammar;
		m_pSingleLangGrammar = NULL;
	}
	CPair charMark(lpszStart, lpszEnd);
	m_pMultiLangGrammar->m_charMarkArray.Add(charMark);
}

void CLangGrammarBuilder::AddEscapeStr(const char* lpszEscapeStr)
{
	if(m_pSingleLangGrammar != NULL)
	{
		if(GetLength(m_pSingleLangGrammar->m_escapeStr) <= 0)
		{
			m_pSingleLangGrammar->m_escapeStr = lpszEscapeStr;
			return;
		}
		//Change to multi
		delete m_pSingleLangGrammar;
		m_pSingleLangGrammar = NULL;
	}
	m_pMultiLangGrammar->m_escapeStrArray.Add(lpszEscapeStr);
}