@echo off
set prj=
set customer=TOUR
set optr_path=PPP
set optr_spec=NONE
set main_lcd_size=240X320
set touch_panel_support=NONE
set MTK_PROJECT_PATH=%2
set code_gen=FALSE
set remake_resgen=FALSE
set resgen_type=Building
set COMPILER_VER=gcc33
set MMI_IME_VERSION=2

set LOG_PATH=.\..\..\..\build\%MTK_PROJECT_PATH%\log
set LOG_FILE=%LOG_PATH%\resgen.log

rem Pure offline resgen has not been completed so we don't need to build the tool exe here
set remake_offline_resgen=FALSE

if %customer%==MTK set customer=PLUTO

if %COMPILER_VER%==gcc45 goto PATH_SETTING_GCC45:

    rem Normal case

    path ..\..\tools;..\..\..\tools;..\..\..\Tools\MSYS\bin;..\..\..\..\Tools\MSYS\bin;..\..\Tools\MinGW\bin;..\..\..\Tools\MinGW\bin;..\..\..\tools\MinGW\lib\gcc-lib\mingw32\3.3.1;..\debug;.\debug;..\..\..\Tools;%path%;
    set RESGEN_MAKE=..\..\..\Tools\MSYS\bin\make

    goto END_OF_PATH_SETTING:


:PATH_SETTING_GCC45

    rem gcc45 case

    path ..\..\tools;..\..\..\tools;..\..\Tools\MinGW\bin;..\..\..\Tools\MinGW\bin;..\..\..\tools\MinGW\lib\gcc-lib\mingw32\3.3.1;..\debug;.\debug;..\..\..\Tools;%path%;
    set RESGEN_MAKE=..\..\..\Tools\make 

:END_OF_PATH_SETTING


if  not .%1==.  goto a:
goto menu:

:a

rem parsing the parameters form command line
call:sub_parse_parameters %3 %4 %5 %6 %7 %8 %9 

cd plutommi\Customer\ResGenerator

REM Set GCC temp directory
if not exist .\gcctmp mkdir .\gcctmp
if not "%TMPDIR%"=="" (set TMPDIR_ORIGINAL=%TMPDIR%)
if not "%TMP%"=="" (set TMP_ORIGINAL=%TMP%)
if not "%TEMP%"=="" (set TEMP_ORIGINAL=%TEMP%)

set TMPDIR=.\gcctmp
set TMP=.\gcctmp
set TEMP=.\gcctmp

echo ----------------------------------------------------------------
echo MediaTek Inc. Resource Generator Script
echo %resgen_type% resource for %customer%...
echo ******************************************************************************** > %LOG_FILE%
echo **RESGEN_ERROR_NOTIFY_SKIP** >> %LOG_FILE%
echo ******************************************************************************** >> %LOG_FILE%
echo [%date%] >> %LOG_FILE%
echo [%Time%] Resgen [XML] start >> %LOG_FILE%
echo. >> %LOG_FILE%

echo IME Version=[%MMI_IME_VERSION%]


set /a COMPILE_NUM=%NUMBER_OF_PROCESSORS%*2
echo NUMBER_OF_PROCESSORS=[%NUMBER_OF_PROCESSORS%] COMPILE_NUM=[%COMPILE_NUM%]

set TIMELOGFILE=%CD%\xml_time.log
echo [%Time%] start > %TIMELOGFILE%


if .%1==.PLUTO_MMI set prj=PLUTO

REM if exist ..\Res_MMI\ rd /S/Q ..\Res_MMI\
if exist ..\Res_MMI_XML\ rd /S/Q ..\Res_MMI_XML\

rem ************************************************************
rem *************** Log Resgen Tools Version            ********
rem ************************************************************

SET RESGEN_TOOL_VER_LOG_FILE=%LOG_PATH%\resgen_tool_version.log
IF EXIST %RESGEN_TOOL_VER_LOG_FILE% del %RESGEN_TOOL_VER_LOG_FILE% /Q /F

echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
echo * GCC version (Must be 3.3.1) >> %RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
gcc -v>>%RESGEN_TOOL_VER_LOG_FILE% 2>&1
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
echo * MAKE version (Must be 3.79.1)  >> %RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
%RESGEN_MAKE% -version >> %RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
echo * Python version (Must be 2.5.1)>> %RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
..\..\..\tools\python25\python --version>>%RESGEN_TOOL_VER_LOG_FILE% 2>&1
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
echo * Active Perl version (Must be v5.8.6)  >> %RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
perl -version >>%RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
echo * Path Infomation (Please check if there is no other cygwin or mingw runtime)  >>%RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%
echo %path% >>%RESGEN_TOOL_VER_LOG_FILE%
echo ******************************************************************************** >>%RESGEN_TOOL_VER_LOG_FILE%

echo [%Time%] Log tool version>>%TIMELOGFILE%


rem ************************************************************
rem *************** Copy PLUTO Project BASE Files FIRST ********
rem ************************************************************
echo --------------Copying Base file form PLUTO_MMI-----------------
REM if not exist ..\Res_MMI\ md ..\Res_MMI\
if not exist ..\Res_MMI_XML\ md ..\Res_MMI_XML\
REM copy ..\custresource\PLUTO_MMI\Res_MMI\*.c ..\Res_MMI\. > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_camera.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_camcorder.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_video.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_barcodereader.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_mediaplayer.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_bcr.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_mtv_player.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\MMI_features_dtv_player.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_camera_skins.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_camera_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_camcorder_skins.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_camcorder_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_video_skins.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_video_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_vt_skins.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_vt_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_barcodereader_skins.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_barcodereader_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_bcr_skins.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_bcr_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_audply_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_audply_sub_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_fmradio_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_fmradio_sub_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_fmschedulerec_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_world_clock_city.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_mediaplayer_skins.c ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_mediaplayer_skins.h ..\custresource > nul
REM copy ..\custresource\PLUTO_MMI\resource_vdoedt_skins.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_vdoedt_skins.h ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_abrepeat_skins.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_lang_pack_jtbl.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_calc_coordinates.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\IMERes.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_shortcuts.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_aud_eq_values.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_langln_lk_skins.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_sndrec_skins.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\resource_ecompass.c ..\custresource
REM copy ..\custresource\PLUTO_MMI\qwerty_lang_res.c ..\custresource
echo ------------------------------DONE------------------------------


@echo off
rem dir L_*.h /b > font_list_remove.txt
REM dir ..\custresource\L_*.h /b > font_list_remove.txt
REM echo CustMiscData%prj%.c >> font_list_remove.txt
REM echo CustResDef%prj%.h >> font_list_remove.txt
REM echo MMI_features_switch%prj%.h >> font_list_remove.txt
REM echo FontRes.c >> font_list_remove.txt
REM echo ref_list.txt >> font_list_remove.txt
REM echo font_list_remove.txt >> font_list_remove.txt
REM xcopy ..\custresource\%prj%_MMI\*.* ..\custresource\. /Y /EXCLUDE:font_list_remove.txt > nul
REM del font_list_remove.txt /F

rem ************************************************************
rem *************** Copy Project Related Files *****************
rem ************************************************************
echo -------------Copying Project file form Project folder-------------
if %prj%==PLUTO goto skip_copy_prj
REM copy ..\custresource\%prj%_MMI\Res_MMI\*.c ..\Res_MMI\. > nul
:skip_copy_prj

