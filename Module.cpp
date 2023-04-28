//
// Created by 16479 on 2023/4/22.
//

#include "Module.h"

using namespace std;

Module::~Module() {
if(this->mModuleHandle != NULL)
{
    FreeLibrary(this->mModuleHandle);//释放模块
}
}

Module::Module(const string moduleAddress) {
    wstring temp = this->mConvert.from_bytes(moduleAddress);//string 转换为 wstring

    this->mModuleHandle = LoadLibrary(temp.c_str());//以unicode 的方式加载动态链接库
    if(this->mModuleHandle == NULL)//判断模块是否被正确加载
        throw runtime_error(to_string(GetLastError()));//抛出包含 windows 错误的异常
}
