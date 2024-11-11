

copy .\output\usr_pic_index.h  ..\..\lv_frame\jlres\usr_pic_index.h

copy  .\output\usr_pic_index.c  ..\..\lv_frame\jlres\usr_pic_index.c


copy .\output\ui.res  ..\..\..\cpu\br28\tools\ui_resource


rd /S /Q ..\资源更换工具入口\USER_IMAGE

xcopy /E /I /Y .\imbtools\images   ..\资源更换工具入口\USER_IMAGE


pause