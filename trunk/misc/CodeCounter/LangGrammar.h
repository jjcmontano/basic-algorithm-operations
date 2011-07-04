#ifndef _LANG_GRAMMAR_H_
#define _LANG_GRAMMAR_H_


#if _MSC_VER > 1000
#pragma once
#endif

#include "TinyVector.h"

#define START_COLUMN_ANY	(-1)	//ANY -- Any Column of Line
#define START_COLUMN_SOL	(0)		//SOL -- Start of Line


#if defined(STRING_USE_STL)
#include <string>
#define LG_STRING	std::string
#else
#define LG_STRING	CString
#endif


int GetLength(const LG_STRING& str);
char GetAt(const LG_STRING& str, int nIndex);

class CSingleLineComment
{
public:
	CSingleLineComment(const char* lpszCommentStr = NULL, int nColumn = START_COLUMN_ANY);
public:
	LG_STRING m_szTag;
	int m_nStartCol;
};

class CPair
{
public:
	CPair();
	CPair(const char* lpszStart, const char* lpszEnd);
public:
	LG_STRING m_szStart;
	LG_STRING m_szEnd;
};

typedef CPair CMultiLineComment;

class ILangGrammar
{
public:
	virtual ~ILangGrammar() {};
	virtual	CSingleLineComment& GetSingleLineComment(int nIndex = 0) = 0;
	virtual BOOL IsSingleLineComment(const CString& sLine, int nBeginIndex = 0) = 0;

	virtual LG_STRING& GetEscapeStr(int nIndex = 0) = 0;
	virtual int  IndexOfEscStr(const CString& sLine, int nBeginIndex = 0) = 0;
	
	virtual CMultiLineComment& GetMultiLineComment(int nIndex = 0) = 0;
	virtual int  GetMultiLineCommentStartIndex(const CString& sLine, int nBeginIndex = 0) = 0;
	virtual BOOL IsMultiLineCommentEnd(int iIndexOfMultiComment, const CString& sLine, int nBeginIndex = 0) = 0;
	
	virtual CPair& GetStringMark(int nIndex = 0) = 0;
	virtual int  GetStringStartIndex(const CString& sLine, int nBeginIndex = 0) = 0;
	virtual BOOL IsStringEnd(int iStrIndex, const CString& sLine, int nBeginIndex = 0) = 0;
	
	virtual CPair& GetCharMark(int iCharIndex = 0) = 0;
	virtual int  GetCharStartIndex(const CString& sLine, int nBeginIndex = 0) = 0;
	virtual BOOL IsCharEnd(int iStrIndex, const CString& sLine, int nBeginIndex = 0) = 0;

	static int  GetStartIndex(const CTinyVector<CPair>& tinyVector, const CString& sLine, int nBeginIndex = 0);
	static BOOL IsEnd(const CTinyVector<CPair>& tinyVector, int iIndex, const CString& sLine, int nBeginIndex = 0);
	static BOOL IsStartsWith(const CString& sSrc, const LG_STRING& sPrefix, int nBeginIndex = 0);
	static BOOL IsSingleComment(const CSingleLineComment& sComment, const CString& sLine, int nBeginIndex = 0);
};

class CSingleLangGrammar : public ILangGrammar
{
public:
	CSingleLangGrammar();
	~CSingleLangGrammar();
	
	CSingleLineComment& GetSingleLineComment(int nIndex = 0);
	BOOL IsSingleLineComment(const CString& sLine, int nBeginIndex = 0);

	LG_STRING& GetEscapeStr(int nIndex = 0);
	int  IndexOfEscStr(const CString& sLine, int nBeginIndex = 0);
	
	CMultiLineComment& GetMultiLineComment(int nIndex = 0);
	int  GetMultiLineCommentStartIndex(const CString& sLine, int nBeginIndex = 0);
	BOOL IsMultiLineCommentEnd(int iIndexOfMultiComment, const CString& sLine, int nBeginIndex = 0);
	
	CPair& GetStringMark(int nIndex = 0);
	int  GetStringStartIndex(const CString& sLine, int nBeginIndex = 0);
	BOOL IsStringEnd(int iStrIndex, const CString& sLine, int nBeginIndex = 0);
	
	CPair& GetCharMark(int nIndex = 0);
	int  GetCharStartIndex(const CString& sLine, int nBeginIndex = 0);
	BOOL IsCharEnd(int iStrIndex, const CString& sLine, int nBeginIndex = 0);
public:
	CSingleLineComment m_singleComment;
	CMultiLineComment  m_multiComment;
	CPair m_stringMark;
	CPair m_charMark;
	LG_STRING m_escapeStr;
};

class CMultiLangGrammar : public ILangGrammar
{
public:
	CMultiLangGrammar();
	~CMultiLangGrammar();
	
	CSingleLineComment& GetSingleLineComment(int nIndex = 0);
	BOOL IsSingleLineComment(const CString& sLine, int nBeginIndex = 0);

	LG_STRING& GetEscapeStr(int nIndex = 0);
	int  IndexOfEscStr(const CString& sLine, int nBeginIndex = 0);
	
	CMultiLineComment& GetMultiLineComment(int nIndex = 0);
	int  GetMultiLineCommentStartIndex(const CString& sLine, int nBeginIndex = 0);
	BOOL IsMultiLineCommentEnd(int iIndexOfMultiComment, const CString& sLine, int nBeginIndex = 0);
	
	CPair& GetStringMark(int nIndex = 0);
	int  GetStringStartIndex(const CString& sLine, int nBeginIndex = 0);
	BOOL IsStringEnd(int iStrIndex, const CString& sLine, int nBeginIndex = 0);
	
	CPair& GetCharMark(int nIndex = 0);
	int  GetCharStartIndex(const CString& sLine, int nBeginIndex = 0);
	BOOL IsCharEnd(int iStrIndex, const CString& sLine, int nBeginIndex = 0);
public:
	CTinyVector<CSingleLineComment> m_singleCommentArray;
	CTinyVector<CMultiLineComment> m_multiCommentArray;
	CTinyVector<CPair> m_stringMarkArray;	// eg. "string"
	CTinyVector<CPair> m_charMarkArray;		// eg. 'A'
	CTinyVector<LG_STRING> m_escapeStrArray;	
};

#define LG_TYPE_SINGLE		0
#define LG_TYPE_MULTI		1

class CLangGrammarBuilder
{
public:
	CLangGrammarBuilder(int type = LG_TYPE_SINGLE);
	ILangGrammar* GetResult();
	void AddSingleComment(const char* lpszCommentStr, int nColumn = START_COLUMN_ANY);
	void AddMultiComment(const char* lpszStart, const char* lpszEnd);
	void AddStringMark(const char* lpszStart, const char* lpszEnd);
	void AddCharMark(const char* lpszStart, const char* lpszEnd);
	void AddEscapeStr(const char* lpszEscapeStr);
protected:
	CSingleLangGrammar* m_pSingleLangGrammar;
	CMultiLangGrammar*  m_pMultiLangGrammar;
};

#endif // _LANG_GRAMMAR_H_