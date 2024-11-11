@echo off
cd /d "%~dp0\GPU2D"
cmake . -G "MinGW Makefiles"
cd /d "%~dp0\lv_frame\adapter"
cmake . -G "MinGW Makefiles"
cd /d "%~dp0\lv_frame\jlres"
cmake . -G "MinGW Makefiles"
cd /d "%~dp0\lv_frame\generated"
cmake . -G "MinGW Makefiles"
cd /d "%~dp0\lv_frame\custom"
cmake . -G "MinGW Makefiles"
cd /d "%~dp0\lv_frame\lvgl"
cmake . -G "MinGW Makefiles"
cd /d "%~dp0\lv_frame\ui"
cmake . -G "MinGW Makefiles"
cd /d "%~dp0\porting"
cmake . -G "MinGW Makefiles"

cd /d "%~dp0"

del *makefile /s
del *.ninja /s
del *.cmake /s
del *CMakeCache.txt /s

for /d /r %%i in (*) do (
    if "%%~nxi"=="CMakeFiles" (
        rd /s /q "%%i"
    )
)

cd  ..

for /d /r %%i in (*) do (
    if "%%~nxi"=="objs" (
        rd /s /q "%%i"
    )
)

::pause