if %customer%==PLUTO goto skip_copy_customer
REM copy ..\custresource\%customer%_MMI\MMI_features_camera.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\MMI_features_camcorder.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\MMI_features_video.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\MMI_features_barcodereader.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\MMI_features_mediaplayer.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\MMI_features_bcr.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\MMI_features_mtv_player.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\MMI_features_dtv_player.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_camera_skins.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_camera_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_camcorder_skins.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_camcorder_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_video_skins.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_video_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_vt_skins.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_vt_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_barcodereader_skins.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_barcodereader_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_bcr_skins.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_bcr_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_audply_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_audply_sub_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_fmradio_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_fmradio_sub_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_fmschedulerec_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_world_clock_city.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_mediaplayer_skins.h ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_mediaplayer_skins.c ..\custresource > nul
REM copy ..\custresource\%customer%_MMI\resource_vdoedt_skins.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_vdoedt_skins.h ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_abrepeat_skins.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_lang_pack_jtbl.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_calc_coordinates.c ..\custresource
REM copy ..\custresource\%customer%_MMI\IMERes.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_shortcuts.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_aud_eq_values.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_langln_lk_skins.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_sndrec_skins.c ..\custresource
REM copy ..\custresource\%customer%_MMI\resource_ecompass.c ..\custresource
REM copy ..\custresource\%customer%_MMI\qwerty_lang_res.c ..\custresource
:skip_copy_customer
echo ------------------------------DONE------------------------------

REM ren ..\Res_MMI\Res_*.* res_*.*

REM movefile ..\custresource\MMI_features_camera.h ..\..\MMI\Inc\MMI_features_camera.h > nul
REM movefile ..\custresource\MMI_features_camcorder.h ..\..\MMI\Inc\MMI_features_camcorder.h > nul
REM movefile ..\custresource\MMI_features_video.h ..\..\MMI\Inc\MMI_features_video.h > nul
REM movefile ..\custresource\MMI_features_mediaplayer.h ..\..\MMI\Inc\MMI_features_mediaplayer.h > nul
REM movefile ..\custresource\MMI_features_barcodereader.h ..\..\MMI\Inc\MMI_features_barcodereader.h > nul
REM movefile ..\custresource\MMI_features_bcr.h ..\..\MMI\Inc\MMI_features_bcr.h > nul
REM movefile ..\custresource\MMI_features_mtv_player.h ..\..\MMI\Inc\MMI_features_mtv_player.h > nul
REM movefile ..\custresource\MMI_features_dtv_player.h ..\..\MMI\Inc\MMI_features_dtv_player.h > nul
REM movefile ..\custresource\resource_camera_skins.h ..\..\MMI\Inc\resource_camera_skins.h > nul
REM movefile ..\custresource\resource_camcorder_skins.h ..\..\MMI\Inc\resource_camcorder_skins.h > nul
REM movefile ..\custresource\resource_video_skins.h ..\..\MMI\Inc\resource_video_skins.h > nul
REM movefile ..\custresource\resource_vt_skins.h ..\..\MMI\Inc\resource_vt_skins.h > nul
REM movefile ..\custresource\resource_bcr_skins.h ..\..\MMI\Inc\resource_bcr_skins.h > nul
REM movefile ..\custresource\resource_barcodereader_skins.h ..\..\MMI\Inc\resource_barcodereader_skins.h > nul
REM movefile ..\custresource\resource_mediaplayer_skins.h ..\..\MMI\Inc\resource_mediaplayer_skins.h > nul
REM movefile ..\custresource\PLUTO_MMI\resource_vdoedt_skins.h ..\..\MMI\Inc\resource_vdoedt_skins.h > nul

echo [%Time%] Copied files >> %TIMELOGFILE%

rem ************************************************************
rem ************** Start to Generate Resource ******************
rem ************** -Using Pixtel ResGenerator ******************
rem ************************************************************
rem goto skip_del_obj
if exist ..\..\customer\custresource\ref_list.txt del ..\..\customer\custresource\ref_list.txt > nul

if exist .\temp\ rd /S/Q .\temp\ >nul
if exist .\debug\ rd /S/Q .\debug\ >nul
if exist .\resgen_pch.h.gch del .\resgen_pch.h.gch >nul

if %remake_resgen%==TRUE goto skip_del_rp_def
if exist ..\CustomerInc\mmi_rp*.* del ..\CustomerInc\mmi_rp*.* > nul

:skip_del_rp_def
if exist .\resgen_xml.exe del .\resgen_xml.exe > nul

:skip_del_obj


