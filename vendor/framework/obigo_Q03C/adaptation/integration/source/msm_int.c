#ifdef Q03C_IND_MOD_ARCH_SUPPORT
/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2005
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

/*******************************************************************************
 *
 * Filename:
 * ---------
 * msm_int.c
 *
 * Project:
 * --------
 *   MAUI
 *
 * Description:
 * ------------
 *   This file is intends for adapter functions of Mobile Suite Manager
 *
 * Author:
 * -------
 * -------
 *
 *==============================================================================
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
 *==============================================================================
 *******************************************************************************/
#define _FILE_CODE_  _MSM_INT_C_

#include "kal_public_api.h"        /* Basic data type */
#include "kal_public_defs.h"

#include "stack_ltlcom.h" /* Task message communiction */

#include "syscomp_config.h"
#include "task_config.h"        /* Task creation */

#include "stacklib.h"   /* Basic type for dll, evshed, stacktimer */

#include "event_shed.h" /* Event scheduler */

#include "stack_timer.h"        /* Stack timer */
#include "kal_public_api.h"
#include "fat_fs.h"     /* file system */

#include "stdio.h"

#include "msf_cfg.h"
#include "msf_mem.h"
#include "msf_log.h"
#include "msf_file.h"
#include "msm_int.h"
#include "msm_env.h"
#include "msm.h"
#include "stk_env.h"
#include "brs_env.h"
#include "msf_int.h"

#ifdef MSF_MODID_PRS
#include "prs_env.h"
#include "prs_cfg.h"
#endif
#ifdef WAP_SEC_SUPPORT
#include "sec_env.h"
#endif 
#ifdef OBIGO_Q03C_MMS_V01
#include "mms_env.h"
#include "mea_def.h"
#include "mea_env.h"
#include "sls_env.h"
#include "sma_env.h"
#endif /* OBIGO_Q03C_MMS_V01 */ 
#ifdef WPS_SUPPORT
#include "wps_env.h"
#endif 
#include "bam_env.h"

#include "das_env.h"

#include "msf_int.h"
#include "msf_cmmn.h"
#ifdef MSF_CFG_WAP_PROF_SUPPORT
#include "WAPProfileSrvType.h"
#endif /* MSF_CFG_WAP_PROF_SUPPORT */
#include "nvram_user_defs.h"
#include "widget.h"
#include "widget_extension.h"
#include "phs_env.h"
#include "pmg_env.h"

#ifdef Q03C_IND_MOD_ARCH_SUPPORT
#include "Int_timer.h"
#endif /*Q03C_IND_MOD_ARCH_SUPPORT*/

#ifndef Q03C_IND_MOD_ARCH_SUPPORT
#include "kal_internal_api.h"
#endif

/* 
 * global variables for download file info 
 */
static int wap_download_file_num_g = -1;    /* uninitialized */
static long wap_download_file_size_g = 0;

#if defined(PRS_CONFIG_WAP) || defined(PRS_CONFIG_WAP_WBXML)

#define WAP_DEFAULT_REGISTRY_CONTENT        \
"[/msm/rt_db/prs]\r\n"                      \
"MimeType=\""                               \
"application/x-wap-prov.browser-settings,"  \
"application/x-wap-prov.browser-bookmarks," \
"application/vnd.wap.connectivity-wbxml"    \
"\"\r\n"

#else /* defined(PRS_CONFIG_WAP) || defined(PRS_CONFIG_WAP_WBXML) */ 

#define WAP_DEFAULT_REGISTRY_CONTENT       \
"[/msm/rt_db/prs]\r\n"                     \
"MimeType=\""                              \
"application/x-wap-prov.browser-settings," \
"application/x-wap-prov.browser-bookmarks" \
"\"\r\n"

#endif /* defined(PRS_CONFIG_WAP) || defined(PRS_CONFIG_WAP_WBXML) */ 

#define MSF_MOD_IS_RUNNING(modId) \
   (msf_mod_status[modId] != MSM_MODULE_STATUS_TERMINATED)

#define MSF_SET_MOD_STATUS(msfUid, mod_status) \
   msf_mod_status[msfUid] = mod_status;

typedef void (*msf_void_func_ptr) (void);
typedef int (*msf_int_func_ptr) (void);

#ifdef WAP_COOPERATIVE_SHARE_MCU_TIME
/* If WAP task keeps processing internal queue for more than the assigned timer period,
   it should voluntarily give cnotrol to MMI task. */
#define WAP_TIME_QUANTUM_IN_TICKS   (KAL_TICKS_1_SEC /4)
#endif /* WAP_COOPERATIVE_SHARE_MCU_TIME */ 

/*
 * Private functions for backup critical files
 */
eventid msf_start_timer(MSF_UINT32 timeInterval, kal_timer_func_ptr timer_hdlr, void *event_param);

void msm_backup_recover_critical_files(void);
void msm_compute_checksum_critical_files(void);

void msm_backup_recover_index_files(void);
void msm_compute_checksum_index_files(void);

void msm_backup_recover_sec_files(void);
void msm_compute_checksum_sec_files(void);

#ifdef MSF_REGISTRY_SUPPPORT
void msm_backup_recover_reg_files(void);
void msm_compute_checksum_reg_files(void);
#endif /*MSF_REGISTRY_SUPPPORT*/

void msm_remove_files_under_dir(const char *folder);

typedef struct msf_int_func_t
{
    msf_int_func_ptr wantsToRun;
    msf_void_func_ptr run;
    msf_void_func_ptr kill;

} msf_int_func_t;

typedef struct
{
    char startup_policy;
    char *short_name;
} msf_cfg_t;

msf_start_call_back_t msf_start_call_back;
//event_scheduler *msf_evshed_ptr = NULL;
//eventid msm_timer_event_id;
int msf_mod_status[MSF_NUMBER_OF_MODULES];
extern kal_uint32 msf_mod_init_mask;

#ifdef WPS_TASK_SUPPORT
kal_mutexid wap_ctrl_mutex = NULL;
kal_bool wap_in_critical_section;
kal_bool wps_want_to_run;
#endif /* WPS_TASK_SUPPORT */ 

#ifdef OBIGO_Q03C_MMS_V01
extern void mmsUpdateIndicator(void);
#endif 

extern void wap_fetch_msg_to_int_q(void);

extern int mms_get_disk_label(int type);
extern int getDiskLabel(int type);

#ifdef __MMI_URI_AGENT__
#include "mmsadp.h"
#include "UriAgentSrvGprot.h"
#endif /*#ifdef __MMI_URI_AGENT__*/


#if 0
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#ifdef MSF_MODID_BRA
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif        
#ifdef __WAP_PUSH_SUPPORT__     
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif 
#ifdef MSF_MODID_PRS
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
    #ifdef WAP_SEC_SUPPORT
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
    #endif /* WAP_SEC_SUPPORT */ 
    #ifdef OBIGO_Q03C_MMS_V01
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
    #ifdef __UNIFIED_COMPOSER_SUPPORT__
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
    #endif
    #ifdef __MMI_MMS_VENDOR_APP_SUPPORT__
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
    #endif
/* under construction !*/
    #ifdef MMSAT_SUPPORT
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
    #endif /* MMSAT_SUPPORT */ 
    #endif /* OBIGO_Q03C_MMS_V01 */ 
    #ifdef WPS_SUPPORT
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
    #endif /* WPS_SUPPORT */ 
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif


#if 0
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
        #ifdef OBIGO_Q03C_MMS_V01
/* under construction !*/
/* under construction !*/
/* under construction !*/
        #ifdef __MMI_MMS_IN_UM__
/* under construction !*/
        #ifdef __UNIFIED_COMPOSER_SUPPORT__
/* under construction !*/
        #endif
        #ifdef __MMI_MMS_VENDOR_APP_SUPPORT__
/* under construction !*/
        #endif
/* under construction !*/
        #endif
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
        #ifdef __MMI_MMS_IN_UM__  /* check if both MEA and MMS are ready */
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
            #ifdef MMS_FILE_PROTECT_SUPPORT
/* under construction !*/
/* under construction !*/
/* under construction !*/
            #endif /* MMS_FILE_PROTECT_SUPPORT */ 
/* under construction !*/
/* under construction !*/
        #endif /* __MMI_MMS_IN_UM__ */ 
/* under construction !*/
        #endif /* OBIGO_Q03C_MMS_V01 */ 
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
                #ifdef WAP_QUEUE_SMS_PUSH
/* under construction !*/
                #endif 
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#ifdef WAP_SEC_SUPPORT
/* under construction !*/
#endif /* WAP_SEC_SUPPORT */
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#ifdef MSF_MODID_BRA
/* under construction !*/
#endif    
/* under construction !*/
/* under construction !*/
#endif
/*****************************************************************************
 * FUNCTION
 *  msf_timer_expiry_hdlr
 * DESCRIPTION
 *  
 * PARAMETERS
 *  ilm_ptr     [?]     
 * RETURNS
 *  void
 *****************************************************************************/
