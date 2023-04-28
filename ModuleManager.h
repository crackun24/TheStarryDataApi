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
#include <algorithm>
#include <filesystem>
#include "Module.h"

typedef enum{
    library, module
}LoaderType;//判断要管理的dll类型是库还是模块

class ModuleManager {
private:
    const std::string MODULE_PATH = "./modules";
    const std::string LIBRARY_PATH = "./libs";//模块使用的库的存放的位置
#ifdef _WINDOWS//判断系统的类型决定要加载的动态库的类型
    const std::string MODULE_TYPE_NAME = "dll";
#endif
#ifdef linux
    const std::string MODULE_TYPE_NAME = "so";
#endif

    void LoadAllLibrary();//加载所有的库
    std::unordered_map<std::string, std::shared_ptr<Module>> mModuleMap;//模块的名字和模块的句柄的对照表
    std::shared_ptr<spdlog::logger> mLogger;//日志记录器对象
    std::shared_ptr<Module> LoadModule(const std::string &moduleName);//加载单个模块
    std::string mLoadPath;//加载dll的路径
    LoaderType mLoaderType;
public:
    void LoadAllModules();//加载所有的模块到内存中
    ModuleManager(LoaderType type);//构造函数
};


#endif //ALERTSYS_MODULEMANAGER_H
