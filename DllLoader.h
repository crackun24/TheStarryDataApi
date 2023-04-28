//
// Created by 16479 on 2023/4/28.
//

#ifndef THESTARRYDATAAPI_DLLLOADER_H
#define THESTARRYDATAAPI_DLLLOADER_H

#include <windows.h>
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

class DllLoader {
protected:
    std::wstring_convert<std::codecvt_utf8<wchar_t>> mConvert;//字符转换对象
    HMODULE mModuleHandle = nullptr;//dll的句柄
public:
    DllLoader(const std::string moduleAddress);

    virtual ~DllLoader();
};


#endif //THESTARRYDATAAPI_DLLLOADER_H
