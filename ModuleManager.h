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

typedef std::unordered_map<std::string,std::shared_ptr<Module> > NameModuleMap;

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

    NameModuleMap mModuleMap;//模块的文件名字和模块的句柄的对照表
    std::vector<std::shared_ptr<DllLoader>> mLibList;//库文件的队列

    std::shared_ptr<spdlog::logger> mLogger;//日志记录器对象
    std::shared_ptr<Module> LoadModule(const std::string &moduleName);//加载单个模块
    std::shared_ptr<DllLoader> LoadLibrary(const std::string &libraryName);//加载单个库
    std::string mLoadPath;//加载dll的路径
    std::string mLoaderName;//加载器的名字,(模块或库)
    LoaderType mLoaderType;
    void LoadAllModule();//加载模块
    void LoadAllLib();//加载库
public:
    void LoadAll();//加载所有的dll到内存中
    NameModuleMap GetModuleList();//获取模块名字和单个对象的对照
    ModuleManager(LoaderType type);//构造函数
};


#endif //ALERTSYS_MODULEMANAGER_H
