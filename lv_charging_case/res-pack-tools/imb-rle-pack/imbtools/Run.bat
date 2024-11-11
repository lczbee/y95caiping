@echo off
ResBuilder.exe
if not exist output md output
copy result.bin output\ui.res
copy result.str output\ui.str
copy result_pic_index.h output\ui_pic_index.h
copy result_str_index.h output\ui_str_index.h



pause