if not exist .\temp\ md .\temp\
if not exist .\debug\ md .\debug\
if not exist .\debug\obj md .\debug\obj
if not exist .\debug\dep md .\debug\dep
if not exist .\debug\obj\resgen_xml md .\debug\obj\resgen_xml
if not exist .\debug\obj\mtk_resgenerator md .\debug\obj\mtk_resgenerator
if not exist .\debug\obj\mtk_resgenerator_xml md .\debug\obj\mtk_resgenerator_xml
if not exist .\debug\obj\mtk_resgenerator_core md .\debug\obj\mtk_resgenerator_core
if not exist .\debug\obj\ref_list_merge md .\debug\obj\ref_list_merge
if not exist .\debug\obj\plmncreate md .\debug\obj\plmncreate
if not exist .\debug\obj\font_gen md .\debug\obj\font_gen
if not exist .\debug\dep\resgen md .\debug\dep\resgen
if not exist .\debug\dep\xml_parser md .\debug\dep\xml_parser
if not exist .\debug\dep\common md .\debug\dep\common
if not exist %LOG_PATH%\ md %LOG_PATH%\


rem ************************************************************
rem *************** generate resgen include path ************
rem ************************************************************
echo [Dependency] plutommi\Customer\ResGenerator\Makefile >%LOG_PATH%\resgen_xml_tool.log

echo -----------------generate resgen include path----------------
REM generate ResGenerator\resgen_inc.txt included by Makefile
..\..\..\tools\python25\python .\resgen_gen_inc.py
echo [Dependency] plutommi\Customer\ResGenerator\resgen_gen_inc.py plutommi\Customer\ResGenerator\resgen_default_inc.txt >>%LOG_PATH%\resgen_xml_tool.log

rem ************************************************************
rem ******         Build Resgen LIB and TOOLs           ********
rem ************************************************************
if not exist .\OfflineResGenerator\lib\common md .\OfflineResGenerator\lib\common
if not exist .\OfflineResGenerator\lib\tool md .\OfflineResGenerator\lib\tool
if not exist .\ResgenLog\lib\common md .\ResgenLog\lib\common
if not exist .\ResgenCore\lib\common md .\ResgenCore\lib\common

if NOT %remake_offline_resgen%==TRUE GOTO SKIP_OFFLINE_RESGEN
echo ----------- Build Offline Resgen LIB and TOOLs -----------------
call:sub_run_module "make offline_resgen" "%RESGEN_MAKE% -j%COMPILE_NUM% -fMAKEFILE offline_resgen -k" 1 resgen_ofline_make.log
 if %SUB_MODULE_RET%==FAIL (
    echo Error in stage: [make offline_resgen.exe], check log: [resgen_offline_make.log] !!
    exit 3
)
echo ------------------------------DONE------------------------------
:SKIP_OFFLINE_RESGEN

if %MMI_IME_VERSION%==3 (
		echo ******************************************************************************
		echo 												VKV3 RESGEN START
		echo ******************************************************************************
		cd ResgenVk3
		copy /y ..\..\FontResgen\FontConstTable.txt  .\
		start ..\..\..\..\tools\python25\python vkv3_resgen_main.py
		cd ..
		echo ******************************************************************************
		echo 												VKV3 RESGEN END
		echo ******************************************************************************
)

(
	echo ****************************************************************************** >> handwritingresgen.log
	echo 					Handwriting Data RESGEN START >> handwritingresgen.log
	echo ****************************************************************************** >> handwritingresgen.log
	cd ..\HandwritingResgen
	start ..\..\..\tools\python25\python Hand_writing_main.py >> handwritingresgen.log
	cd ..\ResGenerator
	echo ****************************************************************************** >> handwritingresgen.log
	echo 					Handwriting Data RESGEN END >> handwritingresgen.log
	echo ****************************************************************************** >> handwritingresgen.log
)

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

