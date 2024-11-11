import os
import shutil
import xml.etree.ElementTree as ET

# 创建output文件夹
# if not os.path.exists('output'):
#     os.makedirs('output')

# def callback(input_path, output_path):
#     print('in:{}, out:{}'.format(input_path, output_path))


# 定义函数，遍历当前路径及子目录下所有指定后缀文件
def files_ergodic(scan_folder, output_folder, suffix, ergodic_callback):
    """遍历指定后缀文件

    Args:
        scan_folder (str): 需被遍历的路径
        output_folder (str): 输出文件夹
        suffix (str): 后缀类型
        ergodic_callback (str): 遍历回调
    """
    for root, dirs, files in os.walk(scan_folder):
        for file in files:
            if file.endswith(suffix):
                input_dir = os.path.join(root, file)
                output_dir = os.path.join(output_folder, os.path.relpath(input_dir, scan_folder).replace(suffix, ''))
                print(output_dir)
                
                os.makedirs(os.path.dirname(output_dir), exist_ok=True)
                
                ergodic_callback(input_dir, output_dir)

# # 遍历当前路径及子目录下所有的xml文件，并输出同名txt文件到output文件夹下
# files_ergodic('.', 'output')

# print("处理完成！")

# files_ergodic('.', 'output', 'xml', callback)