void msf_timer_expiry_hdlr(ilm_struct *ilm_ptr)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

#ifndef Q03C_IND_MOD_ARCH_SUPPORT 	
    evshed_timer_handler(msf_evshed_ptr);
#else
    mms_timer_expiry_hdlr();
#endif	
}
#ifndef Q03C_IND_MOD_ARCH_SUPPORT 	
/*****************************************************************************
 * FUNCTION
 *  msf_stop_timer
 * DESCRIPTION
 *  
 * PARAMETERS
 *  event_id        [?]     
 * RETURNS
 *  void
 *****************************************************************************/
void msf_stop_timer(eventid *event_id)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    /* If the is Timer Not Running it is not stopped */
    if (event_id)
    {
        evshed_cancel_event(msf_evshed_ptr, event_id);
    }

}





/*****************************************************************************
 * FUNCTION
 *  msm_timer_expiry_hdlr
 * DESCRIPTION
 *  
 * PARAMETERS
 *  event_param     [?]     
 * RETURNS
 *  void
 *****************************************************************************/
void msm_timer_expiry_hdlr(void *event_param)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    msm_timer_event_id = NULL;
    MSMc_timerExpiredEvent();
}

/*****************************************************************************
 * FUNCTION
 *  MSMa_setTimer
 * DESCRIPTION
 *  
 * PARAMETERS
 *  timeInterval        [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void MSMa_setTimer(MSF_UINT32 timeInterval)
{
#if 1
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    ASSERT(msm_timer_event_id == NULL);
    msm_timer_event_id = msf_start_timer(timeInterval, msm_timer_expiry_hdlr, NULL);
#else /* 1 */ 
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif /* 1 */ 
}


/*****************************************************************************
 * FUNCTION
 *  MSMa_resetTimer
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void MSMa_resetTimer(void)
{
#if 1
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    msf_stop_timer(&msm_timer_event_id);
#else /* 1 */ 
/* under construction !*/
#endif /* 1 */ 
}


/*****************************************************************************
 * FUNCTION
 *  MSMa_registryResponse
 * DESCRIPTION
 *  
 * PARAMETERS
 *  id      [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void MSMa_registryResponse(MSF_UINT8 id)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
#ifndef MSF_CFG_WAP_PROF_SUPPORT
    extern void wap_prof_access_proc(int prof_id);
    msf_registry_param_t param;

    /* currently, only for profile id in case wap profile access */
    if (!MSMc_registryRespGetNext(id, &param))
    {
        wap_prof_access_proc(-1);
    }
    else
    {
        wap_prof_access_proc(param.value_i);
    }

    MSMc_registryRespFree(id);
#endif /* MSF_CFG_WAP_PROF_SUPPORT */
}


/*****************************************************************************
 * FUNCTION
 *  MSMa_externalGet
 * DESCRIPTION
 *  
 * PARAMETERS
 *  id          [IN]        
 *  path        [IN]        
 *  key         [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void MSMa_externalGet(MSF_INT32 id, const char *path, const char *key)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    ilm_struct *ilm_ptr;
    kal_uint8 send_imsi_to_sim = 0;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/    	
    if (strcmp(key, "NETW_SSD") == 0)
    {
        send_imsi_to_sim = 1;
    }
    else if (strcmp(key, "NETW_SSD_1") == 0)
    {
        send_imsi_to_sim = 1;
    }
    else if (strcmp(key, "NETW_SSD_2") == 0)
    {
        send_imsi_to_sim = 2;
    }
    else
    {
        MSMc_externalResponse(id, NULL);
        return;
    }

    if (send_imsi_to_sim)
    {
        /* PRS requesting IMSI */
        wap_external_get_id = (kal_int32)id;

        ilm_ptr = allocate_ilm(MOD_WAP);
        ilm_ptr->msg_id = (kal_uint16)MSG_ID_MMI_SMU_GET_IMSI_REQ;
        ilm_ptr->peer_buff_ptr = NULL;
        ilm_ptr->local_para_ptr = NULL;

        if (send_imsi_to_sim == 1)
        {
            SEND_ILM(MOD_WAP, MOD_L4C, 0, ilm_ptr);
        }
#ifdef __WAP_DUAL_SIM__
        else if (send_imsi_to_sim == 2)
        {
            SEND_ILM(MOD_WAP, MOD_L4C_2, 0, ilm_ptr);
        }
#endif  /* __WAP_DUAL_SIM__ */
        else
        {
            ASSERT(0);
        }
    }
}
#endif /*Q03C_IND_MOD_ARCH_SUPPORT 	*/

/*****************************************************************************
 * FUNCTION
 *  MSF_moduleIsRunning
 * DESCRIPTION
 *  
 * PARAMETERS
 *  modId       [IN]        
 * RETURNS
 *  
 *****************************************************************************/
int MSF_moduleIsRunning(MSF_UINT8 modId)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (modId >= MSF_NUMBER_OF_MODULES)
    {
        return 0;
    }

    return MSF_MOD_IS_RUNNING(modId);
}


/*****************************************************************************
 * FUNCTION
 *  MSF_wapIsReady
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  
 *****************************************************************************/
int MSF_wapIsReady(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return (!(widget_is_shutdown_UI()) && (!msf_mod_init_mask));
}


/*****************************************************************************
 * FUNCTION
 *  MSF_wapIsInit
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  
 *****************************************************************************/
int MSF_wapIsInit(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    extern kal_uint8 wap_status;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return (wap_status == WAP_RUNNING && msf_mod_init_mask);
}

#ifdef MSF_NEW_EXCEPTION_HANDLING
MSF_UINT8 MSF_getExceptionPool(void)
{
	extern MSF_UINT8 HDIa_memGetException();

	return HDIa_memGetException();
}
#endif

/*****************************************************************************
 * FUNCTION
 *  MSF_start
 * DESCRIPTION
 *  
 * PARAMETERS
 *  slow_start      [IN]        
 *  callback        [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
void MSF_start(kal_bool slow_start, msf_start_call_back_t callback)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
	#ifdef MSF_REGISTRY_SUPPORT
    int fd;
	#endif
    extern kal_uint8 wap_status;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    msf_start_call_back = callback;
    wap_status = WAP_RUNNING;
    if (slow_start == KAL_TRUE)
    {
        msf_mod_init_mask = (1 << MSF_MODID_MSM);
    }

    MSF_SET_MOD_STATUS(MSF_MODID_MSM, MSM_MODULE_STATUS_ACTIVE)
	msf_modules[MSF_MODID_MSM].isActive = 1;
        /*
         * Justin 
         * * MSF_start() is called after wap_init() but before wap_fsm()
         * * recover or backup important configuration files here
         */
        msm_backup_recover_critical_files();

    /*
     * index files (Kevin)
     */
    msm_backup_recover_index_files();

    /*
     * sec files (Kevin)
     */
    /* msm_backup_recover_sec_files(); */

    /*
     * registry files (johnnie)
     */
#ifdef MSF_REGISTRY_SUPPORT
    msm_backup_recover_reg_files();

    fd = MSF_FILE_OPEN(MSF_MODID_MSM, WAP_MSM_REGISTRY_FILE, HDI_FILE_SET_RDONLY, 0 );
    if (fd < 0)
    {
        /* initialize default registry file */
        char param[32];

        fd = MSF_FILE_OPEN(MSF_MODID_MSM, WAP_DEFAULT_REGISTRY_FILE, HDI_FILE_SET_RDONLY, 0 );
        if (fd < 0)
        {
            MSMc_startMobileSuite(NULL);
        }
        else
        {
            MSF_FILE_CLOSE(fd);
            sprintf(param, "-r %s", WAP_DEFAULT_REGISTRY_FILE);
            MSMc_startMobileSuite(param);
        }
    }
    else
#endif /*MSF_REGISTRY_SUPPPORT*/
    {
#ifdef MSF_REGISTRY_SUPPORT
        MSF_FILE_CLOSE(fd);
#endif /*MSF_REGISTRY_SUPPPORT*/
        MSMc_startMobileSuite(NULL);
    }
}