rem ****************************** make resgen_xml.exe ***************************
call:sub_run_module "make resgen_xml.exe" "%RESGEN_MAKE% -j%COMPILE_NUM% -fMAKEFILE resgen_xml.exe -k" 2 resgen_xml_make.log
if %SUB_MODULE_RET%==FAIL (
    echo Error in stage: [make resgen_xml.exe], check log: [resgen_xml_make.log] !!
    exit 3
)

rem ****************************** copy *.res ***************************
REM call ResGenerator\resgen_xml_copy.pl to copy *.res to ResGenerator\temp\res\*.c
call:sub_run_module "copy *.res" "resgen_xml.exe -c" 1 resgen_xml_copy.log
if %SUB_MODULE_RET%==FAIL (
    set RESGEN_ERR=TRUE
)

echo -----------------mmi_res_check--------------------
echo *************************************************************************** >> %LOG_FILE%
echo [%Time%] mmi_res_check >> %LOG_FILE%
PUSHD ..\..\..\
if exist tools\mmi_res_check.pl perl tools\mmi_res_check.pl
POPD
echo [%Time%] Executed mmi_res_check.pl >> %TIMELOGFILE%
IF ERRORLEVEL 2 (
    call:sub_parse_error mmi_res_check.log
    echo Error in stage: [mmi_res_check], check log: [mmi_res_check.log] !!
    exit 3
) ELSE (
    echo Succeed. >> %LOG_FILE%
)
echo. >> %LOG_FILE%

echo -----------------venus_app_icon_cfg_generator.pl--------------------
echo *************************************************************************** >> %LOG_FILE%
echo [%Time%] venus_app_icon_cfg_generator >> %LOG_FILE%
if exist venus_app_icon_cfg_generator.pl perl venus_app_icon_cfg_generator.pl
echo. >> %LOG_FILE%

rem ************************************************************
rem *************** Run ResGenerator_OP.bat ********************
rem ************************************************************
if %optr_spec%==NONE goto skip_optr
echo -----------------Run Resgenerator_op.bat-----------------
echo *************************************************************************** >> %LOG_FILE%
echo [%Time%] Run ResGenerator_OP.bat >> %LOG_FILE%
call ..\..\..\%optr_path%\ResGenerator_OP.bat %optr_spec% %main_lcd_size% %touch_panel_support%
echo [%Time%] Run ResGenerator_OP.bat >> %TIMELOGFILE%
echo ------------------------------DONE------------------------------
:skip_optr

rem ****************************** pre-process *.res ***************************
REM gcc -E from ResGenerator\temp\res\*.c to ResGenerator\debug\res\*.i
call:sub_run_module "pre-process *.res" "%RESGEN_MAKE% -j%COMPILE_NUM% -fMAKEFILE xml_files -k" 2 resgen_xml_preprocess.log
if %SUB_MODULE_RET%==FAIL (
    set RESGEN_ERR=TRUE
)

rem ****************************** parse *.res ***************************
call:sub_run_module "parse *.res" "resgen_xml.exe -p" 1 resgen_xml_parse.log "error:"
if %SUB_MODULE_RET%==FAIL (
    set RESGEN_ERR=TRUE
)

:jump_resgen_xml

echo -----------------finalizing...--------------------

copy /y .\debug\res\mmi_rp_*.c ..\Res_MMI_XML\. > nul

if exist .\resgen_xml.exe COPY .\resgen_xml.exe ..\..\VendorApp\ResGenerator\ /y > nul

perl ..\..\..\tools\pack_dep_gcc.pl debug\dep\xml_parser.dep debug\dep\xml_parser plutommi\Customer\ResGenerator
perl ..\..\..\tools\pack_dep_gcc.pl debug\dep\common.dep debug\dep\common plutommi\Customer\ResGenerator

echo ******************************************************************************** >> %LOG_FILE%
echo [%Time%] Resgen [XML] end >> %LOG_FILE%
echo. >> %LOG_FILE%
if .%RESGEN_ERR%==.TRUE (
    echo -----------------ResGenerator_XML Fail!!----------------- >> %LOG_FILE%
) ELSE (
    echo -----------------ResGenerator_XML Succeed!!----------------- >> %LOG_FILE%
)
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%

