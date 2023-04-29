//
// Created by 16479 on 2023/4/29.
//

#include "Core.h"

using namespace std;

Core::Core() : mLogger(spdlog::get("TheStarryDataApi")) {//构造函数
    this->mLibraryMgr = std::make_shared<ModuleManager>(LoaderType::library);//构造库管理对象
    this->mModuleMgr = std::make_shared<ModuleManager>(LoaderType::module);//构造模块管理对象
}

void Core::InitService() {
    this->mLibraryMgr->LoadAll();//加载所有的库
    this->mModuleMgr->LoadAll();//加载所有的模块
    this->mModuleMap = this->mModuleMgr->GetModuleList();//获取模块和名字的对照表
    this->mConfig = libProp::Config::Parse("./config.properties");//加载配置文件
}

void Core::RunService() {
    try {
        InitService();//初始化服务
        VerifyModuleService();//验证服务
    } catch (const exception &e) {
        this->mLogger->error("An error occurred when initializing the service,error msg {}.", e.what());
    }

    HttpService service;
    for (auto &temp: this->mServiceModuleMap)//遍历列表
    {
        if (temp.second)//添加服务
        {
            string serviceName = "/" + temp.second->GetServiceName();//获取运行的服务的名字
            this->mLogger->info("Enabling {}", serviceName);
            service.GET(serviceName.c_str(), temp.second->GetServiceFunc());
        }
    }

    http_server_t server;
    server.service = &service;
    server.port = this->mConfig["servicePort"];

    http_server_run(&server);//运行服务
}

void Core::VerifyModuleService() {
    /*
     * 判断对照表中的服务名字是否重复,如果重复,则直接禁用两个模块中的服务
    */
    for (auto &temp: this->mModuleMap)//遍历循环
    {
        std::string serviceName = temp.second->GetServiceName();//获取循环时的服务名字
        std::string name = temp.second->GetModuleName();//获取模块的名字

        if (this->mServiceModuleMap.find(serviceName) != this->mServiceModuleMap.end())//元素重复
        {
            //根据相同的服务名字获取到该重复对象的对象指针
            std::string inListName = this->mServiceModuleMap[serviceName]->GetModuleName();

            this->mLogger->error("{} and {} have equal service name,closed.", inListName, name);

            this->mServiceModuleMap[serviceName].reset();//设置对照表中的重复的模块的对象指针为空
        } else {//元素没有重复
            this->mServiceModuleMap.insert(make_pair(serviceName, shared_ptr<Module>(temp.second)));
        }
    }
}

void Core::RunHttpService() {

}