/*****************************************************************************
 * FUNCTION
 *  MSF_fsm
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void MSF_fsm(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    kal_bool run = KAL_TRUE;
    kal_uint8 i;
    extern void HDIa_setModuleID(int mod_id);
    extern int isSignalPending(module_type mod_id);
    int run_count = 0;

#ifdef WAP_COOPERATIVE_SHARE_MCU_TIME
    kal_uint32 last_ticks, ticks;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    kal_get_time(&last_ticks);
#endif /* WAP_COOPERATIVE_SHARE_MCU_TIME */ 

    while (run)
    {
      

        run = KAL_FALSE;

        /* except WIDGET, each module has chance to run */
        for (i = 0; i < MSF_NUMBER_OF_MODULES; i++)
        {
            if(msf_modules[i].taskId == MOD_WPS)
                continue;
            
        #ifdef WPS_TASK_SUPPORT
            kal_take_mutex(wap_ctrl_mutex);
            wap_in_critical_section = KAL_TRUE;
            wps_want_to_run = KAL_FALSE;
        #endif /* WPS_TASK_SUPPORT */ 
        
            if (((msf_modules[i].taskId == MOD_WAP)) && (msf_modules[i].isActive))
            {

                if(run_count < 5)     /*MAUI_03210871*/
                {
                HDIa_setModuleID (msf_modules[i].moduleId);
                if (msf_modules[i].pTaskWantsToRun())
                {
                    msf_modules[i].pTaskRun();
                    run = KAL_TRUE;
                        run_count++;
                }
                HDIa_setModuleID(-1);
            }

            }
        #ifdef WPS_TASK_SUPPORT
            if (isSignalPending(MOD_WPS))
            {
                
                /* If there are already pending signals in WPS queue, no need to notify */
                if (!(msg_get_task_extq_messages(INDX_WPS) > 0))
                {
                extern void widget_send_update_event_to_wps(void);

                widget_send_update_event_to_wps();
                }
            }
            wap_in_critical_section = KAL_FALSE;
            kal_give_mutex(wap_ctrl_mutex);
        #endif /* WPS_TASK_SUPPORT */ 
        }
        wap_fetch_msg_to_int_q();
    #ifdef __MTK_TARGET__
        if (msf_mod_init_mask)
        {
            wap_task_sleep(10);
            if (msg_get_task_extq_messages(INDX_WAP) > 0)
            {
                return;
            }
        }
    #endif /* __MTK_TARGET__ */ 
        /* if(msg_get_ext_queue_info(task_info_g[INDX_WAP].task_ext_qid, &num_of_msg)
           && num_of_msg > 0)
           return; */
    #ifdef WAP_COOPERATIVE_SHARE_MCU_TIME
        if (run)
        {
            kal_get_time(&ticks);
            if (ticks > last_ticks)
            {
                if (ticks - last_ticks > WAP_TIME_QUANTUM_IN_TICKS)
                {
                    /* Voluntarily make the current task sleep */
                    wap_task_sleep(10);
                    kal_get_time(&last_ticks);
                }
            }
            else
            {
                /* Abnormal. maybe integer overflow */
                last_ticks = ticks;
            }
        }
    #endif /* WAP_COOPERATIVE_SHARE_MCU_TIME */ 
    }
    if (isSignalPending(MOD_WAP))
    {
        extern void hdi_notify_task(module_type src, module_type dst, msg_type msg_id);

        hdi_notify_task(MOD_WAP, MOD_WAP, MSG_ID_WAP_STATUS_UPDATE_IND);
    }
#ifdef Q03C_IND_MOD_ARCH_SUPPORT
    if (isSignalPending(MOD_MMS))
    {
        extern void hdi_notify_task(module_type src, module_type dst, msg_type msg_id);

        hdi_notify_task(MOD_WAP, MOD_MMS, MSG_ID_WAP_STATUS_UPDATE_IND);
    }
#endif
}



/*****************************************************************************
 * FUNCTION
 *  MSM_init
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  
 *****************************************************************************/
kal_bool MSM_init(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    kal_uint8 i;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
#ifdef WPS_TASK_SUPPORT
    if (wap_ctrl_mutex == NULL)
    {
        wap_ctrl_mutex = kal_create_mutex("WAP CTRL Mutex");
        wap_in_critical_section = KAL_FALSE;
    }
#endif /* WPS_TASK_SUPPORT */ 

    for (i = 0; i < MSF_NUMBER_OF_MODULES; i++)
    {
        msf_mod_status[i] = MSM_MODULE_STATUS_TERMINATED;
    }

#ifdef Q03C_IND_MOD_ARCH_SUPPORT
        init_mms_timer();
#else
    msm_timer_event_id = NULL;

    if(msf_evshed_ptr == NULL)
    {
        /* Create an Event Scheduler */
     msf_evshed_ptr = evshed_create("WAP_MSF_TIMER", MOD_WAP, 0, 0);
	 evshed_set_index(msf_evshed_ptr, MSF_MSM_TIMER_ID);
    }
#endif

    return KAL_TRUE;
}


/*****************************************************************************
 * FUNCTION
 *  MSM_deinit
 * DESCRIPTION
 *  
 * PARAMETERS
 *  void
 * RETURNS
 *  
 *****************************************************************************/
kal_bool MSM_deinit(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
#ifndef Q03C_IND_MOD_ARCH_SUPPORT 	
    /* Delete all the pending events and the event scheduler */
    evshed_delete_all_events(msf_evshed_ptr);
    
    stack_stop_timer(&msf_timer);
#else
    deinit_mms_timer();
#endif	
    
    return KAL_TRUE;
}

/*****************************************************************************
 * Justin. Dealing with abnormal condition
 *
 * We duplicate important files, and maintain checksum for master and backup files
 * We try to keep atmost _one_ file open for writing when possible.
 *
 * Reference: MSF_start(), MSMa_terminated()
 */

/* Reference: hdi_needflush_file_list[] */
static const char *MSM_CRITICAL_FILES[MSM_NUM_CRITICAL_FILES] = MSM_CRITICAL_FILES_VALUES;

static const char *MSM_CRITICAL_FILES_BACKUP[MSM_NUM_CRITICAL_FILES] = MSM_CRITICAL_FILES_BACKUP_VALUES;

/* should we compute the checksum of the corresponding files during poweroff */
static const kal_uint8 MSM_CRITICAL_FILES_CHECKSUM_POWEROFF[MSM_NUM_CRITICAL_FILES] =
    MSM_CRITICAL_FILES_CHECKSUM_POWEROFF_VALUES;

const char *MSM_BACKUP_CHECKSUM_PATH[MSM_NUM_BACKUP_CHECKSUM_PATH] = MSM_BACKUP_CHECKSUM_PATH_VALUES;

static const char *MSM_CHECKSUM_MASTER_FILENAME = "/msm/chksum1.dat";
static const char *MSM_CHECKSUM_BAK_FILENAME = "/msm/chksum2.dat";

typedef kal_int32 msm_checksum_t;

typedef struct msm_checksum_package_struct
{

    msm_checksum_t *checksum;
    int fd;     /* file handle */
    int mode;   /* see blow */
    int dirty;  /* is modified */
} *msm_checksum_handle_t;

/* read/write mode for open checksum package */
#define MSM_CHECKSUM_MODE_RDONLY (0)
#define MSM_CHECKSUM_MODE_RDWR (1)

/****************************************************************************
 * Kevin: Deal with the corruption of index files.
 *
 * the handling is different from critical files:
 * when we detects the index file is been corrupted, we delete all files
 * under the folder.
 ****************************************************************************/
static const char *MSM_INDEX_FILES[MSM_NUM_INDEX_FILES] = MSM_INDEX_FILES_VALUES;
static const char *MSM_INDEX_FILE_FOLDERS[MSM_NUM_INDEX_FILES] = MSM_INDEX_FILES_FOLDER_VALUES;
static const char *MSM_IDX_CHECKSUM_FILENAME = "/msm/idxchksum.dat";
const char *MSM_IDX_FILE_PATH[MSM_NUM_IDX_FILE_PATH] = MSM_IDX_FILE_PATH_VALUES;

/****************************************************************************
 * Kevin: Deal with the corruption of security files. 
 ****************************************************************************/
#ifdef WAP_SEC_SUPPORT
static const char *MSM_SEC_CHECKSUM_FILENAME = "/msm/secchksum.dat";
#endif
const char *MSM_SEC_FILE_PATH[MSM_NUM_SEC_FILE_PATH] = MSM_SEC_FILE_PATH_VALUES;

#ifdef MSF_REGISTRY_SUPPORT
static const char *MSM_REG_CHECKSUM_FILENAME = "/msm/regchksum.dat";
#endif /*MSF_REGISTRY_SUPPPORT*/

/*****************************************************************************
 * FUNCTION
 *  msm_copy_file
 * DESCRIPTION
 *  copy the content of a file
 * PARAMETERS
 *  dstName     [IN]        Destination file (might be overwritten)
 *  srcName     [IN]        Source file
 * RETURNS
 *  KAL_TRUE    success
 *  KAL_FALSE   failed
 *****************************************************************************/
