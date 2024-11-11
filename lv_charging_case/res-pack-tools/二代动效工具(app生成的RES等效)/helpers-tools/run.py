import os
import shutil

# 源文件夹路径
input_folder = "input"
# 目标文件夹路径
target_folder = "imbtools/images"

# 删除目标文件夹中的所有文件
shutil.rmtree(target_folder)
# 创建目标文件夹
os.makedirs(target_folder)

# 遍历源文件夹中的所有文件
for filename in os.listdir(input_folder):
    # 拼接源文件路径
    source_file = os.path.join(input_folder, filename)
    # 拼接目标文件路径
    target_file = os.path.join(target_folder, filename)
    # 复制文件到目标文件夹
    shutil.copyfile(source_file, target_file)


file_list = os.listdir(input_folder)
new_lines = []

for filename in file_list:
    if filename.endswith('.gif'):
        new_lines.append(f'    <Picture  compress_level="low" fmt="GIF">./images/{filename}</Picture>\n')

new_lines.append('    <Picture folder="true" png_format="ARGB8565" bmp_format="RGB565">images</Picture>\n')





# 修改ResBuilder.xml文件
xml_file = "imbtools/ResBuilder.xml"
with open(xml_file, "r", encoding='utf-8') as file:
    lines = file.readlines()

# 找到需要修改的行索引
start_index = lines.index("    <PictureList>\n") + 1
end_index = lines.index("    </PictureList>\n")

# 替换原有标签内容
lines[start_index:end_index] = new_lines

# 写入修改后的内容到文件
with open(xml_file, "w", encoding='utf-8') as file:
    file.writelines(lines)


import os
import re
#from PIL import Image


# 构建文件路径
run_bat_path = os.path.join('imbtools', 'Run.bat')

# 检查文件是否存在
if os.path.exists(run_bat_path):
    # 进入文件夹路径
    os.chdir("imbtools")
    
    # 执行Run.bat
    os.system('start /wait cmd /c Run.bat')
    
    # 返回上一级目录
    os.chdir('..')

# 读取头文件内容
with open("./imbtools/output/ui_pic_index.h", "r") as file:
    code = file.read()

# 提取常量数值和路径
pattern = r"#define\s+(\w+)\s+(\w+)\s*//\s*(.*)"
matches = re.finditer(pattern, code)

# 构建常量、数值和路径的列表
constants = []
for match in matches:
    constant = match.group(1)
    value = match.group(2)
    path = match.group(3)
    constants.append((constant, value, path))

# 检查路径是否已按大小排序
# is_sorted = all(constants[i][2] <= constants[i+1][2] for i in range(len(constants)-1))
# if not is_sorted:
#     print("文件名没有排序，重新排序")
#     constants = sorted(constants, key=lambda x: x[2])  # 按路径排序

# 暂停并输出常量列表
print("常量列表：")
for (constant, value, path) in constants:
    path = path.replace("\\", "/")
    print(f"Constant: {constant}, Value: {value}, Path: {path}") 

# 定义文件路径
output_path = "output/usr_pic_index.h"

f_count = 0

# 创建usr_pic_index.c文件
with open(output_path, "w") as f:
    f.write("#ifndef __usr_pic_index__\n")     
    f.write("#define __usr_pic_index__\n")  
    f.write('''
struct Idex {
  char* name;
  int id;
};
int NAME2ID(char* src);
''')
    for (constant, value, path) in constants:
        filename = os.path.basename(path);
        filename = os.path.splitext(filename)[0]
        id_name = constant.upper().replace(".", "_").replace("~", "_")
        #f.write(f"#define ID_{filename}\t\t\t(*(\"{int(value,16)}\"))\n")  #二级指针    
        f.write(f"#define ID_{filename}\t\t\t\"{int(value,16)}\"\n")    #字符串
        f_count = f_count+1
    f.write("#endif")   

    
# 定义文件路径
output_path3 = "output/usr_pic_index.idx"

f_count = 0

# 创建usr_pic_index.c文件
with open(output_path3, "w") as f:
    for (constant, value, path) in constants:
        filename = os.path.basename(path)
        filename = filename.ljust(12, '\0')

        #value = 1234
        formatted_value = f"{int(value,16):04d}"
        print(formatted_value)  # 输出：1234
        
        #f.write(f"#define ID_{filename}\t\t\t(*(\"{int(value,16)}\"))\n")  #二级指针    
        f.write(f"{filename}{formatted_value}")    #字符串
        f_count = f_count+1
    
    
    
# 定义文件路径
output_path2 = "output/usr_pic_index.c"
    
    
    
# 创建usr_pic_index.c文件

with open(output_path2, "w") as f:

    f.write('''
#include "usr_pic_index.h"
''')

    f.write("const struct Idex use_img_index[" + f"{f_count}" + "] = {\n")
    
    for (constant, value, path) in constants:
        filename = os.path.basename(path)
        filename = filename.replace(".png", ".bin")
        filename = filename.replace(".bmp", ".bin")
        filename = '/' + filename
        #filename = os.path.splitext(filename)[0]
        id_name = constant.upper().replace(".", "_").replace("~", "_")
        # f.write(f"\{\"{filename}\", {int(value,16)},\n")    
        
        f.write("    {" + ".name=\"{}\", .id={},".format(filename, int(value,16)) + "},\n")
    f.write("};")
    
    f.write('''
#include "cpu.h"
AT(.lvgl_ram) int NAME2ID(char* src){
    // extern const struct Idex use_img_index[];
    int i;
    sizeof(struct Idex);
    sizeof(use_img_index[0]);
    for(i=0;i<ARRAY_SIZE(use_img_index);i++){
        if(strcmp(src, use_img_index[i].name)==0){
            return use_img_index[i].id;
        }
    }
    printf("FIND ERROR");
    return 0;
}
''')
    
os.replace("imbtools/output/ui.res", "./output/ui.res")
os.replace("imbtools/output/ui_pic_index.h", "./output/ui_pic_index.h")
    
# 运行copy.bat文件
bat_file = '.\\copy.bat'
os.system(f'cmd /c "{bat_file}"')
    
    
print("图片总数量：{}".format(f_count))

import os

def get_file_size(file_path):
    # 检查文件是否存在
    if os.path.isfile(file_path):
        # 获取文件大小
        file_size = os.path.getsize(file_path)
        return file_size
    else:
        return "文件不存在"

# 替换成你要检查的文件路径
file_path = 'output/ui.res'
size = get_file_size(file_path)
print(f"资源文件大小: {size} 字节")

    
    
    
# 复制imbtools/output/ui_pic_index.h文件到Smartwatch_lvgl/ui/jl_images/
#import shutil
#shutil.copy(imbtools_path, "Smartwatch_lvgl/ui/jl_images/")
