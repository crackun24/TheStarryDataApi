//
// Created by 16479 on 2023/4/22.
//

#include "ModuleManager.h"

using namespace std;
using namespace spdlog;

ModuleManager::ModuleManager(LoaderType type) : mLogger(get("TheStarryDataApi")), mLoaderType(type) {
    switch (type) {
        case module:
            this->mLoadPath = MODULE_PATH;
            this->mLoaderName = "module";
            break;
        case library:
            this->mLoadPath = LIBRARY_PATH;
            this->mLoaderName = "library";
            break;
    }
}

void ModuleManager::LoadAll() {
   if(this->mLoaderType == module)//判断是否为模块
    {
       LoadAllModule();//加载所有的模块
    }else if(this->mLoaderType == library)//判断是否为库类型
    {
       LoadAllLib();//加载所有的库
    }
}

shared_ptr<Module> ModuleManager::LoadModule(const string &moduleName) {//加载单个模块
    const string fullFilePath = mLoadPath + "/" + moduleName;//生成完整的文件路径

    shared_ptr<Module> module;
    module = make_shared<Module>(fullFilePath);//加载模块

    return module;//返回模块的智能指针对象
}

void ModuleManager::LoadAllLib() {
    this->mLogger->info("Loading the {}.", this->mLoaderName);

    bool isPathExist = true;
    if (filesystem::exists(this->mLoadPath)) {//判断文件是否存在
        isPathExist = filesystem::is_directory(this->mLoadPath);//判断文件是否为目录

    } else {
        isPathExist = false;
    }

    if (!isPathExist) {//判断文件的类型是否为文件夹
        filesystem::create_directory(this->mLoadPath);//文件夹不存在则创建插件的文件夹
        this->mLogger->warn("The {} directory does not exist,created.", this->mLoaderName);
    } else {//如果文件夹不存在则无需执行下面的操作
        for (auto &file: filesystem::directory_iterator(this->mLoadPath)) {//遍历模块文件夹下的所有文件
            if (!file.is_directory()) {
                string fileName = file.path().filename().string();//获取文件的名字
                string fileType = fileName.substr(fileName.find_last_of('.') + 1);//获取文件的类型
                transform(fileType.begin(), fileType.end(), fileType.begin(), [](unsigned char c) {
                    return tolower(c);
                });//将文件的类型名转换为小写

                if (fileType == MODULE_TYPE_NAME) {//判断文件的后缀名是否符合要求
                    this->mLogger->info("Found {}: {}", this->mLoaderName, file.path().filename().string());

                    try {
                        auto handle = LoadLibrary(fileName);
                        this->mLibList.push_back(handle);//假如库列表中

                        this->mLogger->info("{} {} loaded", this->mLoaderName, fileName);
                    } catch (const logic_error &e) {
                        this->mLogger->error("An error occurred when loading the {}: {}, error str: {}",
                                             this->mLoaderName, fileName,
                                             e.what());
                    }
                    catch (const runtime_error &e) {
                        this->mLogger->error("An error occurred when loading the {}: {},error code: {}",
                                             this->mLoaderName, fileName,
                                             e.what());
                    }
                }

            }
        }

        this->mLogger->info("All available {} Loaded.Amount: {}", this->mLoaderName, this->mLibList.size());
    }
}

void ModuleManager::LoadAllModule() {
    this->mLogger->info("Loading the {}.", this->mLoaderName);

    bool isPathExist = true;
    if (filesystem::exists(this->mLoadPath)) {//判断文件是否存在
        isPathExist = filesystem::is_directory(this->mLoadPath);//判断文件是否为目录

    } else {
        isPathExist = false;
    }

    if (!isPathExist) {//判断文件的类型是否为文件夹
        filesystem::create_directory(this->mLoadPath);//文件夹不存在则创建插件的文件夹
        this->mLogger->warn("The {} directory does not exist,created.", this->mLoaderName);
    } else {//如果文件夹不存在则无需执行下面的操作
        for (auto &file: filesystem::directory_iterator(this->mLoadPath)) {//遍历模块文件夹下的所有文件
            if (!file.is_directory()) {
                string fileName = file.path().filename().string();//获取文件的名字
                string fileType = fileName.substr(fileName.find_last_of('.') + 1);//获取文件的类型
                transform(fileType.begin(), fileType.end(), fileType.begin(), [](unsigned char c) {
                    return tolower(c);
                });//将文件的类型名转换为小写

                if (fileType == MODULE_TYPE_NAME) {//判断文件的后缀名是否符合要求
                    this->mLogger->info("Found {}: {}", this->mLoaderName, file.path().filename().string());

                    try {
                        auto handle = LoadModule(fileName);
                        this->mModuleMap.insert(make_pair(fileName.substr(0, fileName.find_last_of('.')),
                                                          handle));//将模块插入对照表中

                        this->mLogger->info("{} {} loaded", this->mLoaderName, fileName);
                    } catch (const logic_error &e) {
                        this->mLogger->error("An error occurred when loading the {}: {}, error str: {}",
                                             this->mLoaderName, fileName,
                                             e.what());
                    }
                    catch (const runtime_error &e) {
                        this->mLogger->error("An error occurred when loading the {}: {},error code: {}",
                                             this->mLoaderName, fileName,
                                             e.what());
                    }
                }

            }
        }

        this->mLogger->info("All available {} Loaded.Amount: {}", this->mLoaderName, this->mModuleMap.size());
    }
}

shared_ptr<DllLoader> ModuleManager::LoadLibrary(const string &libraryName) {//加载单个模块
    const string fullFilePath = this->mLoadPath + "/" + libraryName;//生成完整的文件路径

    shared_ptr<DllLoader> library;
    library = make_shared<DllLoader>(fullFilePath);//加载模块

    return library;//返回库的智能指针对象
}

NameModuleMap ModuleManager::GetModuleList() {
   return this->mModuleMap;
}