kal_bool msm_copy_file(const char *dstName, const char *srcName)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int src, dst;
    int size;
    unsigned char buf[128];

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    /*
     * Since we have HDI_FILE_SET_CUSTOM_BLOCKING, the subsequent calls should
     * not return HDI_FILE_ERROR_DELAYED. ie. it should not return values < 0 unless error 
     */

    src = MSF_FILE_OPEN(MSF_MODID_MSM, srcName, HDI_FILE_SET_RDONLY | HDI_FILE_SET_CUSTOM_BLOCKING, 0 );
    if (src < 0)
    {
        return KAL_FALSE;
    }

    MSF_FILE_REMOVE(dstName );   /* kevin fix */

    dst = MSF_FILE_OPEN(
            MSF_MODID_MSM,
            dstName,
            HDI_FILE_SET_WRONLY | HDI_FILE_SET_CREATE | HDI_FILE_SET_CUSTOM_BLOCKING,
            0 );
    if (dst < 0)
    {
        MSF_FILE_CLOSE(src);
        return KAL_FALSE;
    }

    MSF_FILE_SEEK(dst, 0, HDI_FILE_SEEK_SET);
    for (;;)
    {
        size = MSF_FILE_READ(src, buf, 128);
        if (HDI_FILE_ERROR_EOF == size) /* finished */
        {
            MSF_FILE_CLOSE(src);
            MSF_FILE_CLOSE(dst);
            return KAL_TRUE;    /* success */
        }
        if (size < 0)
        {
            /* it really should not happen */
            WAP_DBG_ASSERT(0);
            MSF_FILE_CLOSE(src);
            MSF_FILE_CLOSE(dst);
            // HDIa_fileRemove(srcName);    /* Should we remove the source file? */
            MSF_FILE_REMOVE(dstName );
            return KAL_FALSE;
        }
        if (MSF_FILE_WRITE(dst, buf, size) < 0)
        {
            /* it should not happen unless the filesystem is full */
            WAP_DBG_ASSERT(0);
            MSF_FILE_CLOSE(src);
            MSF_FILE_CLOSE(dst);
            MSF_FILE_REMOVE(dstName );   /* invalid output file */
            return KAL_FALSE;
        }
    }

}


/*****************************************************************************
 * FUNCTION
 *  msm_load_checksum
 * DESCRIPTION
 *  open a checksum package
 * PARAMETERS
 *  fileName        [IN]        Filename of the checksum package
 *  mode            [IN]        MSM_CHECKSUM_MODE_RDONLY or MSM_CHECKSUM_MODE_RDWR
 *  file_num        [IN]        
 * RETURNS
 *  0           fail
 *  Otherwise   a handle of later manipulation
 *****************************************************************************/
static msm_checksum_handle_t msm_load_checksum(const char *fileName, int mode, int file_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    /*
     * XXX at this time, MSM module is not initialized before MSF_start(). 
     * * Does it have any potential problems?
     */

    /* HDI_FILE_SET_CUSTOM_BLOCKING is a temp fix */

    int fd, i;
    int rwmode;
    msm_checksum_handle_t handle = MSF_MEM_ALLOC(
                                    MSF_MODID_MSM,
                                    sizeof(struct msm_checksum_package_struct));

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (handle == 0)
    {
        /*
         * it should not happen because we should always have  
         * * enough memory
         */
        WAP_DBG_ASSERT(0);
        return 0;
    }

    handle->checksum = MSF_MEM_ALLOC(MSF_MODID_MSM, sizeof(msm_checksum_t) * file_num);

    if (mode == MSM_CHECKSUM_MODE_RDONLY)
    {
        rwmode = HDI_FILE_SET_RDONLY;
    }
    else
    {
        rwmode = HDI_FILE_SET_RDWR;
    }

    if ((fd = MSF_FILE_OPEN(MSF_MODID_MSM, fileName, rwmode | HDI_FILE_SET_CUSTOM_BLOCKING, 0 )) < 0)
    {
        if (fd != HDI_FILE_ERROR_PATH)
        {
            WAP_DBG_ASSERT(0);
            MSF_MEM_FREE(MSF_MODID_MSM, handle);
            return 0;
        }

        /*
         * file not existed (HDI_FILE_ERROR_PATH) 
         * * Note that we always use HDI_FILE_SET_RDWR because
         * * (HDI_FILE_SET_RDONLY|HDI_FILE_SET_CREATE) will fail.
         */

        fd = MSF_FILE_OPEN(
                MSF_MODID_MSM,
                fileName,
                HDI_FILE_SET_RDWR | HDI_FILE_SET_CREATE | HDI_FILE_SET_CUSTOM_BLOCKING,
                0 );
        if (fd < 0)
        {
            WAP_DBG_ASSERT(0);
            MSF_MEM_FREE(MSF_MODID_MSM, handle);
            return 0;
        }

        /* Fill as -1 for newly created entries */
        for (i = 0; i < file_num; i++)
        {
            handle->checksum[i] = -1;
        }
    }
    else
    {
        msm_checksum_t chksum;
        int ret;

        /* file opened, read stored value */
        for (i = 0; i < file_num; i++)
        {
            ret = MSF_FILE_READ(fd, &chksum, sizeof(chksum));
            if (sizeof(chksum) == ret)
            {
                handle->checksum[i] = chksum;
            }
            else if (HDI_FILE_ERROR_EOF == ret)
            {
                break;
            }
            else
            {
                WAP_DBG_ASSERT(0);          /* should rarely happen */
                break;
            #if 0
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
            #endif /* 0 */ 
            }
        }

        if (i < file_num)
        {
            /*
             * in case of new code on old filesystem 
             * * fill the rest entries as -1
             */
            for (; i < file_num; i++)
            {
                handle->checksum[i] = -1;   /* -1 for newly created entries */
            }
        }
    }

    handle->fd = fd;
    handle->mode = mode;
    handle->dirty = 0;
    return handle;
}


/*****************************************************************************
 * FUNCTION
 *  msm_unload_checksum
 * DESCRIPTION
 *  free a checksum package, store results when necessary
 * PARAMETERS
 *  handle          [IN]        Handle obtained by msm_load_checksum()
 *  file_num        [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
static void msm_unload_checksum(msm_checksum_handle_t handle, int file_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i, ret;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (handle->dirty)  /* modified */
    {
        ASSERT(handle->mode == MSM_CHECKSUM_MODE_RDWR);

        MSF_FILE_SEEK(handle->fd, 0, HDI_FILE_SEEK_SET);
        for (i = 0; i < file_num; i++)
        {
            ret = MSF_FILE_WRITE(handle->fd, &(handle->checksum[i]), sizeof(msm_checksum_t));
            if (ret != sizeof(msm_checksum_t))
            {
                WAP_DBG_ASSERT(0);
                break;
            }
        }
    }

    MSF_FILE_CLOSE(handle->fd);

    MSF_MEM_FREE(MSF_MODID_MSM, handle->checksum);

    MSF_MEM_FREE(MSF_MODID_MSM, handle);
}

/*****************************************************************************
 * Helper functions
*****************************************************************************/

/* Note. if return  -1, it means the checksum is invalid */


/*****************************************************************************
 * FUNCTION
 *  msm_get_checksum
 * DESCRIPTION
 *  
 * PARAMETERS
 *  handle          [IN]        
 *  idx             [IN]        
 *  file_num        [IN]        
 * RETURNS
 *  
 *****************************************************************************/
static msm_checksum_t msm_get_checksum(msm_checksum_handle_t handle, int idx, int file_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    WAP_DBG_ASSERT(idx < file_num && idx >= 0);
    if (idx >= file_num || idx < 0)
    {
        return -1;
    }
    return handle->checksum[idx];
}


/*****************************************************************************
 * FUNCTION
 *  msm_put_checksum
 * DESCRIPTION
 *  
 * PARAMETERS
 *  handle          [IN]        
 *  idx             [IN]        
 *  chksum          [IN]        
 *  file_num        [IN]        
 * RETURNS
 *  void
 *****************************************************************************/
static void msm_put_checksum(msm_checksum_handle_t handle, int idx, msm_checksum_t chksum, int file_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    ASSERT(idx < file_num && idx >= 0);
    ASSERT(handle->mode == MSM_CHECKSUM_MODE_RDWR);
    handle->checksum[idx] = chksum;
    handle->dirty = 1;
}


/*****************************************************************************
 * FUNCTION
 *  msm_compute_checksum_from_file
 * DESCRIPTION
 *  msm_compute_checksum_from_file (non-static, for use in other place)
 * PARAMETERS
 *  filename        [IN]        
 *  fileName(?)     [IN]        The file to compute checksum
 * RETURNS
 *  -1      error
 *  Otherwise,  checksum (0~65535 16 bit)
 *****************************************************************************/
static msm_checksum_t msm_compute_checksum(const char *fileName);

int msm_compute_checksum_from_file(const char *filename)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return (int)msm_compute_checksum(filename);
}


