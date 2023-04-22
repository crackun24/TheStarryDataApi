//
// Created by 16479 on 2023/4/22.
//

#ifndef ALERTSYS_MODULEMANAGER_H
#define ALERTSYS_MODULEMANAGER_H

#include <windows.h>
#include <spdlog/spdlog.h>
#include <vector>
#include <unordered_map>
#include <memory>
#include <filesystem>

class ModuleManager {
private:
    const std::string MODULE_PATH = "./modules";

#ifdef _WINDOWS//判断系统的类型决定要加载的动态库的类型
    const std::string  MODULE_TYPE_NAME = "dll";
#elifdef linux
    const std::string MODULE_TYPE_NAME = "so";
#endif

    std::unordered_map<std::string,HINSTANCE>mModuleMap;//模块的名字和模块的句柄的对照表
    std::shared_ptr<spdlog::logger> mLogger;//日志记录器对象
public:
    void LoadAllModules();//加载所有的模块到内存中
    ModuleManager();//构造函数
};


#endif //ALERTSYS_MODULEMANAGER_H
