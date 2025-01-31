@echo off
set prj=
set customer=TOUR
set optr_path=PPP
set optr_spec=NONE
set main_lcd_size=240X320
set touch_panel_support=NONE
if %customer%==MTK set customer=PLUTO
set clean_opt=FALSE
set remake_opt=FALSE
set copy_opt=FALSE
set remake_plmn=FALSE
set only_xml_parser=FALSE
set choice=1
path ..\..\tools;..\..\..\tools;..\..\..\Tools\MSYS\bin;..\..\..\..\Tools\MSYS\bin;..\..\Tools\MinGW\bin;..\..\..\Tools\MinGW\bin;..\debug;.\debug;..\..\..\Tools;%path%;
if  not .%1==.  goto set_prj
goto menu

:set_prj
set prj=%1%
rem if not exist .\CustResource\%prj%_MMI\MMI_features_switch%prj%.h goto prj_error
if not exist .\CustResource\%customer%_MMI\MMI_features_switch%customer%.h goto prj_error
goto option

rem ************************************************************
rem ***************** Clean .o and .exe ************************
rem ************************************************************
:clean
if %clean_opt%==FALSE goto a
cd ResGenerator
rem del ..\Res_MMI\*.c
del *.o
del mtk_resgenerator.exe
cd ..

:a
if %remake_opt%==FALSE goto done
cd ResGenerator

echo ----------------------------------------------------------------
echo MediaTek Inc. Resource Generator Script
echo Building resource for %customer%...

rem ************************************************************
rem ****************** Backup Old Resource *********************
rem ************************************************************
echo --------------Copying old Resources for backup-----------------
del /Q ..\custresource\BackupRes\* > nul
if not exist ..\custresource\BackUpRes mkdir ..\custresource\BackUpRes > nul
copy ..\custresource\*.c ..\custresource\BackUpRes\. > nul
echo ------------------------------DONE------------------------------
:skip_backup_res

rem ************************************************************
rem *************** Copy PLUTO Project BASE Files FIRST ********
rem ************************************************************
echo --------------Copying Base file form PLUTO_MMI-----------------
if not exist ..\Res_MMI\ md ..\Res_MMI\
copy ..\custresource\PLUTO_MMI\Res_MMI\*.c ..\Res_MMI\. > nul
copy ..\custresource\PLUTO_MMI\VKV2.vkw ..\resgenerator > nul
copy ..\custresource\PLUTO_MMI\VKV2ResourceGen.exe ..\resgenerator > nul
echo ------------------------------DONE------------------------------

rem ************************************************************
rem *************** Copy Project Related Files *****************
rem ************************************************************
echo -------------Copying Project file form Project folder-------------
if %prj%==PLUTO goto skip_copy_prj
copy ..\custresource\%prj%_MMI\Res_MMI\*.c ..\Res_MMI\. > nul
:skip_copy_prj

if %customer%==PLUTO goto skip_copy_customer
copy ..\custresource\%customer%_MMI\VKV2.vkw ..\resgenerator > nul
copy ..\custresource\%customer%_MMI\VKV2ResourceGen.exe ..\resgenerator > nul
:skip_copy_customer
echo ------------------------------DONE------------------------------

ren ..\Res_MMI\Res_*.* res_*.*

rem ************************************************************
rem *************** Copy MMI_features_switch.h *****************
rem ************************************************************
if %copy_opt%==FALSE goto b
copy ..\custresource\%customer%_MMI\MMI_features_switch%customer%.h ..\..\MMI\Inc\MMI_features_switch.h
:b

rem ************************************************************
rem ************** Start to Generate Resource ******************
rem ************** -Using Pixtel ResGenerator ******************
rem ************************************************************
rem if exist .\debug\*.obj del .\debug\*.obj > nul

if not exist .\temp\ md .\temp\
if not exist .\debug\ md .\debug\
if not exist .\debug\obj md .\debug\obj
if not exist .\..\..\..\build\%2\log\ md .\..\..\..\build\%2\log\


