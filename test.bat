@echo off
::工程文件的存放目录，设定变量，以%dir%引用该变量
::使用""包裹袋空格的路径
::set dir="D:\A B\"

::/r命令后面跟随目录，以该目录为根遍历文件树，Debug ipch为要删除的文件夹 /q为静默删除，/s为删除目录下所有文件
::遍历文件树时，变量%%a也会包含空格使用""包裹
for /r %dir% %%a in (Debug ipch) do rd /q/s "%%a"
::删除dir目录及其子目录的所有以sdf结尾的文件
del /s %dir%*.sdf

pause