///////////////////////////////////////////////////////////
//  AppParameter.h
//  Implementation of the Class AppParameter
//  Created on:      05-ÎåÔÂ-2009 11:59:46
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#if !defined(EA_86ADC6BA_ED76_416f_B102_838339A1F4ED__INCLUDED_)
#define EA_86ADC6BA_ED76_416f_B102_838339A1F4ED__INCLUDED_

#include <string>
using namespace std;

class AppParameter
{

public:
	AppParameter();
	virtual ~AppParameter();

	string& getAppStyle();
	string& getFontName();
	short getFontSize();
	string& getLastDir();
	void setAppStyle(string& newVal);
	void setFontName(string& newVal);
	void setFontSize(short newVal);
	void setLastDir(string& newVal);

private:
	string m_appStyle;
	string m_fontName;
	short m_fontSize;
	string m_lastDir;

};
#endif // !defined(EA_86ADC6BA_ED76_416f_B102_838339A1F4ED__INCLUDED_)