/*****************************************************************************
 * FUNCTION
 *  msm_compute_checksum
 * DESCRIPTION
 *  compute simple checksum
 * PARAMETERS
 *  fileName        [IN]        The file to compute checksum
 * RETURNS
 *  -1      error
 *  Otherwise,  checksum (0~65535 16 bit)
 *****************************************************************************/
static msm_checksum_t msm_compute_checksum(const char *fileName)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    /*
     * Reference: in_cksum_hdr()
     */

    int fd;
    unsigned char buf[128];
    int i, size;
    int oddcount = 0;   /*
                         * for debug. Only the last read return size < 128, 
                         * * Otherwise, the checksum would be wrong
                         */

    unsigned int rc = 0;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    /*
     * Since we have HDI_FILE_SET_CUSTOM_BLOCKING, the subsequent calls should
     * not return HDI_FILE_ERROR_DELAYED. ie. it should not return values < 0 unless error 
     */

    if ((fd = MSF_FILE_OPEN(MSF_MODID_MSM, fileName, HDI_FILE_SET_RDONLY | HDI_FILE_SET_CUSTOM_BLOCKING, 0 )) < 0)
    {
        return -1;
    }

    for (;;)
    {
        size = MSF_FILE_READ(fd, buf, 128);

        if (HDI_FILE_ERROR_EOF == size) /* finished */
        {
            break;
        }

        WAP_DBG_ASSERT(oddcount == 0);  /* if oddcount == 1, it should be the last read */

        if (size < 0)   /* fail */
        {
            WAP_DBG_ASSERT(0);
            MSF_FILE_CLOSE(fd);
            return -1;
        }

        if (size & 1)
        {
            /*
             * we add two char in one time 
             * * size is smaller than 127, and buf[size] will not cause overflow
             */
            buf[size] = 0;
            oddcount++; /* for debug */
        }
        for (i = 0; i < size; i += 2)
        {
            rc += (buf[i] << 8) | buf[i + 1];
        }
    }
    MSF_FILE_CLOSE(fd);

    WAP_DBG_ASSERT(oddcount == 1 || oddcount == 0);

    rc = (rc >> 16) + (rc & 0xffff);
    rc += (rc >> 16);

    return (~rc) & 0xffff;;
}


/*****************************************************************************
 * FUNCTION
 *  msm_backup_recover_critical_files
 * DESCRIPTION
 *  recover or backup important configuration files
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
/* 
 * TODO: I should not overwrite the backup file everytime when 
 * it is unnecessary (it's not a good thing to erase flash too often)
 * 
 * Besides, if the file doesn't exist (e.g., /bra/profiles.dat is only created 
 * after modify WAP settings), we should not call HDIa_fileRemove
 */
void msm_backup_recover_critical_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;
    msm_checksum_handle_t handle, handle_bak;
    msm_checksum_t chksum;
    kal_bool update_master_checksum = KAL_FALSE;
    int action[MSM_NUM_CRITICAL_FILES]; /*
                                         * 0: copy from master to backup
                                         * * 1: recover from backup to master
                                         * * 2: delete both the master & backup file
                                         */
    msm_checksum_t correct_chksum[MSM_NUM_CRITICAL_FILES];

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    for (i = 0; i < MSM_NUM_CRITICAL_FILES; i++)
    {
        action[i] = 0;
        correct_chksum[i] = -1;
    }

    /*
     * 0. make sure the the relevant directories are created
     *  because they are typically created later in MSF_start
     */
    for (i = 0; i < MSM_NUM_BACKUP_CHECKSUM_PATH; i++)
    {
        MSF_FILE_MKDIR(MSM_BACKUP_CHECKSUM_PATH[i] );
    }

    /*
     * 1. First open the checksum package READONLY
     */

    handle = msm_load_checksum(MSM_CHECKSUM_MASTER_FILENAME, MSM_CHECKSUM_MODE_RDONLY, MSM_NUM_CRITICAL_FILES);
    if (handle == 0)
    {
        WAP_DBG_ASSERT(0);
        return;
    }
    handle_bak = msm_load_checksum(MSM_CHECKSUM_BAK_FILENAME, MSM_CHECKSUM_MODE_RDONLY, MSM_NUM_CRITICAL_FILES);
    if (handle_bak == 0)
    {
        WAP_DBG_ASSERT(0);
        msm_unload_checksum(handle, MSM_NUM_CRITICAL_FILES);
        return;
    }

    for (i = 0; i < MSM_NUM_CRITICAL_FILES; i++)
    {
        chksum = msm_get_checksum(handle, i, MSM_NUM_CRITICAL_FILES);
        if (chksum >= 0 && msm_compute_checksum(MSM_CRITICAL_FILES[i]) == chksum)
        {
            action[i] = 0;
            correct_chksum[i] = chksum;
        }
        else
        {
            chksum = msm_get_checksum(handle_bak, i, MSM_NUM_CRITICAL_FILES);
            if (chksum >= 0 && msm_compute_checksum(MSM_CRITICAL_FILES_BACKUP[i]) == chksum)
            {
                /* use backup file to recover master file */
                action[i] = 1;
                correct_chksum[i] = chksum;
                update_master_checksum = KAL_TRUE;
            }
            else
            {
                /* remove both the master and backup file */
                action[i] = 2;
                correct_chksum[i] = -1;
                update_master_checksum = KAL_TRUE;
            }
        }
    }

    msm_unload_checksum(handle, MSM_NUM_CRITICAL_FILES);
    msm_unload_checksum(handle_bak, MSM_NUM_CRITICAL_FILES);

    /* 
     * 2. copy the files
     */
    for (i = 0; i < MSM_NUM_CRITICAL_FILES; i++)
    {
        switch (action[i])
        {
            case 0:
                msm_copy_file(MSM_CRITICAL_FILES_BACKUP[i], MSM_CRITICAL_FILES[i]);
                break;
            case 1:
                msm_copy_file(MSM_CRITICAL_FILES[i], MSM_CRITICAL_FILES_BACKUP[i]);
                break;
            case 2:
                MSF_FILE_REMOVE(MSM_CRITICAL_FILES[i] );
                MSF_FILE_REMOVE(MSM_CRITICAL_FILES_BACKUP[i] );
                break;
            default:
                ASSERT(0);
        }
    }

    /*
     * 3. reopen the checksum package, update it, 
     * * we want to keep the time short while files are open
     * * Beside, only ONE checksum file is open at one time
     * * This guarentee that at least one checksum file is correct
     */

    /* write back master checksum */
    if (update_master_checksum)
    {
        handle = msm_load_checksum(MSM_CHECKSUM_MASTER_FILENAME, MSM_CHECKSUM_MODE_RDWR, MSM_NUM_CRITICAL_FILES);

        if (handle == 0)
        {
            WAP_DBG_ASSERT(0);
            return;
        }

        for (i = 0; i < MSM_NUM_CRITICAL_FILES; i++)
        {
            if (action[i] == 1 || action[i] == 2)
            {
                msm_put_checksum(handle, i, correct_chksum[i], MSM_NUM_CRITICAL_FILES);
            }
        }
        msm_unload_checksum(handle, MSM_NUM_CRITICAL_FILES);
    }

    /* write back checksum of backup */

    handle_bak = msm_load_checksum(MSM_CHECKSUM_BAK_FILENAME, MSM_CHECKSUM_MODE_RDWR, MSM_NUM_CRITICAL_FILES);
    if (handle_bak == 0)
    {
        WAP_DBG_ASSERT(0);
        return;
    }

    for (i = 0; i < MSM_NUM_CRITICAL_FILES; i++)
    {
        if (action[i] == 0 || action[i] == 2)
        {
            msm_put_checksum(handle_bak, i, correct_chksum[i], MSM_NUM_CRITICAL_FILES);
        }
    }

    msm_unload_checksum(handle_bak, MSM_NUM_CRITICAL_FILES);

}


/*****************************************************************************
 * FUNCTION
 *  msm_compute_checksum_critical_files
 * DESCRIPTION
 *  recompute the checksum of important configuration files
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void msm_compute_checksum_critical_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;
    msm_checksum_handle_t handle;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    handle = msm_load_checksum(MSM_CHECKSUM_MASTER_FILENAME, MSM_CHECKSUM_MODE_RDWR, MSM_NUM_CRITICAL_FILES);
    if (handle == 0)
    {
        WAP_DBG_ASSERT(0);
        return;
    }

    for (i = 0; i < MSM_NUM_CRITICAL_FILES; i++)
    {
        if (MSM_CRITICAL_FILES_CHECKSUM_POWEROFF[i])
        {
            msm_put_checksum(handle, i, msm_compute_checksum(MSM_CRITICAL_FILES[i]), MSM_NUM_CRITICAL_FILES);
        }
    }
    msm_unload_checksum(handle, MSM_NUM_CRITICAL_FILES);
}


/*****************************************************************************
 * FUNCTION
 *  msm_compute_checksum_critical_file_by_index
 * DESCRIPTION
 *  recompute the checksum of specified configuration file
 * PARAMETERS
 *  idx     [IN]        The index of the file
 * RETURNS
 *  void
 *****************************************************************************/
