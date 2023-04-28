//
// Created by 16479 on 2023/4/21.
//
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>
#include <io.h>
#include <direct.h>
#include <memory>
#include "ModuleManager.h"

using namespace spdlog;
using namespace std;

int main()
{
    SetErrorMode(SEM_FAILCRITICALERRORS);//设置发生错误时,不会弹窗,防止阻塞程序
if(_access("./logs",0) == -1)//判断日志存放文件夹是否存在
    _mkdir("./logs");

    auto console_sink = make_shared<sinks::stdout_color_sink_mt>();
    auto daily_sink = make_shared<sinks::daily_file_sink_mt>("./logs/log.log", 0, 0);
    auto logger = make_shared<spdlog::logger>("TheStarryDataApi", sinks_init_list{console_sink, daily_sink});
    register_logger(logger);//注册日志记录器

    unique_ptr<ModuleManager>moduleManager(new ModuleManager(LoaderType::module));//创建一个模块管理对象
    moduleManager->LoadAllModules();

    getchar();
    return 0;
}