import file_ergodic as fe
import xml_decode as xd
import os
import shutil

input_path = '.'
output_path = 'output'

if __name__ == '__main__':
    if(os.path.exists(output_path)):
        shutil.rmtree(output_path)
        
    fe.files_ergodic(input_path, output_path, 'xml', xd.xml_unicode_2_char_save_as_txt)