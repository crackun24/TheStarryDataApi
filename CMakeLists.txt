cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)

set(INCLUDE E:/env64/include)
set(LIB E:/env64/lib)

include_directories(${INCLUDE})
link_directories(${LIB})

add_definitions(-DGLOG_NO_ABBREVIATED_SEVERITIES
        -DWIN32_LEAN_AND_MEAN
        -DUNICODE
        -D_UNICODE)

project ("TheStarryDataApi")

link_libraries(libProp
        glog
        hv
        mysqlcppconn
        mysqlcppconn8
        libSls
        )


add_executable(${PROJECT_NAME} "main.cpp" main.cpp ModuleManager.cpp ModuleManager.h Module.cpp Module.h DllLoader.cpp DllLoader.h)

target_link_libraries(${PROJECT_NAME}
        glog
        hv
        mysqlcppconn
        mysqlcppconn8
        libSls
        )
