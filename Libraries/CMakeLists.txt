cmake_minimum_required(VERSION 3.2)	
project(Libraries)

if(NOT TARGET imgui)
    include(imgui.cmake)
    set_target_properties(imgui PROPERTIES FOLDER ${THIRD_PARTY_FOLDER})
endif()

LIST(APPEND LibrariesSubDir "glad")
LIST(APPEND LibrariesSubDir "glfw")
LIST(APPEND LibrariesSubDir "glm")
LIST(APPEND LibrariesSubDir "assimp")

set(PROJECT_LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
foreach(dirname ${LibrariesSubDir}) 
	add_subdirectory(${dirname})
endforeach()

add_subdirectory("ImGuiFileDialog")
target_include_directories(ImGuiFileDialog PRIVATE
    $<TARGET_PROPERTY:imgui,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:imgui,INCLUDE_DIRECTORIES>
)
set_target_properties(ImGuiFileDialog PROPERTIES FOLDER ${THIRD_PARTY_FOLDER})
