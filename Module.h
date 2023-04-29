//
// Created by 16479 on 2023/4/22.
//

#ifndef THESTARRYDATAAPI_MODULE_H
#define THESTARRYDATAAPI_MODULE_H

#include <windows.h>
#include <iostream>
#include <shared_mutex>
#include <hv/http_client.h>
#include <DataApi.h>
#include <codecvt>
#include "DllLoader.h"

static const int API_VERSION = 1;//使用的api的版本

typedef int (*moduleMainFunc)(HttpRequest *req,HttpResponse *rep);//模块中的数据处理的函数
typedef ApiData (*moduleRegFunc)();//模块中的注册函数

class Module :public DllLoader{
private:
    ApiData mApiData;//api的信息
    moduleMainFunc mMainFunc = nullptr;//主函数的函数指针
    moduleRegFunc mRegFunc = nullptr;//模块注册的函数指针
    void VerifyApi();//验证api是否符合要求

public:
    Module(const std::string moduleAddress);//按照地址加载动态链接库
    moduleMainFunc GetServiceFunc();//获取函数注册的函数指针
    int GetModuleApiVersion();
    std::string GetModuleName();//获取模块的名字
    std::string GetServiceName();//获取模块要注册的网络服务的名字
};


#endif //THESTARRYDATAAPI_MODULE_H