void msm_compute_checksum_critical_file_by_index(int idx)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    /* int i; */
    msm_checksum_handle_t handle;

#if 0   /* johnnie */
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif /* 0 */ 

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    handle = msm_load_checksum(MSM_CHECKSUM_MASTER_FILENAME, MSM_CHECKSUM_MODE_RDWR, MSM_NUM_CRITICAL_FILES);
    if (handle == 0)
    {
        WAP_DBG_ASSERT(0);
        return;
    }

    msm_put_checksum(handle, idx, msm_compute_checksum(MSM_CRITICAL_FILES[idx]), MSM_NUM_CRITICAL_FILES);

    msm_unload_checksum(handle, MSM_NUM_CRITICAL_FILES);
}

/* 
 * auth/cache/cookie index files 
 */


/*****************************************************************************
 * FUNCTION
 *  msm_remove_files_under_dir
 * DESCRIPTION
 *  This function deletes all files under the given folder.
 * PARAMETERS
 *  folder      [IN]        
 *  a(?)        [IN]        Folder
 * RETURNS
 *  void
 *****************************************************************************/
void msm_remove_files_under_dir(const char *folder)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    char *pathname;
    int type, filesize;
    int fileIdx = 0;    /* reset */
    char *name;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    WAP_DBG_ASSERT(folder[0]);
    WAP_DBG_ASSERT(strcmp(folder, "/"));
    WAP_DBG_ASSERT(strcmp(folder, "\\"));

    if (folder[0] == '\0' || strcmp(folder, "/") == 0 || strcmp(folder, "\\") == 0)
    {
        return;
    }

    pathname = MSF_MEM_ALLOC(MSF_MODID_MSM, FS_MAX_PATH);

    sprintf(pathname, "%s/", folder);
    name = strrchr(pathname, '/') + 1;
    while (MSF_FILE_READ_DIR(folder, fileIdx, name, FS_MAX_PATH, &type, &filesize ) == HDI_FILE_OK)
    {
        if (type == HDI_FILE_DIRTYPE)
        {
            msm_remove_files_under_dir(pathname);
            fileIdx++;
        }
        else if (type == HDI_FILE_FILETYPE)
        {
            if (MSF_FILE_REMOVE(pathname ) != HDI_FILE_OK)
            {
                fileIdx++;
            }
        }
    }

    MSF_MEM_FREE(MSF_MODID_MSM, pathname);

}   /* end of msm_remove_files_under_dir */


/*****************************************************************************
 * FUNCTION
 *  msm_copy_files_under_dir
 * DESCRIPTION
 *  This function copy all files under the given folder to another folder.
 * PARAMETERS
 *  srcFolder       [IN]        
 *  dstFolder       [IN]        
 *  a(?)            [IN]        SrcFolder
 *  b(?)            [IN]        DstFolder
 * RETURNS
 *  void
 *****************************************************************************/
void msm_copy_files_under_dir(const char *srcFolder, const char *dstFolder)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    char pathname[MAX_HDI_FILE_NAME_SIZE];
    char dstname[MAX_HDI_FILE_NAME_SIZE];
    int type, filesize;
    int fileIdx = 0;    /* reset */
    char *name;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    WAP_DBG_ASSERT(srcFolder[0]);
    WAP_DBG_ASSERT(strcmp(srcFolder, "/"));
    WAP_DBG_ASSERT(strcmp(srcFolder, "\\"));

    if (srcFolder[0] == '\0' || strcmp(srcFolder, "/") == 0 || strcmp(srcFolder, "\\") == 0)
    {
        return;
    }

    sprintf(pathname, "%s/", srcFolder);
    name = strrchr(pathname, '/') + 1;

    MSF_FILE_MKDIR(dstFolder );

    while (MSF_FILE_READ_DIR(srcFolder, fileIdx, name, MAX_HDI_FILE_NAME_SIZE, &type, &filesize ) == HDI_FILE_OK)
    {
        if (type == HDI_FILE_DIRTYPE)
        {
            fileIdx++;
            sprintf(dstname, "%s/%s", dstFolder, name);
            msm_copy_files_under_dir(pathname, dstname);
        }
        else if (type == HDI_FILE_FILETYPE)
        {
            fileIdx++;
            sprintf(dstname, "%s/%s", dstFolder, name);
            msm_copy_file(dstname, pathname);
        }
    }

}   /* end of msm_copy_files_under_dir */


/*****************************************************************************
 * FUNCTION
 *  msm_backup_recover_index_files
 * DESCRIPTION
 *  This function checks whether index files are been corrupted,
 *  if yes delete all files under the corresponding folder.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void msm_backup_recover_index_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;
    msm_checksum_handle_t handle;
    msm_checksum_t chksum;
    kal_bool update_checksum = KAL_FALSE;
    int action[MSM_NUM_INDEX_FILES];    /*
                                         * 0: do nothing
                                         * * 1: delete all files under folder
                                         */
    /*msm_checksum_t correct_chksum[MSM_NUM_INDEX_FILES];*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    for (i = 0; i < MSM_NUM_INDEX_FILES; i++)
    {
        action[i] = 0;
        /*correct_chksum[i] = -1;*/
    }

    for (i = 0; i < MSM_NUM_IDX_FILE_PATH; i++)
    {
        MSF_FILE_MKDIR(MSM_IDX_FILE_PATH[i]);
    }

    handle = msm_load_checksum(MSM_IDX_CHECKSUM_FILENAME, MSM_CHECKSUM_MODE_RDONLY, MSM_NUM_INDEX_FILES);
    if (handle == 0)
    {
        WAP_DBG_ASSERT(0);
        return;
    }

    for (i = 0; i < MSM_NUM_INDEX_FILES; i++)
    {
        chksum = msm_get_checksum(handle, i, MSM_NUM_INDEX_FILES);
        if (chksum >= 0 && msm_compute_checksum(MSM_INDEX_FILES[i]) == chksum)
        {
            action[i] = 0;  /* index file is ok */
            /*correct_chksum[i] = chksum;*/
        }
        else
        {
            action[i] = 1;  /* index file is wrong */
        }
    }

    msm_unload_checksum(handle, MSM_NUM_INDEX_FILES);

    for (i = 0; i < MSM_NUM_INDEX_FILES; i++)
    {
        switch (action[i])
        {
            case 0:
                break;
            case 1:
                msm_remove_files_under_dir(MSM_INDEX_FILE_FOLDERS[i]);
                update_checksum = KAL_TRUE;
                break;
            default:
                ASSERT(0);
                break;
        }
    }

    if (update_checksum == KAL_TRUE)
    {
        handle = msm_load_checksum(MSM_IDX_CHECKSUM_FILENAME, MSM_CHECKSUM_MODE_RDWR, MSM_NUM_INDEX_FILES);

        if (handle == 0)
        {
            WAP_DBG_ASSERT(0);
            return;
        }

        for (i = 0; i < MSM_NUM_INDEX_FILES; i++)
        {
            if (action[i] == 1)
            {
                msm_put_checksum(handle, i, -1, MSM_NUM_INDEX_FILES);
            }
        }
        msm_unload_checksum(handle, MSM_NUM_INDEX_FILES);
    }

}   /* end of msm_backup_recover_index_files */


/*****************************************************************************
 * FUNCTION
 *  msm_compute_checksum_index_files
 * DESCRIPTION
 *  This function computes the checksum for some index files.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void msm_compute_checksum_index_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;
    msm_checksum_handle_t handle;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    handle = msm_load_checksum(MSM_IDX_CHECKSUM_FILENAME, MSM_CHECKSUM_MODE_RDWR, MSM_NUM_INDEX_FILES);
    if (handle == 0)
    {
        WAP_DBG_ASSERT(0);
        return;
    }

    for (i = 0; i < MSM_NUM_INDEX_FILES; i++)
    {
        msm_put_checksum(handle, i, msm_compute_checksum(MSM_INDEX_FILES[i]), MSM_NUM_INDEX_FILES);
    }

    msm_unload_checksum(handle, MSM_NUM_INDEX_FILES);

}   /* end of msm_compute_checksum_index_files */

/* 
 * for recoverying security files
 */

#ifdef WAP_SEC_SUPPORT
/*****************************************************************************
 * FUNCTION
 *  get_sec_filename
 * DESCRIPTION
 *  This function allocates memory for security backup file names.
 *  And make the path as the original security path.
 *  Eg, /sec/backup/S_0, S_1,
 *  filename contains /sec/storage/S_0 and/sec/storage/S_1
 * PARAMETERS
 *  path            [?]             
 *  filename        [IN]            
 *  a(?)            [IN/OUT]        Filename
 * RETURNS
 *  number of secuirty files
 *****************************************************************************/
