//
// Created by 16479 on 2023/4/22.
//

#include "ModuleManager.h"

using namespace std;
using namespace spdlog;

ModuleManager::ModuleManager() : mLogger(get("TheStarryDataApi")) {
}

void ModuleManager::LoadAllModules() {
    this->mLogger->info("Loading the modules.");

    bool isPathExist = true;
    if (filesystem::exists(MODULE_PATH)) {//判断文件是否存在
        isPathExist = filesystem::is_directory(MODULE_PATH);//判断文件是否为目录

    } else {
        isPathExist = false;
    }

    if (!isPathExist) {
        filesystem::create_directory(MODULE_PATH);
        this->mLogger->warn("The modules directory does not exist,created.");
    }

    for (auto &file: filesystem::directory_iterator(MODULE_PATH)) {//遍历模块文件夹下的所有文件
        if (!file.is_directory()) {
            string fileName = file.path().filename().string();//获取文件的名字
            string fileType = fileName.substr(fileName.find_last_of('.') + 1);//获取文件的类型
            transform(fileType.begin(), fileType.end(), fileType.begin(), [](unsigned char c) {
                return tolower(c);
            });//将文件的类型名转换为小写

            if (fileType == MODULE_TYPE_NAME) {
                try {
                    auto handle = LoadModule(fileName);
                    this->mModuleMap.insert(make_pair(fileName.substr(0, fileName.find_last_of('.')),
                                                      handle));//将模块插入对照表中
                } catch (const exception &e) {
                    this->mLogger->error("An error occurred when loading the module: {},error code: {}", fileName,
                                         e.what());
                }
            }

            this->mLogger->info("Found library: {}", file.path().filename().string());
        }
    }

    this->mLogger->info("All available modules Loaded.Amount: {}", this->mModuleMap.size());
}

shared_ptr<Module> ModuleManager::LoadModule(const string moduleName) {
    const string fullFilePath = MODULE_PATH + "/" + moduleName;//生成完整的文件路径

    shared_ptr<Module> module;
    module.reset(new Module(fullFilePath));//加载模块

    return module;//返回模块的智能指针对象
}
