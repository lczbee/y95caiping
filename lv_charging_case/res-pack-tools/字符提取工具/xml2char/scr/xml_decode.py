import xml.etree.ElementTree as ET

# XML文件路径
xml_file = 'cp1250.xml'

def extract_char_ranges(xml_path):
    """提取字符串范围

    Args:
        xml_path (str): 输入xml文件路径

    Returns:
        list: 返回字符串范围列表
    """
    # 解析XML文件
    tree = ET.parse(xml_path)
    root = tree.getroot()

    # 提取Char元素内的文本内容
    char_ranges = [char.text for char in root.findall('Char')]

    return char_ranges

def convert_unicode_to_chars(unicode_list):
    """将unicode码点转字符

    Args:
        unicode_list (list): 输入unicode码点范围列表

    Returns:
        list: 返回字符串列表
    """
    chars_list = []

    for item in unicode_list:
        if '-' in item:  # 处理编码范围
            start, end = item.split('-')
            start, end = int(start[2:], 16), int(end[2:], 16)
            for code_point in range(start, end + 1):
                chars_list.append(chr(code_point))
        else:  # 处理单个编码
            code_point = int(item[2:], 16)
            chars_list.append(chr(code_point))

    return chars_list

def remove_unprintable_chars(s):
    """过滤不可见字符

    Args:
        s (list): 需要过滤的字符串列表

    Returns:
        list: 返回可见字符的字符串
    """
    return ''.join(char for char in s if char.isprintable())

def xml_unicode_2_char(file_path):
    # 执行提取范围
    ranges_list = extract_char_ranges(file_path)
    # 输出结果
    # print(ranges_list)
    
    # 转换并打印结果
    converted_chars = convert_unicode_to_chars(ranges_list)
    # print(converted_chars)
    
    # 过滤不可见字符并拼接成字符串
    str = remove_unprintable_chars(converted_chars)
    # print(str)
    
    return str

def xml_unicode_2_char_save_as_txt(input_path, output_path):
    str = xml_unicode_2_char(input_path)
    # print(output_path)
    
    with open(output_path.replace('xml', '') + 'txt', 'w', encoding='utf-8') as f:
        f.write(str)
    
    

# if __name__ == "__main__":
#     # # 执行提取操作
#     # ranges_list = extract_char_ranges(xml_file)
    
#     # # 输出结果
#     # print(ranges_list)
    
#     # # 转换并打印结果
#     # converted_chars = convert_unicode_to_chars(ranges_list)
#     # print(converted_chars)
        
#     # str = remove_unprintable_chars(converted_chars)
    
#     str = xml_unicode_2_char(xml_file)
    
#     with open('code.txt', 'w', encoding='utf-8') as f:
#         f.write(str)
    
