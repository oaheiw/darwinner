#include "SearchBox.h"

SearchBox::SearchBox(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_regExpPatternMap[0] = QRegExp::RegExp;
	m_regExpPatternMap[1] = QRegExp::Wildcard;
	m_regExpPatternMap[2] = QRegExp::FixedString;
	m_keyword.clear();
	m_pattern = 0;
	m_column = -1;
	m_searchIgnoreCase = true;
	m_sortIgnoreCase = true;

	m_sortCaseSensitivity = m_sortIgnoreCase ? Qt::CaseInsensitive : Qt::CaseSensitive;
	m_syntax = QRegExp::PatternSyntax(m_regExpPatternMap[m_pattern]);
	m_searchCaseSensitivity = m_searchIgnoreCase ? Qt::CaseInsensitive : Qt::CaseSensitive;
	m_searchRegExp = QRegExp(m_keyword, m_searchCaseSensitivity, m_syntax);
}

SearchBox::~SearchBox()
{

}

void SearchBox::keywordChange(QString keyword)
{
	m_keyword = keyword;
	m_searchRegExp.setPattern(m_keyword);
	emit regExpChanged(m_searchRegExp);
}

void SearchBox::searchPatternChange(int pattern)	
{
	m_pattern = pattern;
	m_syntax = QRegExp::PatternSyntax(m_regExpPatternMap[m_pattern]);
	m_searchRegExp.setPatternSyntax(m_syntax);
	emit regExpChanged(m_searchRegExp);
}

void SearchBox::searchCaseChange(bool bCase)
{
	m_searchIgnoreCase = bCase;
	m_searchCaseSensitivity = m_searchIgnoreCase ? Qt::CaseInsensitive : Qt::CaseSensitive;
	m_searchRegExp.setCaseSensitivity(m_searchCaseSensitivity);
	emit regExpChanged(m_searchRegExp);
}

void SearchBox::searchItemChange(int item)
{
	m_column = item - 1;//this is for select all column
	emit columnChanged(m_column);
}

void SearchBox::sortCaseChange(bool bCase)
{
	m_sortIgnoreCase = bCase;
	m_sortCaseSensitivity = m_sortIgnoreCase ? Qt::CaseInsensitive : Qt::CaseSensitive;
	emit sortChanged(m_sortCaseSensitivity);
}

