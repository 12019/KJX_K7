@cd make
@if exist *gprs.mak goto gprs
echo �Ҳ������õ�MAKE�ļ�
goto end
:gprs
@for %%x in (*gprs.mak) do set project=%%x
@cd ..\
@echo off
echo 	------------------------------------
echo 	---�������Ϲ�����---����A62;B601...
echo 	------------------------------------
set /p custom=
make %custom% gprs %*