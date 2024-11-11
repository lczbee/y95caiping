import os

# 输入文件名
input_file = "input.txt"
# 输出文件名
output_file = 'output.xml'

# @brief    转换为unicode编码
# @param    文件路径
# @return   unicode编码字符串
def convert_to_unicode(file_path):
    # 打开文件
    with open(file_path, 'r', encoding='utf-8') as file:
        content = file.read()

        # 用于记录unicode编码内容
        unicode_content = ""
        
        # 遍历文件内容，并通过ord()转换为ascii或者unicode编码
        for char in content:
            unicode_content += f"\\u{ord(char):04x}"
        
        return unicode_content
    

# @brief    合并连续编码，如0x0003 0x0004 0x0005合并为0x0003-0x0005
# @param    unicode编码列表
# @return   合并后的unicode编码列表
def merge_continuous(nums):
    intervals = [[nums[0]]]  # 初始化一个二维列表
    for num in nums[1:]:
        if num == intervals[-1][-1] + 0x1:  # 如当前数字与上一个区间的最后一个数字相差1，则将该数字添加到上一个区间
            intervals[-1].append(num)
        else:  # 否则新建一个区间并以当前数字为起始
            intervals.append([num])

    # 如果区间长度大于1则以‘起始值-结束值’的形式输出，否则只输出起始值
    return ['0x{:04X}-0x{:04X}'.format(x[0], x[-1]) if len(x) > 1 else '0x{:04X}'.format(x[0]) for x in intervals]

    
# @brief    转化为xml内容
# @param    unicode编码列表
# @return   合并后的unicode编码列表
def convert_to_xml(unicode_list):

    # 用于记录xml内容
    xml_content = ""

    # 遍历unicode编码列表
    for unicode_item in unicode_list:
        if '-' in unicode_item:  # 若内容包含‘-’则输出为“<Char>{起始值}-{结束值}</Char>”
            start_u, end_u = unicode_item.split('-')
            xml_content += f"\t<Char>{start_u}-{end_u}</Char>\n"
        else:  #否则输出<Char>{起始值}</Char>
            xml_content += f"\t<Char>{unicode_item}</Char>\n"
    
    # 去除头尾空格
    return xml_content.strip()



def main():
    # 判断是否存在输出文件，存在则清除，确保重头开始写文件
    if(os.path.exists(output_file)):
        os.remove(output_file)

    # 打开输出文件，以追加方式写
    output = open(output_file, 'a', encoding='utf-8')

    # 写入xml头部信息：
    # <?xml version="1.0" encoding="UTF-8"?>
    # <CharSet>
    output.write('<?xml version="1.0" encoding="UTF-8"?>\n<CharSet>\n\t')
    unicode_data = convert_to_unicode(input_file)
    # print(unicode_data)

    # 输出unicode编码的过程文件，内容为\uaaaa\ubbbb......
    # unicode_data_file = open('unicode_data.txt', 'w', encoding='utf-8')
    # unicode_data_file.write(str(unicode_data))

    # 将\uaaaa转换为0xaaaa
    unicode_data = str.replace(unicode_data, r'\u', ' 0x')
    # 利用set特性去重，再利用sorted进行升序排序
    unicode_unique = sorted((set(unicode_data.split())))

    # 输出去重并重新排序的unicode列表
    # unicode_unique_file = open('unicode_unique.txt', 'w', encoding='utf-8')
    # unicode_unique_file.write(str(unicode_unique))

    # 将unicode列表每个元素转为16进制整数形式
    unicode_unique = [int(x, 16) for x in unicode_unique]
    # print(unicode_unique)

    # 合并连续区间
    merged = merge_continuous(unicode_unique)
    # print(merged)
    
    # 转换为xml文件输出
    merged_str = convert_to_xml(merged)
    output.write(merged_str)

    # 写入xml结尾信息：
    # </CharSet>
    output.write('\n</CharSet>')

if __name__ == "__main__":
    main()

