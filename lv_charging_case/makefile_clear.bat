@echo off

del *.mk /s
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
