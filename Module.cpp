//
// Created by 16479 on 2023/4/22.
//

#include "Module.h"

Module::~Module() {
if(this->mModuleHandle != NULL)
{
    FreeLibrary(this->mModuleHandle);//释放模块
}
}