if %only_xml_parser%==TRUE goto skip_VKV2
rem ************************************************************
rem *************** make and run ref_list_merge.exe ************
rem ************************************************************

echo -----------------make and run ref_list_merge.exe----------------
..\..\..\Tools\MSYS\bin\make ref_list_merge.exe
if not exist ref_list_merge.exe goto RESGEN_REF_LIST_MERGE_ERR
ref_list_merge.exe > .\debug\res_gen_run_ref_list.log
IF ERRORLEVEL 2 goto RESGEN_RUN_REF_LIST_MERGE_ERR

rem COPY ..\custresource\%prj%_MMI\ref_list.txt ..\custresource\ref_list.txt
COPY ..\custresource\PLUTO_MMI\ref_list.txt ..\custresource\ref_list.txt
if not exist ..\custresource\ref_list.txt goto RESGEN_REF_LIST_ERR
echo ------------------------------DONE------------------------------
rem ************************************************************
rem *************** make and run plmncreate.exe     ************
rem ************************************************************
if %remake_plmn%==FALSE goto skip_plmn
echo ---------------------make and run plmncreate.exe-----------------
COPY ..\custresource\PLUTO_MMI\plmnlist.txt ..\custresource\plmnlist.txt
COPY ..\custresource\PLUTO_MMI\PlmnEnum.tmp ..\..\MMI\MiscFramework\MiscFrameworkInc\PlmnEnum.h
COPY ..\custresource\PLUTO_MMI\PlmnName.tmp ..\..\Service\NetSetSrv\PlmnName.c

if not exist .\..\..\..\build\%2\log\ md .\..\..\..\build\%2\log\
..\..\..\Tools\MSYS\bin\make plmncreate.exe
if not exist plmncreate.exe goto RESGEN_PLMN_ERR
plmncreate.exe > .\debug\res_gen_run_plmn.log
IF ERRORLEVEL 2 goto RESGEN_RUN_PLMN_ERR
echo ------------------------------DONE------------------------------
:skip_plmn

rem ************************************************************
rem *************** Copy VKV2 Resource               ***********
rem ************************************************************

echo ------------------------Copy VKV2 Resource-------------------
if not exist gui_virtual_keyboard_res.h goto RESGEN_VKV2_ERR_3
if not exist res_virtual_keyboard.c goto RESGEN_VKV2_ERR_4
if not exist VKB.dat goto RESGEN_VKV2_ERR_5
movefile ..\resgenerator\gui_virtual_keyboard_res.h ..\..\Framework\GUI\GUI_INC\gui_virtual_keyboard_res.h
movefile ..\resgenerator\VKB.dat ..\..\Framework\GUI\GUI_INC\VKB.dat
COPY ..\resgenerator\res_virtual_keyboard.c ..\Res_MMI\res_virtual_keyboard.c
echo ------------------------------DONE------------------------------
:skip_VKV2

rem goto jump_resgen_xml
rem ************************************************************
rem *************** make and run resgen_xml.exe ************
rem ************************************************************
:make_resgen_xml
echo -----------------make and run resgen_xml.exe----------------
if not exist .\debug\res md .\debug\res
if not exist .\temp\res md .\temp\res
if not exist .\temp\res_out md .\temp\res_out
if not exist .\temp\res_out\res md .\temp\res_out\res
if not exist .\temp\res_out\CustomerInc md .\temp\res_out\CustomerInc

if exist .\debug\res\*.i del .\debug\res\*.i > nul

echo -----------------make resgen_xml.exe----------------
..\..\..\Tools\MSYS\bin\make resgen_xml.exe 2> .\..\..\..\build\%2\log\resgen_xml_make.log
if not exist resgen_xml.exe goto RESGEN_RESGEN_XML_ERR

