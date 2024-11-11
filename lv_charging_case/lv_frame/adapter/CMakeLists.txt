cmake_minimum_required(VERSION 3.12)
project(MyProject)

set(PREFIX_PATH "lv_charging_case/lv_frame/adapter")  # 定义前缀路径

# 遍历文件夹并获取.c文件和.h文件
file(GLOB_RECURSE C_FILES "*.c")
file(GLOB_RECURSE H_FILES "*.h")

# 过滤掉不需要的文件或文件夹
list(FILTER C_FILES EXCLUDE REGEX "CMakeFiles")
list(FILTER H_FILES EXCLUDE REGEX "CMakeFiles")

# 生成.mk文件
file(WRITE "adapter.mk" "c_SRC_FILES += \\\n")
foreach(file ${C_FILES})
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${file})
    file(APPEND "adapter.mk" "\t${PREFIX_PATH}/${rel_path} \\\n")
endforeach()

file(APPEND "adapter.mk" "\nINCLUDES += \\\n")
# 获取包含.h文件的目录
set(H_DIRS "")
foreach(file ${H_FILES})
    get_filename_component(dir_path ${file} DIRECTORY)
	file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${dir_path})
    list(APPEND H_DIRS ${rel_path})
endforeach()
list(REMOVE_DUPLICATES H_DIRS)

# 生成包含.h文件的目录的路径
if(H_DIRS)
	foreach(dir ${H_DIRS})
		file(APPEND "adapter.mk" "\t-I${PREFIX_PATH}/${dir} \\\n")
	endforeach()
else()
	file(APPEND "adapter.mk" "\t-I${PREFIX_PATH} \\\n")
endif()