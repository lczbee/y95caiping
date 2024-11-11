@echo off

@echo ********************************************************************************
@echo 			SDK BR28			
@echo ********************************************************************************
@echo %date%

cd %~dp0


copy ..\..\script.ver .
copy ..\..\uboot.boot .
::copy ..\..\ota.bin .
::copy ..\..\ota_all.bin .
copy ..\..\nor_ota.bin .
copy ..\..\tone.cfg .
copy ..\..\cfg_tool.bin .
::copy ..\..\app.bin .
copy ..\..\br28loader.bin .
::copy ..\..\user_api.bin .
::copy ..\..\isd_config.ini .
copy ..\..\p11_code.bin .
::copy ..\..\config.dat .
copy ..\..\default.key .
copy ..\..\json.txt .
copy ..\..\eq_cfg_hw.bin .

cd ..\..\ui_resource
copy *.* ..\download\watch

cd %~dp0

cd ..\..\ui_upgrade
copy *.* ..\download\watch\ui_upgrade
cd %~dp0

..\..\json_to_res.exe json.txt
..\..\md5sum.exe app.bin md5.bin
set /p "themd5=" < "md5.bin"


::echo %1

set CHIPKEY=default.key


del /Q res.ori\*
del upgrade.zip
move JL res.ori\JL
move watch? res.ori\
move font res.ori\font

::..\..\packres.exe -n res -o res.bin new_res.bin 0 -normal

..\..\isd_download.exe -tonorflash -dev br28 -boot 0x120000 -div8 -wait 300 -uboot uboot.boot -app app.bin cfg_tool.bin -res  ui_upgrade p11_code.bin config.dat tone.cfg eq_cfg_hw.bin  -uboot_compress -key %CHIPKEY% -format all

::-format all
::-ex_flash res.bin

:: -format all
::-reboot 2500
:: -key xxxx.key

::-format all
::-reboot 100


@rem ɾ����ʱ�ļ�-format all
if exist *.mp3 del *.mp3 
if exist *.PIX del *.PIX
if exist *.TAB del *.TAB
if exist *.res del *.res
if exist *.sty del *.sty
if exist *.str del *.str
if exist *.anim del *.anim
if exist *.view del *.view
if exist *.json del *.json

copy ota.bin ota_all.bin
copy nor_ota.bin ota.bin
@rem ���ɹ̼������ļ�
..\..\fw_add.exe -noenc -fw jl_isd.fw  -add ota.bin -type 100 -out jl_isd.fw
@rem �������ýű��İ汾��Ϣ�� FW �ļ���
..\..\fw_add.exe -noenc -fw jl_isd.fw -add script.ver -out jl_isd.fw


..\..\ufw_maker.exe -fw_to_ufw jl_isd.fw
copy jl_isd.ufw nor_up.ufw
del jl_isd.ufw

copy ota_all.bin ota.bin
del ota_all.bin 

::..\..\zip.exe -r upgrade.zip res.ori nor_up.ufw

@REM ���������ļ������ļ�
::ufw_maker.exe -chip AC800X %ADD_KEY% -output config.ufw -res bt_cfg.cfg

::IF EXIST jl_693x.bin del jl_693x.bin 


@rem ��������˵��
@rem -format vm        //����VM ����
@rem -format cfg       //����BT CFG ����
@rem -format 0x3f0-2   //��ʾ�ӵ� 0x3f0 �� sector ��ʼ�������� 2 �� sector(��һ������Ϊ16���ƻ�10���ƶ��ɣ��ڶ�������������10����)

ping /n 2 127.1>null
IF EXIST null del null
pause
