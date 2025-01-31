/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2010
*
*  BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
*  THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
*  RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON
*  AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
*  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
*  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
*  NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
*  SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
*  SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH
*  THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
*  NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S
*  SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
*  BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
*  LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
*  AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
*  OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY BUYER TO
*  MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
*  THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
*  WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF
*  LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING THEREOF AND
*  RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN FRANCISCO, CA, UNDER
*  THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE (ICC).
*
*****************************************************************************/
/*****************************************************************************
 *
 * Filename:
 * ---------
 *  DialerMain.c
 *
 * Project:
 * --------
 *  MAUI
 *
 * Description:
 * ------------
 *  This file implements the dialer application.
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 * removed!
 * removed!
 * removed!
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

/****************************************************************************
 * Include
 ****************************************************************************/

#include "MMIDataType.h"
#include "DialerCuiGprot.h"
#include "DialerGprot.h"
#include "DialerMain.h"
#include "mmi_common_app_trc.h"
#include "MMI_common_app_trc.h"
#include "custom_phb_config.h"
#include "kal_general_types.h"
#include "Unicodexdcl.h"
#include "kal_public_api.h"
#include "DebugInitDef_Int.h"
#include "GlobalResDef.h"
#include "mmi_frm_scenario_gprot.h"
#include "AlertScreen.h"
#include "wgui_categories_util.h"
#include "mmi_frm_events_gprot.h"
#include "BootupSrvGprot.h"
#include "IdleGprot.h"
#include "mmi_rp_app_dialer_def.h"
#include "gui_effect_oem.h"
#ifdef __OP01_FWPBW__
#include "gpioSrvGprot.h"
#include "ucmsrvGprot.h"
#include "phonebookgprot.h"
#include "callsetSrvGprot.h"
#include "ShutdownSrvGprot.h"
#endif

/****************************************************************************
 * Function
 ****************************************************************************/

/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_handle_dialer_close_req
 * DESCRIPTION
 *  This function handles the close request.
 * PARAMETERS
 *  event               : [IN]          Event
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
static mmi_ret mmi_dialer_handle_dialer_close_req(mmi_event_struct *event)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    cui_dialer_close_req_evt_struct *p;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_HANDLE_DIALER_CLOSE_REQ, 200));

    p = (cui_dialer_close_req_evt_struct *)event;

    cui_dialer_close(p->sender_id);

    return MMI_RET_OK;
}

void mmi_dialer_entry_dummy_scrn(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/	

	if (mmi_frm_scrn_enter(SCR_ID_DUMMY, SCR_ID_DUMMY, (FuncPtr)NULL, (FuncPtr)mmi_dialer_entry_dummy_scrn, MMI_FRM_FULL_SCRN))
    {    
		mmi_frm_scrn_clear_attribute(SCR_ID_DUMMY, SCR_ID_DUMMY, MMI_SCRN_ATTRIB_ADD_HISTORY);
        ShowCategoryDummyScreen();
		gui_sse_set_is_dummy_screen(MMI_FALSE);
    }
}

