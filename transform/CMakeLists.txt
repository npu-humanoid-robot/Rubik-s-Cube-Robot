
#1.cmake verson，指定cmake版本 
cmake_minimum_required (VERSION 3.5.1)
#2.project name，指定项目的名称，一般和项目的文件夹名称对应
PROJECT(transform)
#3.find packages
FIND_PACKAGE(WiringPi REQUIRED)
FIND_PACKAGE(Threads REQUIRED)
#4.head file path，头文件目录
INCLUDE_DIRECTORIES(include  ${WIRINGPI_INCLUDE_DIRS})
#5.source directory，源文件目录
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
#6.set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"
SET(TEST_MATH
${DIR_SRCS}
)
#7.add executable file，添加要编译的可执行文件
ADD_EXECUTABLE(${PROJECT_NAME} ${TEST_MATH})
add_definitions(-std=c++0x -lwiringPi -lpthread)
#7.add link library，添加可执行文件所需要的库，比如我们用到了libm.so（命名规则：lib+name+.so），就添加该库的名称
TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${WIRINGPI_LIBRARIES}) 
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT}) 