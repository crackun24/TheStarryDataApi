//
// Created by 16479 on 2023/4/22.
//

#ifndef THESTARRYDATAAPI_MODULE_H
#define THESTARRYDATAAPI_MODULE_H

#include <windows.h>
#include <iostream>
#include <hv/http_client.h>
#include <codecvt>

typedef int (*moduleMainFunc)(HttpRequest *req,HttpResponse *rep);//模块中的函数类型

class Module {
private:
    std::wstring_convert<std::codecvt_utf8<wchar_t>> mConvert;//字符转换对象
    HMODULE mModuleHandle;//模块的句柄
    FARPROC mMainFuncAddress;//主函数的函数地址
public:
    Module(const std::string moduleAddress);//按照地址加载动态链接库
    ~Module();//析构函数
};


#endif //THESTARRYDATAAPI_MODULE_H