echo -----------------resgen_xml.exe -c----------------
resgen_xml.exe -c > .\debug\resgen_xml_copy.log
cd ..\..\..\
if exist tools\mmi_res_check.pl tools\mmi_res_check.pl
cd plutommi\customer\ResGenerator
IF ERRORLEVEL 2 goto RESGEN_COPY_XML_FILES_ERR

rem ************************************************************
rem *************** Run ResGenerator_OP.bat ********************
rem ************************************************************
if %optr_spec%==NONE goto skip_optr
echo -----------------Run Resgenerator_op.bat-----------------
call ..\..\..\%optr_path%\ResGenerator_OP.bat %optr_spec% %main_lcd_size% %touch_panel_support%
echo ------------------------------DONE------------------------------
:skip_optr

echo ----------------- make xml_files ----------------
..\..\..\Tools\MSYS\bin\make xml_files
IF ERRORLEVEL 2 goto RESGEN_BUILD_C_TO_I_ERR

echo -----------------resgen_xml.exe -p----------------
resgen_xml.exe -p > .\debug\resgen_xml.log
IF ERRORLEVEL 2 goto RESGEN_RUN_RESGEN_XML_ERR

:jump_resgen_xml

move .\debug\res\mmi_rp_menu_misc_data.c ..\CustResource\. > nul
copy .\debug\res\mmi_rp_*.c ..\Res_MMI\. > nul
rem copy .\debug\res\mmi_rp_populate.c ..\Res_MMI\. > nul

echo ------------------------------DONE------------------------------

if %only_xml_parser%==TRUE goto jump_old_resgen
rem ************************************************************
rem *************** make and run mtk_resgenerator.exe   ********
rem ************************************************************
echo ---------------make mtk_resgenerator.exe---------------
if not exist .\..\..\..\build\%2\log\ md .\..\..\..\build\%2\log\
..\..\..\Tools\MSYS\bin\make mtk_resgenerator.exe
if not exist mtk_resgenerator.exe goto RESGEN_MAKE_RESGEN_EXE_ERR
echo ------------------------------DONE------------------------------

rem ************************************************************
rem **********  Copy obj files for vendor app  *****************
rem ************************************************************
if exist .\debug\bmp2ems.o COPY .\debug\bmp2ems.o ..\..\VendorApp\ResGenerator\obj\ /y > nul
if exist .\debug\bmpLoader.o COPY .\debug\bmpLoader.o ..\..\VendorApp\ResGenerator\obj\ /y > nul
if exist .\debug\GifLoader.o COPY .\debug\GifLoader.o ..\..\VendorApp\ResGenerator\obj\ /y > nul
if exist .\debug\ResBytestream.o COPY .\debug\ResBytestream.o ..\..\VendorApp\ResGenerator\obj\ /y > nul
if exist .\debug\UCS2.o COPY .\debug\UCS2.o ..\..\VendorApp\ResGenerator\obj\ /y > nul
if exist .\debug\ImageGetDimension.o COPY .\debug\ImageGetDimension.o ..\..\VendorApp\ResGenerator\obj\ /y > nul
if exist .\resgen_xml.exe COPY .\resgen_xml.exe ..\..\VendorApp\ResGenerator\ /y > nul

echo -----------------run mtk_resgenerator.exe---------------
mtk_resgenerator.exe -g -x > .\debug\res_gen_mtk_resgenerator.log
IF ERRORLEVEL 2 goto RESGEN_RUN_RESGEN_EXE_ERR
echo ------------------------------DONE------------------------------

:jump_old_resgen
rem ************************************************************
rem *** Menu Tree Tool gen resource to copy back if needed *****
rem ************************************************************
if exist ..\custresource\CustMenuToolRes.c copy ..\custresource\CustMenuToolRes.c ..\custresource\CustMenuRes.c /y

