#include "StdAfx.h"
#include "SolFileParser.h"

CSolFileParser::CSolFileParser(const char* szLineComment, CFileInfo* pFileInfo, 
							   DWORD nMode, LPCTSTR lpLogFileName)
 : IFileParser(pFileInfo, nMode, lpLogFileName)
{
	m_sSingleLineComment = szLineComment;
}

void CSolFileParser::ParseLine(const CString& sLine, ParseState& state, bool& bHasCode, bool& bHasComments)
{
	bHasCode = false;
	bHasComments = false;

	int nCommentLen = m_sSingleLineComment.GetLength();
	int nLineLen = sLine.GetLength();

	if(nLineLen < nCommentLen)
	{
		bHasCode = true;
		return;
	}

	for(int i = 0; i < nCommentLen; i++)
	{
		if(m_sSingleLineComment.GetAt(i) != sLine.GetAt(i))
		{
			bHasCode = true;
			return;
		}
	}
	bHasComments = true;
}