/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_handle_dialer_change_type
 * DESCRIPTION
 *  This function handles the dialer change type event.
 * PARAMETERS
 *  event               : [IN]          Event
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_handle_dialer_change_type(mmi_event_struct *event)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    cui_dialer_change_type_evt_struct *p;
    WCHAR dial_string[CUI_DIALER_MAX_DIAL_BUF_SIZE];

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_HANDLE_DIALER_CHANGE_TYPE, 200));

    p = (cui_dialer_change_type_evt_struct *)event;

	mmi_frm_group_create_ex(GRP_ID_ROOT, SCR_ID_DUMMY, NULL, NULL, MMI_FRM_NODE_SMART_CLOSE_FLAG);
	mmi_dialer_entry_dummy_scrn();

    mmi_wcsncpy(
        dial_string,
        cui_dialer_get_dial_string(p->sender_id),
        CUI_DIALER_MAX_DIAL_STR_LEN);

    cui_dialer_close(p->sender_id);

    if (p->new_type != CUI_DIALER_TYPE_VOIP &&
        p->old_type != CUI_DIALER_TYPE_VOIP)
    {
        mmi_dialer_launch_by_string_ex(p->new_type, dial_string);
    }
    else
    {
        mmi_dialer_launch_ex(p->new_type);
    }

    return MMI_RET_OK;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_main_evt_hdlr
 * DESCRIPTION
 *  This function is the event handler of the dialer CUI.
 * PARAMETERS
 *  event               : [IN]          Event
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_main_evt_hdlr(mmi_event_struct *event)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ret ret;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    switch (event->evt_id)
    {
        case EVT_ID_CUI_DIALER_CLOSE_REQ:
            ret = mmi_dialer_handle_dialer_close_req(event);
            break;

        case EVT_ID_CUI_DIALER_CHANGE_TYPE:
            ret = mmi_dialer_handle_dialer_change_type(event);
            break;

        default:
            ret = MMI_RET_OK;
            break;
    }

    return ret;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_instance_create
 * DESCRIPTION
 *  This function creates a dialer instance.
 * PARAMETERS
 *  type                : [IN]          Type
 *  proc                : [IN]          Proc function
 *  grp_id              : [OUT]         Group ID
 *  cui_id              : [OUT]         CUI ID
 * RETURNS
 *  void
 *****************************************************************************/
static MMI_BOOL mmi_dialer_instance_create(
    cui_dialer_type_enum type,
    mmi_proc_func proc,
    mmi_id *grp_id,
    mmi_id *cui_id)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_id gid, cid;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
	if(mmi_frm_group_is_present(GRP_ID_DIALER_MAIN))
	{
		mmi_frm_group_close(GRP_ID_DIALER_MAIN);
	}

	
    MMI_DIALER_LOG((TRC_MMI_DIALER_INSTANCE_CREATE, 100));

	gid = mmi_frm_group_create_ex(GRP_ID_ROOT, GRP_ID_DIALER_MAIN, proc, NULL, MMI_FRM_NODE_SMART_CLOSE_FLAG);

    MMI_ASSERT(gid != GRP_ID_INVALID);

    cid = cui_dialer_create_ex(gid, type);

    if (cid == GRP_ID_INVALID)
    {
        MMI_DIALER_LOG((TRC_MMI_DIALER_INSTANCE_CREATE, 600));

        mmi_popup_display_simple(
            (WCHAR *)get_string(STR_GLOBAL_NOT_AVAILABLE),
            MMI_EVENT_FAILURE,
            gid,
            NULL);

        return MMI_FALSE;
    }

    MMI_DIALER_LOG((TRC_MMI_DIALER_INSTANCE_CREATE, 200));

    if (grp_id)
    {
        *grp_id = gid;
    }

    if (cui_id)
    {
        *cui_id = cid;
    }

    return MMI_TRUE;
}


/* For the detail information, please refer to the DialerGprot.h */
void mmi_dialer_launch(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH, 200));

    mmi_dialer_launch_ex(CUI_DIALER_TYPE_UNSPECIFIED);
}


/* For the detail information, please refer to the DialerGprot.h */
mmi_id mmi_dialer_launch_ex(cui_dialer_type_enum type)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_id grp_id, cui_id;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH_EX, 200, type));

    if (!mmi_dialer_instance_create(
            type,
            mmi_dialer_main_evt_hdlr,
            &grp_id,
            &cui_id))
    {
        return GRP_ID_INVALID;
    }

    cui_dialer_run(cui_id);

    return grp_id;
}


/* For the detail information, please refer to the DialerGprot.h */
void mmi_dialer_launch_by_string(const WCHAR *dial_string)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH_BY_STRING, 200));

    mmi_dialer_launch_by_string_ex(CUI_DIALER_TYPE_UNSPECIFIED, dial_string);
}


