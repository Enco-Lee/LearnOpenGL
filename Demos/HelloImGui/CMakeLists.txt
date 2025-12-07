cmake_minimum_required(VERSION 3.2)	
project("HelloImGui")

# 开启多线程编译 和 使用 c++latest 版本
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /std:c++latest")

option(USE_SOLUTION_FOLDERS "使用资源管理器文件夹" ON)
option(GROUP_BY_EXPLORER ON) 							# 开启分组
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

file(GLOB_RECURSE HEADER_FILES *.h *.hpp *.ini)
file(GLOB_RECURSE SOURCE_FILES *.cpp *.c)
file(GLOB_RECURSE SHADER_FILES *.hlsl *.vs *.fs)

set(CppFile ${HEADER_FILES} ${SOURCE_FILES})
set(AllFile ${CppFile} ${SHADER_FILES})

foreach(fileItem ${AllFile})
	get_filename_component(PARENT_DIR "${fileItem}" DIRECTORY)
	string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
	string(REPLACE "/" "\\" GROUP "${GROUP}")
	set(GROUP "${GROUP}")
	source_group("${GROUP}" FILES "${fileItem}")
endforeach()

if(MSVC)
  # 源文件编码：告诉编译器用 UTF-8 解析源码（包括注释）
  add_compile_options("/source-charset:utf-8")
  # 执行编码：字符串常量在运行时的编码（解决中文输出乱码）
  add_compile_options("/execution-charset:utf-8")
endif()

add_executable(${PROJECT_NAME} ${AllFile})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "Demos")

set(RESOURCES ${SHADER_FILES})
set_property(SOURCE ${RESOURCES} PROPERTY VS_TOOL_OVERRIDE "shader")			# 设置 hlsl 为 shader 资源文件

# 设置程序工作目录为 cmake 工作目录
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(${PROJECT_NAME} PUBLIC
	#${PROJECT_COMPONENTS_DIR}/../
)

target_link_libraries(${PROJECT_NAME} PUBLIC 
	#Common
	imgui
	ImGuiFileDialog
	glm
)