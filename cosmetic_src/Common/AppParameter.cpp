///////////////////////////////////////////////////////////
//  AppParameter.cpp
//  Implementation of the Class AppParameter
//  Created on:      05-ÎåÔÂ-2009 11:59:47
//  Original author: Tim Kuo
///////////////////////////////////////////////////////////

#include "AppParameter.h"
#include "common.h"

AppParameter::AppParameter(){
	m_appStyle = STYLE_CLEAN;
	m_fontName = "SimSun";
	m_fontSize = 9;
	m_lastDir = "./";
}



AppParameter::~AppParameter(){

}





string& AppParameter::getAppStyle(){

	return m_appStyle;
}


string& AppParameter::getFontName(){

	return m_fontName;
}


short AppParameter::getFontSize(){

	return m_fontSize;
}


string& AppParameter::getLastDir(){

	return m_lastDir;
}


void AppParameter::setAppStyle(string& newVal){

	m_appStyle = newVal;
}


void AppParameter::setFontName(string& newVal){

	m_fontName = newVal;
}


void AppParameter::setFontSize(short newVal){

	m_fontSize = newVal;
}


void AppParameter::setLastDir(string& newVal){

	m_lastDir = newVal;
	DBHEX("set last dir:", m_lastDir);
}