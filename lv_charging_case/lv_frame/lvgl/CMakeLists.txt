cmake_minimum_required(VERSION 3.12)
project(MyProject)

set(PREFUX_PATH "lv_charging_case/lv_frame/lvgl")
set(PREFUX_FRAME_PATH "lv_charging_case/lv_frame")

# 遍历文件夹并获取.c文件和.h文件
file(GLOB_RECURSE C_FILES "*.c")
file(GLOB_RECURSE H_FILES "*.h")

# 过滤掉不需要的文件或文件夹
list(FILTER C_FILES EXCLUDE REGEX "CMakeFiles")
list(FILTER H_FILES EXCLUDE REGEX "CMakeFiles")

# 生成.mk文件
file(WRITE "lvgl.mk" "c_SRC_FILES += \\\n")
foreach(file ${C_FILES})
    file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${file})
    file(APPEND "lvgl.mk" "\t${PREFUX_PATH}/${rel_path} \\\n")
endforeach()

file(APPEND "lvgl.mk" "\nINCLUDES += \\\n")
# foreach(file ${H_FILES})
#     get_filename_component(dir_path ${file} DIRECTORY)
#     if(NOT "${dir_path}" STREQUAL "${last_dir_path}")
#         file(RELATIVE_PATH rel_path ${CMAKE_SOURCE_DIR} ${dir_path})
#         file(APPEND "lvgl.mk" "\t-I${PREFUX_PATH}/${rel_path} \\\n")
#         set(last_dir_path ${dir_path})
#     endif()
# endforeach()
file(APPEND "lvgl.mk" "\t-I${PREFUX_PATH} \\\n")
file(APPEND "lvgl.mk" "\t-I${PREFUX_FRAME_PATH} \\\n")