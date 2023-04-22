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
        if(!file.is_directory())
        {
            string fileName = file.path().filename().string();//获取文件的名字
            string fileType =  fileName.substr(fileName.find_last_of('.') + 1);//获取文件的类型
           if(fileType ==  MODULE_TYPE_NAME)
           {
           }
            this->mLogger->info(file.path().filename().string());
            this->mLogger->info(fileType);
        }
    }

    this->mLogger->info("Modules Loaded.");
}