static int get_sec_filename(char *path, char ***filename)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i, type, filesize;
    int fileIdx = 0, cnt = 0;   /* reset */
    char *name;
    int file_num;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    ASSERT(filename != NULL);

    file_num = MSF_FILE_GETSIZE_DIR(path );

    if (file_num <= 0)  /* there is no security backup file */
    {
        *filename = NULL;
        return 0;
    }

    *filename = (char **)MSF_MEM_ALLOC(MSF_MODID_MSM, sizeof(char*) * file_num);

    for (i = 0; i < file_num; i++)
    {
        (*filename)[i] = MSF_MEM_ALLOC(MSF_MODID_MSM, MAX_HDI_FILE_NAME_SIZE);
    }

    do
    {
        sprintf((*filename)[cnt], "%s/", path);
        name = strrchr((*filename)[cnt], '/') + 1;

        if (MSF_FILE_READ_DIR(
                path,
                fileIdx,
                name,
                MAX_HDI_FILE_NAME_SIZE - strlen(path) - 1,
                &type,
                &filesize ) != HDI_FILE_OK)
        {
            break;
        }

        if (type == HDI_FILE_FILETYPE)
        {
            cnt++;
        }

        fileIdx++;

    } while (cnt < file_num);

    return file_num;

}   /* end of get_sec_filename */


/*****************************************************************************
 * FUNCTION
 *  free_sec_filename
 * DESCRIPTION
 *  This function frees memory for security backup file names.
 * PARAMETERS
 *  filename        [IN]            
 *  file_num        [IN]            
 *  a(?)            [IN/OUT]        Filename
 *  b(?)            [IN]            File_num
 * RETURNS
 *  void
 *****************************************************************************/
static void free_sec_filename(char **filename, int file_num)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    WAP_DBG_ASSERT(filename != NULL);
    WAP_DBG_ASSERT(file_num > 0);
    if (file_num <= 0 || filename == NULL)
    {
        return;
    }

    for (i = 0; i < file_num; i++)
    {
        WAP_DBG_ASSERT(filename[i] != NULL);
        if (filename[i])
        {
            MSF_MEM_FREE(MSF_MODID_MSM, filename[i]);
        }
    }

    MSF_MEM_FREE(MSF_MODID_MSM, filename);

}   /* end of free_sec_filename */


/*****************************************************************************
 * FUNCTION
 *  msm_backup_recover_sec_files
 * DESCRIPTION
 *  This function checks whether security files are been corrupted,
 *  if yes, copy all security files and recover from backup folder.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void msm_backup_recover_sec_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i, sec_file_num /* , cksum_size */ ;
    msm_checksum_handle_t handle;
    msm_checksum_t chksum;
    kal_bool recover_need = KAL_FALSE;
    char **sec_file_name = NULL;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if ((sec_file_num = get_sec_filename(MSM_SEC_PATH, &sec_file_name)) == 0)
    {
        return; /* there is no security file */
    }
#if 0   /* johnnie */
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif /* 0 */ 
    handle = msm_load_checksum(MSM_SEC_CHECKSUM_FILENAME, MSM_CHECKSUM_MODE_RDONLY, sec_file_num);
    WAP_DBG_ASSERT(handle != 0);
    if (handle == 0)
    {
        free_sec_filename(sec_file_name, sec_file_num);
        return;
    }

    /*
     * in case of some files are disappeared. needed ?
     * cksum_size = HDIa_fileGetSize(MSM_SEC_CHECKSUM_FILENAME);
     * 
     * if(cksum_size != (int)(sizeof(msm_checksum_t)*sec_file_num))
     * recover_need = KAL_TRUE;
     */
    for (i = 0; i < sec_file_num && recover_need == KAL_FALSE; i++)
    {
        chksum = msm_get_checksum(handle, i, sec_file_num);

        if (chksum < 0 || msm_compute_checksum(sec_file_name[i]) != chksum)
            /* once one sec file is corrupted, we recover all sec files */
        {
            recover_need = KAL_TRUE;
        }
    }

    msm_unload_checksum(handle, sec_file_num);

    if (recover_need == KAL_TRUE)
    {
        extern void wap_read_factory_setting(kal_uint8 file_idx);

        msm_remove_files_under_dir(MSM_SEC_PATH);

        wap_read_factory_setting(1);
    }

    free_sec_filename(sec_file_name, sec_file_num);

}   /* end of msm_backup_recover_sec_files */


/*****************************************************************************
 * FUNCTION
 *  msm_compute_checksum_sec_files
 * DESCRIPTION
 *  This function computes the checksum for security files.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void msm_compute_checksum_sec_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int i, sec_file_num;
    char **sec_file_name = NULL;
    msm_checksum_handle_t handle;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if ((sec_file_num = get_sec_filename(MSM_SEC_PATH, &sec_file_name)) == 0)
    {
        return; /* there is no security file */
    }

    handle = msm_load_checksum(MSM_SEC_CHECKSUM_FILENAME, MSM_CHECKSUM_MODE_RDWR, sec_file_num);

    WAP_DBG_ASSERT(handle != 0);
    if (handle == 0)
    {
        free_sec_filename(sec_file_name, sec_file_num);
        return;
    }

    for (i = 0; i < sec_file_num; i++)
    {
        msm_put_checksum(handle, i, msm_compute_checksum(sec_file_name[i]), sec_file_num);
    }

    /*
     * need to set the file size ? KEVIN 
     * HDIa_fileSetSize(handle->fd, sizeof(msm_checksum_t)*sec_file_num);
     */

    msm_unload_checksum(handle, sec_file_num);

    free_sec_filename(sec_file_name, sec_file_num);

}   /* end of msm_compute_checksum_sec_files */
#endif /* WAP_SEC_SUPPORT */

#ifdef MSF_REGISTRY_SUPPORT
/*****************************************************************************
 * FUNCTION
 *  msm_backup_recover_reg_files
 * DESCRIPTION
 *  This function checks whether registry files are been corrupted,
 *  if yes, recover from default registry.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void msm_backup_recover_reg_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    msm_checksum_handle_t handle;
    msm_checksum_t chksum, chksum1;
    kal_bool recover_need = KAL_FALSE;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    handle = msm_load_checksum(MSM_REG_CHECKSUM_FILENAME, MSM_CHECKSUM_MODE_RDONLY, 1);
    WAP_DBG_ASSERT(handle != 0);
    if (handle == 0)
    {
        return;
    }

    chksum = msm_get_checksum(handle, 0, 1);
    chksum1 = msm_compute_checksum(WAP_MSM_REGISTRY_FILE);
    if (chksum < 0 || chksum1 != chksum)
    {
        recover_need = KAL_TRUE;
    }

    msm_unload_checksum(handle, 1);

    if (recover_need == KAL_TRUE)
    {
        MSF_FILE_REMOVE(WAP_MSM_REGISTRY_FILE);
    }

}   /* end of msm_backup_recover_reg_files */


/*****************************************************************************
 * FUNCTION
 *  msm_compute_checksum_reg_files
 * DESCRIPTION
 *  This function computes the checksum for registry files.
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
void msm_compute_checksum_reg_files()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    msm_checksum_handle_t handle;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    handle = msm_load_checksum(MSM_REG_CHECKSUM_FILENAME, MSM_CHECKSUM_MODE_RDWR, 1);

    WAP_DBG_ASSERT(handle != 0);
    if (handle == 0)
    {
        return;
    }

    msm_put_checksum(handle, 0, msm_compute_checksum(WAP_MSM_REGISTRY_FILE), 1);

    msm_unload_checksum(handle, 1);

}   /* end of msm_compute_checksum_reg_files */
#endif /*MSF_REGISTRY_SUPPORT*/
/*
 * for download files quota checking
 */


/*****************************************************************************
 * FUNCTION
 *  msm_get_folder_info
 * DESCRIPTION
 *  This function gets the folder information, eg, file number, file size.
 * PARAMETERS
 *  path            [?]             
 *  file_num        [?]             
 *  file_size       [?]             
 *  c(?)            [IN/OUT]        File_size (will be incremented)
 *  a(?)            [IN]            Path
 *  b(?)            [IN/OUT]        File_num  (will be incremented)
 * RETURNS
 *  void
 *****************************************************************************/
void msm_get_folder_info(char *path, int *file_num, long *file_size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    char name[MAX_HDI_FILE_NAME_SIZE];
    int type;
    long filesize;
    int fileIdx = 0;    /* reset */

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while (MSF_FILE_READ_DIR_LONG(path, fileIdx, name, MAX_HDI_FILE_NAME_SIZE, &type, &filesize ) == HDI_FILE_OK)
    {
        if (type == HDI_FILE_FILETYPE)
        {
            (*file_num)++;
            *file_size += filesize;
        }
        fileIdx++;
    }

}   /* end of msm_get_folder_info */


