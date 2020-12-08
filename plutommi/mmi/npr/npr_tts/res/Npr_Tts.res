////////////////////////////////////////////////////////////////////
// file name: Npr_Tts.res
//hyc 2012/4/11
////////////////////////////////////////////////////////////////////

#ifdef __NPR_TTS_UI__
/* Needed header files of the compile option in XML files, if you need others need to add here */
#include "mmi_features.h"
#include "custresdef.h"

/* Need this line to tell parser that XML start, must after all #include. */
<?xml version="1.0" encoding="UTF-8"?>

/* APP tag, include your app name defined in MMIDataType.h */
//<APP id="APP_NPR_TTS">

<APP id = "APP_NPR_TTS"
#if defined(__MMI_APP_MANAGER_SUPPORT__)
     package_name = "native.mtk.nprtts"            
     name = "@OID:STR_ID_TTS_SETTING_MENU_TEXT"                  
     img = "IMG_ID_TTS_SETTING_MENU_ICON"
     launch = "NPR_TTS_EntryMainScreen"              
#else /*__MMI_APP_MANAGER_SUPPORT__*/
	name = "@OID:STR_ID_TTS_SETTING_MENU_TEXT" 
#endif
>


    /* When you use any ID of other module, you need to add
       that header file here, so that Resgen can find the ID */
    <!--Include Area-->

    <!-----------------------------------------------------String Resource Area----------------------------------------------------->
    /* String ID of you Application, we will get string from ref_list.txt for all languages */
    <STRING id="STR_ID_NPR_TTS_MENU1"/>//��������
    <STRING id="STR_ID_NPR_TTS_MENU2"/>//��������
    <STRING id="STR_ID_NPR_TTS_ABOUT"/>      
    <STRING id="STR_ID_NPR_TTS_ABOUT_INFO"/>      
    <STRING id="STR_ID_NPR_TTS_VOL"/>   
    <STRING id="STR_ID_NPR_TTS_SMS_NOTICE"/>

    <STRING id="STR_ID_TTS_SETTING_MENU_TEXT"/>  //����������
    <STRING id="STR_ID_TTS_MENU_READ"/>		     //�˵��ʶ�
    <STRING id="STR_ID_TTS_INCOMING_CALL_READ"/> //���籨��
    <STRING id="STR_ID_TTS_KEYPAD_READ"/>              //��������
    <STRING id="STR_ID_TTS_TIME_READ_SET"/>            //������ʱ
    <STRING id="STR_ID_TTS_VOICE_SEL"/>			//����ѡ��
    <STRING id="STR_ID_TTS_VOL_SET"/>				//��������
    <STRING id="STR_ID_TTS_ABOUT"/>				//����
    <STRING id="STR_ID_TTS_TIME_READ_AUTO"/>        //�Զ���ʱ
    <STRING id="STR_ID_TTS_TIME_READ_HAND"/>		//�ֶ���ʱ
    
    <STRING id="STR_ID_TTS_SMS_READ_SET"/>		//���Ų���
    
    <STRING id="STR_ID_TTS_SMS_RECV_READ"/>          //���ŵ��ﲥ��
    
    <STRING id="STR_ID_TTS_SMS_AUTO_READ"/>         //�����Զ�����
    
    <STRING id="STR_ID_TTS_TIME_READ_TIPS"/>    	//TIPS
    <STRING id="STR_ID_TTS_ABOUT_INFO"/>                //�������˵��


    <STRING id="STR_ID_TTS_FEMALE"/>				//��׼Ů��
    <STRING id="STR_ID_TTS_GD"/>					//�㶫����
    <STRING id="STR_ID_TTS_SC"/>					//�Ĵ�����
    <STRING id="STR_ID_TTS_DB"/>					//��������			       
    <STRING id="STR_ID_TTS_MALE"/>				// �������
    <STRING id="STR_ID_TTS_CHILDREN"/>			//�ɰ�ͯ��

    <STRING id="STR_ID_NPR_INSERT_SIM_CARD"/>    //�����SIM��
    <STRING id="STR_ID_NPR_INVALID_SIM_CARD"/>  //��ЧSIM��
    <STRING id="STR_ID_NPR_NET_NOT_INITED"/>     
    <STRING id="STR_ID_NPR_INSERT_T_CARD"/>


    <STRING id="STR_ID_NPR_TTS_SET_SIM"/>
    <STRING id="STR_ID_NPR_TTS_RESOURCES_DOWN"/>


    <!-----------------------------------------------------Image Resource Area------------------------------------------------------>
    /* Image Id and path of you Application , you can use compile option in Path, but need out of "" */
    <IMAGE id="IMG_ID_TTS_SETTING_MENU_ICON">"..\\\\..\\\\mmi\\\\npr\\\\npr_tts\\\\res\\\\icon\\\\tts_menu.png"</IMAGE>
    
    <IMAGE id="IMG_ID_NPR_TTS_MENU1">CUST_IMG_PATH"\\\\MainLCD\\\\NPR\\\\npr_Aitalk\\\\menu1.gif"</IMAGE>
    <IMAGE id="IMG_ID_NPR_TTS_MENU2">CUST_IMG_PATH"\\\\MainLCD\\\\NPR\\\\npr_Aitalk\\\\menu2.gif"</IMAGE>

    <SCREEN id="SCR_ID_TTS_SETTING_MIAN"/>
    <SCREEN id="SCR_ID_TTS_ABOUT"/>
    <SCREEN id="SCR_ID_TTS_VOLUME_SET"/>

    <SCREEN id="SCR_ID_TTS_VOICE_SEL"/>
    <SCREEN id="SCR_ID_TTS_SMS_READ_SET"/>
    <SCREEN id="SCR_ID_TTS_TIME_READ_SET"/>

    <!------------------------------------------------------Menu Resource Area------------------------------------------------------>
    /* Only MENUITEM need compile option, MENUITEM_ID does not need */
    <!--Menu Tree Area-->

    <MENU id="MENU_ID_TTS_SETTING" str="STR_ID_TTS_SETTING_MENU_TEXT" img="IMG_ID_TTS_SETTING_MENU_ICON"  highlight="NPR_TTS_MainScreenHighlight">
    <MENUITEM_ID>@OID:MENU_ID_TTS_MENU_READ</MENUITEM_ID>

    <MENUITEM_ID>@OID:MENU_ID_TTS_INCOMING_CALL_READ</MENUITEM_ID>
    <MENUITEM_ID>@OID:MENU_ID_TTS_SMS_READ_SET</MENUITEM_ID>    
    <MENUITEM_ID>@OID:MENU_ID_TTS_KEYPAD_READ</MENUITEM_ID>  
    <MENUITEM_ID>@OID:MENU_ID_TTS_VOL_SET</MENUITEM_ID>

    
	
    <MENUITEM_ID>@OID:MENU_ID_TTS_ABOUT</MENUITEM_ID>
    </MENU>


    <MENU id="MENU_ID_TTS_MENU_READ" str="STR_ID_TTS_MENU_READ" img="NULL"  hint = "NPR_TTS_MenuStatus_Hint"  highlight="NPR_TTS_MenuScrenHighlight"/>
    <MENU id="MENU_ID_TTS_INCOMING_CALL_READ" str="STR_ID_TTS_INCOMING_CALL_READ" img="NULL"  hint = "NPR_TTS_IncomingCallHint"  highlight="NPR_TTS_IncomingCallHighlight"/>
    <MENU id="MENU_ID_TTS_KEYPAD_READ" str="STR_ID_TTS_KEYPAD_READ" img="NULL"  hint = "NPR_TTS_KeyplayHint"  highlight="NPR_TTS_KeyplayHighlight"/>         
    <MENU id="MENU_ID_TTS_ABOUT" str="STR_ID_TTS_ABOUT" img="NULL"   highlight="NPR_TTS_AboutScreenHighlight"/>
    <MENU id="MENU_ID_TTS_VOL_SET" str="STR_ID_TTS_VOL_SET" img="NULL"   highlight="NPR_TTS_VolumeScreenHighlight"/>


	


    <MENU id="MENU_ID_TTS_SMS_READ_SET" str="STR_ID_TTS_SMS_READ_SET" img="NULL"  highlight="NPR_TTS_SmsReadSetingHighlight">
    <MENUITEM_ID>@OID:MENU_ID_TTS_SMS_RECV_READ</MENUITEM_ID>
    <MENUITEM_ID>@OID:MENU_ID_TTS_SMS_AUTO_READ</MENUITEM_ID>    
    </MENU>

    <MENU id="MENU_ID_TTS_SMS_RECV_READ" str="STR_ID_TTS_SMS_RECV_READ" img="NULL"  hint = "NPR_TTS_SmsRecvHint"  highlight="NPR_TTS_SmsRecvHighlight"/>
    <MENU id="MENU_ID_TTS_SMS_AUTO_READ" str="STR_ID_TTS_SMS_AUTO_READ" img="NULL"  hint = "NPR_TTS_SmsAutoReadHint"  highlight="NPR_TTS_SmsAutoHighlight"/>



    <!------------------------------------------------------MMI Cache Resource---------------------------------------------------------->    
    <CACHEDATA type="byte" id="NVRAM_NPR_TTS_FLAG" restore_flag="TRUE">
        <DEFAULT_VALUE> [0XFF] </DEFAULT_VALUE>
        <DESCRIPTION> TTS Play nvram </DESCRIPTION>
    </CACHEDATA>
    
   <CACHEDATA type="byte" id="NVRAM_TTS_VOL_LEVEL" restore_flag="TRUE">
        <DEFAULT_VALUE> [0XFF] </DEFAULT_VALUE>
        <DESCRIPTION> TTS Auto Play Time </DESCRIPTION>
    </CACHEDATA>

    <CACHEDATA type="byte" id="NVRAM_TTS_VOICE_SEL" restore_flag="TRUE">
        <DEFAULT_VALUE> [0XFF] </DEFAULT_VALUE>
        <DESCRIPTION> TTS volume selet </DESCRIPTION>
    </CACHEDATA>




</APP>
#endif

