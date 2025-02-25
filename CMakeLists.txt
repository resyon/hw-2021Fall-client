cmake_minimum_required(VERSION 3.1)

set(project_name hw-2021Fall-client) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 20)

add_library(${project_name}-lib
        src/DemoApiClient.hpp
        src/DemoApiModels.hpp
        src/SimpleClient.hpp
        src/SimpleClient.cpp
        src/CLIClient.cpp
        src/CLIClient.hpp

        src/dto/UserDto.hpp
        src/dto/StatusDto.hpp
        src/dto/DocDto.hpp
        src/dto/LendRecordDto.hpp
        src/dto/PageDto.hpp
        )

## link libs

find_package(oatpp      1.3.0 REQUIRED)
find_package(oatpp-curl 1.3.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-curl
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)