rem ************************************************************
rem ************** Start to Generate Resource ******************
rem ************************************************************
if exist .\debug\FontRes.o COPY .\debug\FontRes.o ..\..\VendorApp\ResGenerator\obj\ /y
echo -----------------clear intermediate files-----------------
if exist ..\Res_MMI\ rd /S/Q ..\Res_MMI\
if exist .\temp\ rd /S/Q .\temp\

echo -----------Resource generated successfully...-------------

if exist ..\custresource\CustENFBImgData copy ..\custresource\CustENFBImgData ..\..\..\MoDIS_VC9\MoDIS\CustENFBImgData /y
if exist ..\custresource\CustENFBImgData copy ..\custresource\CustENFBStrData ..\..\..\MoDIS_VC9\MoDIS\CustENFBStrData /y

rem ************************************************************
rem Generate the MTE image resource header file.
rem ************************************************************
perl mte_parse_img_usage.pl

rem ************************************************************
rem Generate the MSLT resource header file.
rem ************************************************************
if exist mslt_parse_info.pl perl mslt_parse_info.pl

rem ************************************************************
rem Generate the image_resource_usage.htm
rem ************************************************************
if exist output_image_html.pl output_image_html.pl

echo -----------------ResGenerator_HW Complete!!-----------------
goto done

rem ************************************************************
rem ************** Error Handling and Messages *****************
rem ************************************************************
:RESGEN_REF_LIST_MERGE_ERR
echo Error in ResGenerating Process make merge ref_list.txt error!!
echo Please Check log file res_gen_make_ref_list.txt !! 
exit /B 3

:RESGEN_RUN_REF_LIST_MERGE_ERR
echo Error in ResGenerating run merge ref_list.txt error!!
echo Please Check log file res_gen_run_ref_list.txt !! 
exit /B 3

:RESGEN_REF_LIST_ERR
echo Error in ResGenerating Process ref_list.txt not exist!!
echo Please Check it !! 
exit /B 3

:RESGEN_PLMN_ERR
echo Error in ResGenerating Process make plmn error!!
echo Please Check log file res_gen_make_plmn.txt !!
exit /B 3

:RESGEN_RUN_PLMN_ERR
echo Error in run plmncreate error!!
echo Please Check log file res_gen_run_plmn.txt !!
exit /B 3

:RESGEN_RESGEN_XML_ERR
echo Error in make resgen_xml.exe error!!
echo Please Check log file resgen_xml_make.log !!
exit /B 3

:RESGEN_BUILD_C_TO_I_ERR
echo Error in make .c file to .i file!!
echo Please Check log file resgen_xml_files.log !!
exit /B 3

:RESGEN_COPY_XML_FILES_ERR
echo Error in run resgen_xml to copy files from app folder error!!
echo Please Check log file resgen_xml_copy.log !!
exit /B 3

:RESGEN_RUN_RESGEN_XML_ERR
echo Error in run resgen_xml error!!
echo Please Check log file resgen_xml.log !!
exit /B 3

:RESGEN_MAKE_RESGEN_EXE_ERR
echo Error in ResGenerating Process make mtk_resgenerator.exe!!
echo Please Check log file res_gen.log !!
exit /B 3

:RESGEN_RUN_RESGEN_EXE_ERR
echo Error in ResGenerating Process run mtk_resgenerator.exe!!
echo Please Check log file res_gen_mtk_resgenerator.log !!
exit /B 3

:RESGEN_VKV2_ERR_1
echo Error in ResGenerating Process VK_V2 error1!!
echo Please Check again!!
exit /B 3

:RESGEN_VKV2_ERR_2
echo Error in ResGenerating Process VK_V2 error2!!
echo Please Check again!!
exit /B 3

:RESGEN_VKV2_ERR_3
echo Error in ResGenerating Process VK_V2 error3!!
echo Please Check again!!
exit /B 3

:RESGEN_VKV2_ERR_4
echo Error in ResGenerating Process VK_V2 error4!!
echo Please Check again!!
exit /B 3

:RESGEN_VKV2_ERR_5
echo Error in ResGenerating Process VK_V2 error5!!
echo Please Check again!!
exit /B 3