/*****************************************************************************
 * FUNCTION
 *  msm_get_download_file_info
 * DESCRIPTION
 *  This function gets how many download files and the total file size.
 * PARAMETERS
 *  file_num        [?]             
 *  file_size       [?]             
 *  c(?)            [IN/OUT]        File_size
 *  b(?)            [IN/OUT]        File_num
 * RETURNS
 *  void
 *****************************************************************************/
static void msm_get_download_file_info(int *file_num, long *file_size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (file_num == NULL || file_size == NULL)
    {
        return;
    }

    *file_num = *file_size = 0; /* reset */

    msm_get_folder_info(WAP_IMAGE_FOLDER, file_num, file_size);
    msm_get_folder_info(WAP_SOUND_FOLDER, file_num, file_size);

}   /* end of msm_get_download_file_info */


/*****************************************************************************
 * FUNCTION
 *  msm_add_download_file_check
 * DESCRIPTION
 *  This function checks whether the new download can be saved or not
 *  based on current file number/size.
 * PARAMETERS
 *  file_size       [IN]        
 *  b(?)            [IN]        File_size
 * RETURNS
 *  0:  ok
 *  -1: file number exceeded
 *  -2: file size exceeded
 *****************************************************************************/
int msm_add_download_file_check(long file_size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if ((wap_download_file_size_g + file_size) > MAX_TOTAL_DOWNLOAD_SIZE)
    {
        return -2;
    }

    return 0;

}   /* end of msm_download_file_check */


/*****************************************************************************
 * FUNCTION
 *  msm_remove_download_file_stats
 * DESCRIPTION
 *  This function updates the download file and size when removing an file
 * PARAMETERS
 *  file_size       [IN]        
 *  b(?)            [IN]        File_size
 * RETURNS
 *  void
 *****************************************************************************/
void msm_remove_download_file_stats(long file_size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (wap_download_file_num_g < 0)
    {
        return; /* The cache is already invalid, we don't need to update it */
    }

    if (wap_download_file_num_g > 0)
    {
        wap_download_file_num_g--;
    }

    wap_download_file_size_g -= file_size;
    if (wap_download_file_size_g < 0)
    {
        wap_download_file_size_g = 0;
    }
}


/*****************************************************************************
 * FUNCTION
 *  msm_update_download_file_stats
 * DESCRIPTION
 *  This function updates the download file and size.
 * PARAMETERS
 *  file_size       [IN]        
 *  b(?)            [IN]        File_size
 * RETURNS
 *  void
 *****************************************************************************/
void msm_update_download_file_stats(long file_size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (wap_download_file_num_g < 0)
    {
        return; /* The cache is already invalid, we don't need to update it */
    }

    wap_download_file_num_g++;
    wap_download_file_size_g += file_size;
}


/*****************************************************************************
 * FUNCTION
 *  msm_invalidate_download_file_stats
 * DESCRIPTION
 *  Invalidate the cached value of quota size
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
int msm_invalidate_download_file_stats()
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    wap_download_file_num_g = -1;
    return 0;
}


/*****************************************************************************
 * FUNCTION
 *  msm_rescan_download_file_stats
 * DESCRIPTION
 *  rescan the directories for downloaded files to get the total size
 * PARAMETERS
 *  void
 * RETURNS
 *  void
 *****************************************************************************/
int msm_rescan_download_file_stats(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    if (wap_download_file_num_g < 0)
    {
        msm_get_download_file_info(&wap_download_file_num_g, &wap_download_file_size_g);
    }
    return 0;
}

#if 0
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
/* under construction !*/
#endif

/*****************************************************************************
 * FUNCTION
 *  msm_get_folder_info_recursive
 * DESCRIPTION
 *  This function gets the folder information, eg, file number, file size.
 * PARAMETERS
 *  path            [?]             
 *  file_num        [?]             
 *  file_size       [?]             
 *  c(?)            [IN/OUT]        File_size (will be incremented)
 *  a(?)            [IN]            Path
 *  b(?)            [IN/OUT]        File_num  (will be incremented)
 * RETURNS
 *  void
 *****************************************************************************/
/*
 * WARNING!!! This is recursive and it should used for test only .
 * * Otherwise, be careful of stack overflow.
 */
void msm_get_folder_info_recursive(char *path, int *file_num, long *file_size)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    char name[MAX_HDI_FILE_NAME_SIZE];
    int type;
    long filesize;
    int fileIdx = 0;    /* reset */

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    while (MSF_FILE_READ_DIR_LONG(path, fileIdx, name, MAX_HDI_FILE_NAME_SIZE, &type, &filesize ) == HDI_FILE_OK)
    {
        char *tmp_path;

        tmp_path = msf_cmmn_str3cat(MSF_MODID_MSM, path, "\\", name);
        if (type == HDI_FILE_FILETYPE)
        {
            filesize = MSF_FILE_GETSIZE(tmp_path );
            (*file_num)++;
            *file_size += (filesize > 0) ? filesize : 0;
        }
        else
        {
            msm_get_folder_info_recursive(tmp_path, file_num, file_size);
        }
        MSF_MEM_FREE(MSF_MODID_MSM, tmp_path);
        fileIdx++;
    }

}   /* end of msm_get_folder_info */


/*****************************************************************************
 * FUNCTION
 *  msm_get_disk_free_blocks
 * DESCRIPTION
 *  Get the free space of disk
 * PARAMETERS
 *  disk_letter         [IN]        
 *  disk_index(?)       [IN]        The target disk (UNUSED)
 * RETURNS
 *  size in bytes
 *****************************************************************************/
static kal_uint32 msm_get_disk_free_blocks(int disk_letter)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    char path[8];
    WCHAR wpath[8];
    FS_DiskInfo diskinfo;
    kal_uint32 freebytes;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    sprintf(path, "%c:\\", (char)disk_letter);
    widget_utf8_to_ucs2_string((kal_uint8*) wpath, 8 * 2, (kal_uint8*) path);

    FS_GetDiskInfo(wpath, &diskinfo, FS_DI_FREE_SPACE | FS_DI_BASIC_INFO);
    freebytes = diskinfo.FreeClusters * diskinfo.SectorsPerCluster * diskinfo.BytesPerSector;
    return freebytes;
}

#if defined(__FS_QM_SUPPORT__)
/*****************************************************************************
 * FUNCTION
 *  msm_get_folder_quota_space
 * DESCRIPTION
 *  
 * PARAMETERS
 *  path_name       [?]     
 * RETURNS
 *  
 *****************************************************************************/
static kal_uint32 msm_get_folder_quota_space(char *path_name)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/
    int ret;

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    WAP_DBG_ASSERT(path_name[0] == 'Z');
    WAP_DBG_ASSERT(path_name[strlen(path_name) - 1] == '\\');

    ret = FS_QmGetFree((BYTE*) path_name);
    if (ret < 0)
    {
        /* WAP_DBG_ASSERT(0); */
        ret = 0;
    }
    return (kal_uint32) ret;
}
#endif /* defined(__FS_QM_SUPPORT__) */

/*****************************************************************************
 * FUNCTION
 *  msm_get_disk_free_space
 * DESCRIPTION
 *  
 * PARAMETERS
 *  disk_index      [IN]        
 * RETURNS
 *  
 *****************************************************************************/
kal_uint32 msm_get_disk_free_space(kal_uint8 disk_index)
{
#ifndef __MTK_TARGET__
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/
    return 1024 * 1024;

#elif defined(__FS_QM_SUPPORT__)
    /* Only system disk has quota management */

    switch (disk_index)
    {
    #ifdef OBIGO_Q03C_MMS_V01
        case WAP_STORAGE_MMS:

    #ifdef MMS_IN_LARGE_STORAGE
            return msm_get_disk_free_blocks(mms_get_disk_label(WAP_STORAGE_MMS));
    #else 
            return msm_get_folder_quota_space("Z:\\@mms\\");
    #endif 

    #endif /* OBIGO_Q03C_MMS_V01 */ 

        case WAP_STORAGE_PUBLIC:
            /* FIXME. there might be more than one public folder */
            return msm_get_disk_free_blocks(mms_get_disk_label(WAP_STORAGE_PUBLIC));

        case WAP_STORAGE_SYSTEM:
        default:
            WAP_DBG_ASSERT(disk_index == WAP_STORAGE_SYSTEM);
            return msm_get_folder_quota_space("Z:\\@wap\\");
    }

#else 

    return msm_get_disk_free_blocks(mms_get_disk_label(disk_index));

#endif 
}
#endif /*Q03C_IND_MOD_ARCH_SUPPORT*/
