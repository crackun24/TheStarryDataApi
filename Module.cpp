//
// Created by 16479 on 2023/4/22.
//

#include "Module.h"

using namespace std;

Module::Module(const string moduleAddress) : DllLoader(moduleAddress) {
    this->mRegFunc = (moduleRegFunc) GetProcAddress(this->mModuleHandle, "RegApi");
    this->mMainFunc = (moduleMainFunc) GetProcAddress(this->mModuleHandle, "MainFunc");
    VerifyApi();//验证api
}

void Module::VerifyApi() {
    if (this->mRegFunc == nullptr || this->mMainFunc == nullptr)//判断关键的函数是否为空
        throw runtime_error(to_string(GetLastError()));//若函数指针为空则抛出异常

    this->mApiData = this->mRegFunc();//加载api的数据

    if (this->mApiData.apiVersion > API_VERSION)//判断模块的版本是否大于加载器的api版本
        throw logic_error("Module version is higher than loader version.");
}

int Module::GetModuleApiVersion() {
    return this->mApiData.apiVersion;
}

std::string Module::GetModuleName() {
    return this->mApiData.moduleName;
}

std::string Module::GetServiceName() {
    return this->mApiData.apiServiceName;
}

moduleMainFunc Module::GetServiceFunc() {
   return this->mMainFunc;//返回服务的函数指针
}