/* For the detail information, please refer to the DialerGprot.h */
mmi_id mmi_dialer_launch_by_string_ex(
    cui_dialer_type_enum type,
    const WCHAR *dial_string)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_id grp_id, cui_id;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH_BY_STRING_EX, 200, type));

    if (!mmi_dialer_instance_create(
            type,
            mmi_dialer_main_evt_hdlr,
            &grp_id,
            &cui_id))
    {
        return GRP_ID_INVALID;
    }

    cui_dialer_set_dial_string(cui_id, dial_string);

    cui_dialer_run(cui_id);

    return grp_id;
}


/* For the detail information, please refer to the DialerGprot.h */
void mmi_dialer_launch_by_key(U16 key_code)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH_BY_KEY, 200));

    mmi_dialer_launch_by_key_ex(CUI_DIALER_TYPE_UNSPECIFIED, key_code);
}


/* For the detail information, please refer to the DialerGprot.h */
mmi_id mmi_dialer_launch_by_key_ex(cui_dialer_type_enum type, U16 key_code)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_id grp_id, cui_id;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH_BY_KEY_EX, 200, type));

    if (!mmi_dialer_instance_create(
            type,
            mmi_dialer_main_evt_hdlr,
            &grp_id,
            &cui_id))
    {
        return GRP_ID_INVALID;
    }

    cui_dialer_set_key(cui_id, key_code);

    cui_dialer_run(cui_id);

    return grp_id;
}


/* For the detail information, please refer to the DialerGprot.h */
void mmi_dialer_launch_by_translate_key(
    S16 key_code,
    S16 key_type,
    U16 ucs2_value,
    U32 key_flag)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH_BY_TRANSLATE_KEY, 200));

    mmi_dialer_launch_by_translate_key_ex(
            CUI_DIALER_TYPE_UNSPECIFIED,
            key_code,
            key_type,
            ucs2_value,
            key_flag);
}


/* For the detail information, please refer to the DialerGprot.h */
mmi_id mmi_dialer_launch_by_translate_key_ex(
    cui_dialer_type_enum type,
    S16 key_code,
    S16 key_type,
    U16 ucs2_value,
    U32 key_flag)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_id grp_id, cui_id;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_LAUNCH_BY_TRANSLATE_KEY_EX, 200, type));

    if (!mmi_dialer_instance_create(
            type,
            mmi_dialer_main_evt_hdlr,
            &grp_id,
            &cui_id))
    {
        return GRP_ID_INVALID;
    }

    cui_dialer_set_translate_key(cui_id, key_code, key_type, ucs2_value, key_flag);

    cui_dialer_run(cui_id);

    return grp_id;
}

/* For the detail information, please refer to the DialerGprot.h */
MMI_BOOL mmi_dialer_is_active(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    MMI_DIALER_LOG((TRC_MMI_DIALER_IS_ACTIVE, 200, cui_dialer_is_active_if_any));

    return cui_dialer_is_active_if_any();
}


/* For the detail information, please refer to the DialerGprot.h */
const WCHAR *mmi_dialer_get_dial_string(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_GET_DIAL_STRING, 200));

    return cui_dialer_get_dial_string_if_any();
}


#if defined(__MMI_DIALER_SEARCH__)
/* For the detail information, please refer to the DialerGprot.h */
MMI_BOOL mmi_dialer_search_is_enable(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    MMI_DIALER_LOG((TRC_MMI_DIALER_SEARCH_IS_ENABLE, 200, cui_dialer_search_is_enable()));

    return cui_dialer_search_is_enable();
}


/* For the detail information, please refer to the DialerGprot.h */
void mmi_dialer_search_set_enable(MMI_BOOL is_enable)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_SET_ENABLE, 200, is_enable));

    cui_dialer_search_set_enable(is_enable);
}


/* For the detail information, please refer to the DialerGprot.h */
void mmi_dialer_search_entry_setting(MMI_ID group_id)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_DIALER_LOG((TRC_MMI_DIALER_ENTRY_SETTING, 200));

    cui_dialer_search_entry_setting(group_id);
}
#endif /* defined(__MMI_DIALER_SEARCH__) */