:RESGEN_VKV2_ERR_6
echo Error in ResGenerating Process VK_V2 error6!!
echo Please Check VKV2ResourceGen.log!!
exit /B 3

rem ************************************************************
rem **************** Menu To Select Project ********************
rem ************************************************************
:menu
@echo off
rem cls
rem echo MediaTek Resource Generator
rem echo. 
rem echo Please select one project to generate resource...
rem echo.
rem echo    SELECT MENU
rem echo    ==========
rem echo.
rem echo    1 - PLUTO
rem echo.
rem echo    Q - Quit
rem choice /C:1Q>nul

rem if errorlevel 23 goto done
rem if errorlevel 1 goto PLUTO:
goto PLUTO:

goto done


:PLUTO
set prj=PLUTO
goto option:


rem ************************************************************
rem **************** Menu To Select Action ********************
rem ************************************************************
:option
@echo off
set opt=
cls
echo MediaTek Resource Generator
echo. 
echo Please select one action to perform...
echo.
echo    SELECT MENU
echo    ==========
echo.
echo    1 - Remake
echo    2 - Clean then remake
echo    3 - Clean
echo    4 - Copy MMI_features_switch%customer%.h, clean, then remake
echo    5 - Plmncreate, copy MMI_features_switch%customer%.h, clean, then remake
echo    6 - Only XML parser (only change ScreenID/other ID only resources)
echo    7 - ReGen Res without log. (only change image/audio files)
echo    8 - ReGen Res with log. (only change image/audio files)
echo.
echo    Q - Quit
rem choice /C:123Q>nul
rem if errorlevel 4 goto done:
rem if errorlevel 3 goto set_clean:
rem if errorlevel 2 goto set_clean_remake:
rem if errorlevel 1 goto set_remake:

set /p choice=Please enter your choice: 
if '%choice%'=='1' goto set_remake
if '%choice%'=='2' goto set_clean_remake
if '%choice%'=='3' goto set_clean
if '%choice%'=='4' goto set_copy_clean_remake
if '%choice%'=='5' goto set_plmn_copy_clean_remake
if '%choice%'=='6' goto set_xml_parser
if '%choice%'=='7' goto set_regen_res
if '%choice%'=='8' goto set_regen_res_log
if '%choice%'=='q' goto done
if '%choice%'=='Q' goto done

goto done

:set_remake
set remake_opt=TRUE
goto clean

:set_clean_remake
set clean_opt=TRUE
set remake_opt=TRUE
goto clean

:set_clean
set clean_opt=TRUE
goto clean

:set_copy_clean_remake
set clean_opt=TRUE
set remake_opt=TRUE
set copy_opt=TRUE
goto clean

:set_plmn_copy_clean_remake
set clean_opt=TRUE
set remake_opt=TRUE
set copy_opt=TRUE
set remake_plmn=TRUE
goto clean

:set_xml_parser
set only_xml_parser=TRUE
set clean_opt=TRUE
set remake_opt=TRUE
set copy_opt=TRUE
set remake_plmn=TRUE
goto clean

:set_regen_res
cd ResGenerator
echo -----------------run mtk_resgenerator.exe---------------
mtk_resgenerator.exe -g -x -r > .\debug\res_gen_mtk_resgenerator.log
IF ERRORLEVEL 2 goto RESGEN_RUN_RESGEN_EXE_ERR
echo ------------------------------DONE------------------------------
goto done

:set_regen_res_log
cd ResGenerator
echo -----------------run mtk_resgenerator.exe---------------
mtk_resgenerator.exe -g -x > .\debug\res_gen_mtk_resgenerator.log
IF ERRORLEVEL 2 goto RESGEN_RUN_RESGEN_EXE_ERR
echo ------------------------------DONE------------------------------
goto done

:prj_error
echo Error!!
echo Project %prj% does not exist!!

:done
cd ..
