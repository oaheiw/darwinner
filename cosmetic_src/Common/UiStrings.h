#ifndef UISTRINGS_H
#define UISTRINGS_H

#define LOCAL8BITSTR(str) QString::fromLocal8Bit(str)

#define CHINESE_VERSION
#ifdef CHINESE_VERSION
#include "ChineseStrings.h"
#else
#include "EnglishStrings.h"
#endif

#endif // UISTRINGS_H