#ifdef  __GENERAL_TTS__

/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_do_voice_tone_hdlr
 * DESCRIPTION
 *  This function is to read keypad for customer.
 * PARAMETERS
 *  mmi_event_struct:     [IN] Event structure passed by callback manager
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_do_voice_tone_hdlr(mmi_event_struct *event)
{

    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_frm_key_evt_struct *key_evt = (mmi_frm_key_evt_struct *)event;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    if ((((key_evt->key_code == KEY_STAR)||
		(key_evt->key_code >= KEY_0 && key_evt->key_code <= KEY_9)) && 
        (KEY_EVENT_DOWN == key_evt->key_type || KEY_REPEAT == key_evt->key_type))||
        ((key_evt->key_code == KEY_POUND) && (KEY_EVENT_DOWN == key_evt->key_type)))
    {
        if(cui_dialer_is_active_if_any() && cui_dialer_is_tts_enable())
        {
			cui_dialer_do_tts_report();
        }
    }

    return MMI_RET_OK;
}

#endif /* ifdef  __GENERAL_TTS__ */


#ifdef __OP01_FWPBW__

/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_shutdown_hdlr
 * DESCRIPTION
 *  This function is to reset black list when shut down the bwt.
 * PARAMETERS
 *  mmi_event_struct:     [IN] Event structure passed by callback manager
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_shutdown_hdlr(mmi_event_struct* evt)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
	
	cui_dialer_bwt_close();

	return MMI_RET_OK;
}
/*****************************************************************************
 * FUNCTION
 *  mmi_ucm_fwp_hook_key_hdlr
 * DESCRIPTION
 *  This function is to handle the hook key () sent from GPIO
 * PARAMETERS
 *  mmi_event_struct:     [IN] Event structure passed by callback manager
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_gpio_transmitter_hdlr(mmi_event_struct* evt)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 audio_mode = mdi_audio_get_audio_mode();

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (srv_bootup_get_booting_mode() != SRV_BOOTUP_MODE_NORMAL 
        || srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_NO_CSD, NULL)
        || !srv_bootup_is_completed())
    {
        return MMI_RET_OK;
    }
    
    if (EVT_ID_GPIO_TRANSMITTER_HOLD_ON == evt->evt_id && audio_mode != AUD_MODE_LOUDSPK)
        {
            mmi_idle_display();
            mmi_dialer_launch();
        }
    if(EVT_ID_GPIO_TRANSMITTER_HOLD_ON == evt->evt_id && audio_mode == AUD_MODE_LOUDSPK)
    {
	    srv_speech_disable_hand_free();				
    }
    if(EVT_ID_GPIO_TRANSMITTER_PUT_DOWN == evt->evt_id )
    {
    	srv_speech_disable_hand_free();	
        cui_dialer_bwt_close();
		mmi_idle_display();
    }
    else
    {
        return MMI_RET_DONT_CARE;
    }

    return MMI_RET_OK;
}

/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_handfree_process
 * DESCRIPTION
 *  handfree key handle
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
static void mmi_dialer_handfree_process(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    U8 audio_mode = mdi_audio_get_audio_mode();
    MMI_BOOL hold_on = srv_gpio_transmitter_is_hold_on();  /* hook on means guaji*/
    
    
    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_NO_CSD, NULL))
    {
        return;
    }

    MMI_PRINT(MOD_MMI_COMMON_APP, MMI_PHB_TRACE_GROUP,"mmi_dialer_handfree_process: %d", audio_mode);

    if (audio_mode == AUD_MODE_LOUDSPK)
    {
        srv_speech_disable_hand_free();
        if (hold_on == MMI_FALSE)
        {
            cui_dialer_bwt_close();
			mmi_idle_display();
        }
    }
    else
    {
        srv_speech_enable_hand_free();
        if (hold_on == MMI_FALSE)
        {
            mmi_idle_display();
            mmi_dialer_launch();
        }
    }
}


