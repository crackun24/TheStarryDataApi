//
// Created by 16479 on 2023/4/29.
//

#ifndef THESTARRYDATAAPI_CORE_H
#define THESTARRYDATAAPI_CORE_H

#include <hv/HttpServer.h>
#include <spdlog/spdlog.h>
#include <set>
#include <iostream>
#include "ModuleManager.h"

class Core {//核心对象
private:
    NameModuleMap mModuleMap;//名字和服务的对照表
    std::unordered_map<std::string,std::shared_ptr<Module> > mServiceModuleMap;//服务名字和模块对象的对照
    std::shared_ptr<spdlog::logger> mLogger;//日志记录器对象
    std::shared_ptr<ModuleManager> mModuleMgr;//模块管理对象
    std::shared_ptr<ModuleManager> mLibraryMgr; //库管理对象
    void InitService();//初始化服务
    void VerifyModuleService();//校验模块中的服务是否符合要求
    void RunHttpService();//运行http服务
public:
    void RunService();//运行服务
    Core();
};


#endif //THESTARRYDATAAPI_CORE_H