cd ..\..\..\

if .%RESGEN_ERR%==.TRUE (
    echo -----------------ResGenerator_XML Fail!!-----------------
    echo Please check log: [resgen.log]
    exit 3
)

if not "%TMPDIR_ORIGINAL%"=="" (set TMPDIR=%TMPDIR_ORIGINAL%)
if not "%TMP_ORIGINAL%"=="" (set TMP=%TMP_ORIGINAL%)
if not "%TEMP_ORIGINAL%"=="" (set TEMP=%TEMP_ORIGINAL%)

echo -----------------ResGenerator_XML Complete!!-----------------
goto done

rem ************************************************************
rem ************** Error Handling and Messages *****************
rem ************************************************************
:RESGEN_RESGEN_XML_ERR
echo Error in make resgen_xml.exe error!!
echo Please Check log file resgen_xml_make.log !!
exit 3

:RESGEN_BUILD_C_TO_I_ERR
echo Error in make .c file to .i file!!
echo Please Check log file resgen_xml_files.log !!
exit 3

:RESGEN_COPY_XML_FILES_ERR
echo Error in run resgen_xml to copy files from app folder error!!
echo Please Check log file resgen_xml_copy.log !!
exit 3

:RESGEN_RUN_RESGEN_XML_ERR
echo Error in run resgen_xml error!!
echo Please Check log file resgen_xml.log !!
exit 3

rem ************************************************************
rem **************** Parse BAT parameters **********************
rem ************************************************************
:sub_parse_parameters
rem echo Parse BAT parameters: %1 , %2, %3, %4, %5, %6, %7, %8, %9
echo ------------ ResGenerator_XML.bat Parameter Resolving----------------
:BAT_PARAM_PARSING_START
if .%1 == . goto:BAT_PARAM_PARSING_END
echo PARAM: %1
rem parsing the parameter here
if .%1==.R set remake_resgen=TRUE
if .%1==.R set resgen_type=Remake
if .%1==.C set code_gen=TRUE
if .%1==.IMEv3 set MMI_IME_VERSION=3
if .%1==.IMEv2 set MMI_IME_VERSION=2
shift
goto:BAT_PARAM_PARSING_START
:BAT_PARAM_PARSING_END
echo ---------------------------------------------------------------------
goto:eof

rem ***************************************************************************
rem *** run Sub module
rem *** %1 = submodule description
rem *** %2 = command line
rem *** %3 = error direction (1 or 2)
rem *** %4 = log filename
rem *** %5 = log pattern
:sub_run_module
echo -----------------%~1----------------
echo *************************************************************************** >> %LOG_FILE%
echo [%Time%] %~1 >> %LOG_FILE%

%~2 %3> %LOG_PATH%\%~4

echo [%Time%] Executed %~1 >> %TIMELOGFILE%
IF ERRORLEVEL 2 (
    echo Failed!! [%ERRORLEVEL%] >> %LOG_FILE%
    call:sub_parse_error %~4 %~5
    set SUB_MODULE_RET=FAIL
) ELSE (
    echo Succeed. [%ERRORLEVEL%][%Time%] >> %LOG_FILE%
    set SUB_MODULE_RET=OK
)
echo. >> %LOG_FILE%
goto:eof

rem ************************************************************
rem **************** Parse Error function **********************
rem ************************************************************
:sub_parse_error
echo log = [%1], error summarized: >> %LOG_FILE%
echo. >> %LOG_FILE%

IF .%2==. (
    FINDSTR /I /N /R "\<error\>" %LOG_PATH%\%1 > ~tmp.str
) ELSE (
    FINDSTR /I /N /R "\<%2\>" %LOG_PATH%\%1 > ~tmp.str
)
type ~tmp.str >> %LOG_FILE%
del ~tmp.str
goto:eof

rem ************************************************************
rem **************** Menu To Select Project ********************
rem ************************************************************
:menu
@echo off
rem cls
rem echo MediaTek Resource Generator XML
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
goto a:

:done