/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_handfree_key_hdlr
 * DESCRIPTION
 *  handfree key handle
 * PARAMETERS
 *  void
 * RETURNS
 *  MMI_RET_OK to continue key routing, MMI_RET_STOP_KEY_HANDLE to stop
 *  key routing
 *****************************************************************************/
mmi_ret mmi_dialer_handfree_key_hdlr(mmi_event_struct *evt)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/    
    mmi_frm_key_evt_struct *key_evt = (mmi_frm_key_evt_struct *)evt;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/    

    if (srv_bootup_get_booting_mode() != SRV_BOOTUP_MODE_NORMAL
        || !srv_bootup_is_completed())
    {
        return MMI_RET_OK;
    }

    if (KEY_F9 == key_evt->key_code && KEY_EVENT_DOWN == key_evt->key_type)
    {
        mmi_dialer_handfree_process();
        return MMI_RET_OK;
    }

    return MMI_RET_OK;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_evt_hdlr
 * DESCRIPTION
 *  This function is the main event handler of screen locker.
 * PARAMETERS
 *  event           : [IN]      Event
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_idle_launched_hdlr(mmi_event_struct *event)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ret ret;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

	if (srv_ucm_query_call_count(SRV_UCM_CALL_STATE_ALL, SRV_UCM_CALL_TYPE_NO_CSD, NULL))
    {
        return;
    }
	
    srv_callset_blacklist_switch_mode(SRV_CALLSET_BLACKLIST_OFF, MMI_TRUE, NULL);

    if (srv_gpio_transmitter_is_hold_on())
    {
    	if(!cui_dialer_is_active_if_any())
    	{
    	    srv_speech_disable_hand_free();
            mmi_idle_display();
            mmi_dialer_launch();
        }
    }
    return MMI_RET_OK;
}

/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_stop_tone_hdlr
 * DESCRIPTION
 *  This function is to stop dialertone before keytone.
 * PARAMETERS
 *  event           : [IN]      Event
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_stop_tone_hdlr(mmi_event_struct *event)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_frm_key_evt_struct *key_evt = (mmi_frm_key_evt_struct *)event;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

    //if ((key_evt->key_code == KEY_STAR)||(key_evt->key_code == KEY_POUND)||
        //(key_evt->key_code >= KEY_0 && key_evt->key_code <= KEY_9) && KEY_EVENT_DOWN == key_evt->key_type)
    if (KEY_EVENT_DOWN == key_evt->key_type)    
    {
        if(cui_dialer_is_active_if_any())
        {
			srv_prof_stop_tone(SRV_PROF_TONE_DIALER);
	    	srv_prof_stop_tone(SRV_PROF_TONE_GSM_BUSY);
        }
    }

    return MMI_RET_OK;
}


/*****************************************************************************
 * FUNCTION
 *  mmi_dialer_evt_hdlr
 * DESCRIPTION
 *  This function is the main event handler of screen locker.
 * PARAMETERS
 *  event           : [IN]      Event
 * RETURNS
 *  mmi_ret
 *****************************************************************************/
mmi_ret mmi_dialer_evt_hdlr(mmi_event_struct *event)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    mmi_ret ret;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    MMI_ASSERT(event);

    switch (event->evt_id)
    {
	    case EVT_ID_IDLE_ENTER:
            ret = mmi_dialer_idle_launched_hdlr(event);
            break;

        case EVT_ID_GPIO_TRANSMITTER_HOLD_ON:
        case EVT_ID_GPIO_TRANSMITTER_PUT_DOWN:
            ret = mmi_dialer_gpio_transmitter_hdlr(event);
            break;

        case EVT_ID_PRE_KEY_EVT_ROUTING:
            ret = mmi_dialer_handfree_key_hdlr(event);
            break;
			
		case EVT_ID_SRV_SHUTDOWN_DEINIT:
			ret = mmi_dialer_shutdown_hdlr(event);
            break;

        default:
            ret = MMI_RET_OK;
            break;
    }

    return ret;
}

#endif

