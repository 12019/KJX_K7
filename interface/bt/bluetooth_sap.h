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

/*****************************************************************************
 *
 * Filename:
 * ---------
 *   bluetooth_sap.h
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file is defines SAP for BT.
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
   MSG_ID_BT_NOTIFY_EVM_IND = BT_MSG_CODE_BEGIN,
   MSG_ID_BT_POWERON_REQ,
   MSG_ID_BT_POWERON_CNF,
   MSG_ID_BT_ENGINEER_MODE_POWERON_REQ,
   MSG_ID_BT_ENGINEER_MODE_POWERON_CNF,
   MSG_ID_BT_POWEROFF_REQ,
   MSG_ID_BT_POWEROFF_CNF,
   MSG_ID_BT_ENGINEER_MODE_POWEROFF_REQ,
   MSG_ID_BT_ENGINEER_MODE_POWEROFF_CNF,   
   MSG_ID_BT_RESET_REQ_IND,
   MSG_ID_BT_MMI_RESET_REQ,
   MSG_ID_BT_MMI_RESET_CNF,
   MSG_ID_BT_L4C_RESET_REQ,
   MSG_ID_BT_L4C_RESET_CNF,   
   MSG_ID_BT_RESTART_REQ,
   MSG_ID_BT_LOCK_REQ,	/*LAWMO*/
   MSG_ID_BT_READY_IND,
   MSG_ID_BT_DATA_TO_READ_IND,
   MSG_ID_BT_HOST_WAKE_UP_IND,
   MSG_ID_BT_WIFI_SET_CHNL_REQ,         
   MSG_ID_BT_SET_UART_RX_SPEED_LOW_REQ,
   MSG_ID_BT_SET_UART_RX_SPEED_HIGH_REQ,
   MSG_ID_BT_DETECT_CHIP_REQ,
   MSG_ID_BT_DETECT_CHIP_CNF,
   MSG_ID_BT_ACTIVE_UART_CHANGE_REQ,
   MSG_ID_BT_JSR_TEST_INIF_REQ,   
   MSG_ID_BT_JSR_TEST_CMD1_REQ,   
   MSG_ID_BT_JSR_TEST_CMD2_REQ,      
   MSG_ID_BT_JSR_TEST_CMD3_REQ,   
   MSG_ID_BT_JSR_TEST_CMD4_REQ,      
   MSG_ID_BT_JSR_TEST_CMD5_REQ,      
   MSG_ID_BT_JSR_TEST_CMD6_REQ,  
   MSG_ID_BT_JSR_TEST_CMD7_REQ,  
   MSG_ID_BT_JSR_TEST_CMD8_REQ,
   MSG_ID_BT_JSR_TEST_CMD9_REQ,
   MSG_ID_BT_JSR_TEST_CMD10_REQ,
   MSG_ID_BT_JSR_TEST_CMD11_REQ,
   MSG_ID_BT_JSR_TEST_CMD12_REQ,
   MSG_ID_BT_JSR_TEST_CMD13_REQ,
   MSG_ID_BT_JSR_TEST_CMD14_REQ,
   MSG_ID_BT_JSR_TEST_CMD15_REQ,
   /*EM test command*/
   MSG_ID_BT_TEST_MODE_REQ,      
   MSG_ID_BT_TEST_CMD_REQ,
   MSG_ID_BT_L4C_TEST_CMD_CNF,
   MSG_ID_BT_PCM_LB_REQ,
   MSG_ID_BT_PCM_LB_CNF,
   MSG_ID_BT_SET_BD_ADDR_REQ,
   MSG_ID_BT_SET_BD_ADDR_CNF,
   MSG_ID_BT_SET_POWER_TABLE_REQ,
   MSG_ID_BT_SET_ANA_TRIM_REQ,
   MSG_ID_BT_L4C_AT_GENERAL_CNF,
   MSG_ID_BT_GET_BD_ADDR_REQ,
   MSG_ID_BT_GET_BD_ADDR_CNF,
   MSG_ID_BT_GET_BT_VERSION_REQ,
   MSG_ID_BT_GET_BT_VERSION_CNF,   
   MSG_ID_BT_ENGINEER_MODE_CNF,   
   MSG_ID_BT_ENGINEER_MODE_TXRX_TEST_REQ,
   MSG_ID_BT_ENGINEER_MODE_TXRX_TEST_CNF,
   MSG_ID_BT_ENGINEER_MODE_POWER_TEST_REQ,
   MSG_ID_BT_ENGINEER_MODE_POWER_TEST_CNF,
   MSG_ID_BT_ENGINEER_MODE_DEVICE_TEST_REQ,
   MSG_ID_BT_READ_RSSI_REQ,
   MSG_ID_BT_READ_RSSI_CNF,
   MSG_ID_BT_SSP_DEBUG_MODE_REQ,
   MSG_ID_BT_SSP_DEBUG_MODE_CNF,
    MSG_TAG_BT_SAP_START_MSG,
   /*APP --> SPP, DUN*/
   MSG_TAG_BT_SPP_FIRST_REQ_MSG,
   MSG_ID_BT_SPP_ACTIVATE_REQ = MSG_TAG_BT_SPP_FIRST_REQ_MSG,
   MSG_ID_BT_SPP_CONNECT_REQ, /* Add by stanley to test SPP client: 2007-0313 */
   MSG_ID_BT_SPP_SCO_CONNECT_REQ, 
   MSG_ID_BT_SPP_SEND_DATA_REQ,
   MSG_ID_BT_SPP_GET_DATA_REQ,   
   MSG_ID_BT_SPP_DEACTIVATE_REQ,
   MSG_ID_BT_SPP_DISCONNECT_REQ,
   MSG_ID_BT_SPP_AUDIO_CONNECT_REQ,
   MSG_ID_BT_SPP_AUDIO_DISCONNECT_REQ, 
   MSG_ID_BT_SPP_CONNECT_IND_RES,
   MSG_ID_BT_SPP_AUTH_RSP, 
   /* Add by stanley 2007-0402: Notify BT can check if UART_READY_TO_READ_IND is necessary to send or not becasue MMI is owner of port and can receive data */
   MSG_ID_BT_SPP_UART_OWNER_CNF,
   /* Add by stanley 2007-0402: Notify BT can chage the owner of port and MMI has do something completely for UART_PLUGOUT_IND */
   MSG_ID_BT_SPP_UART_PLUGOUT_CNF,
   MSG_ID_BT_DUN_CONNECT_REQ,   /* for DUN_CLIENT */
   MSG_ID_BT_DUN_ACTIVATE_REQ,
   MSG_ID_BT_DUN_DEACTIVATE_REQ,
   MSG_ID_BT_DUN_DISCONNECT_REQ,
   MSG_ID_BT_DUN_CONNECT_IND_RES,
   MSG_ID_BT_DUN_AUTH_RSP,
   
   /* Add FAX related msg by stanley: 2006-11-22 */
   MSG_ID_BT_FAX_ACTIVATE_REQ,
   MSG_ID_BT_FAX_DEACTIVATE_REQ,
   MSG_ID_BT_FAX_DISCONNECT_REQ,
   MSG_ID_BT_FAX_CONNECT_IND_RES,
   MSG_ID_BT_FAX_AUTH_RSP,
   MSG_TAG_BT_SPP_LAST_REQ_MSG = MSG_ID_BT_FAX_AUTH_RSP, /* Modify by stanley:2006-11-22 */

   /*APP <-- SPP*/
   MSG_ID_BT_SPP_CONNECT_IND,
   MSG_ID_BT_SPP_CONNECT_IND_REQ,
   MSG_ID_BT_SPP_SCO_CONNECT_IND,   
   MSG_ID_BT_SPP_DISCONNECT_IND,
   MSG_ID_BT_SPP_ACTIVATE_CNF,
   MSG_ID_BT_SPP_DEACTIVATE_CNF,
   MSG_ID_BT_SPP_DISCONNECT_CNF,
   MSG_ID_BT_SPP_AUTH_REQ, 
   MSG_ID_BT_SPP_AUDIO_CONNECT_CNF,
   MSG_ID_BT_SPP_AUDIO_CONNECT_IND,
   MSG_ID_BT_SPP_AUDIO_DISCONNECT_CNF,
   MSG_ID_BT_SPP_AUDIO_DISCONNECT_IND, 
   MSG_ID_BT_SPP_SCO_RSSI_IND, 
   MSG_ID_BT_SPP_CONNECT_CNF,  /* Add by stanley for SPP client's cnf to MMI */

   MSG_ID_BT_SPP_UART_OWNER_IND, /* Add by stanley 2007-0401: to notify SPP server that it is the uart owner now */

   /*APP <-- DUN*/
   MSG_ID_BT_DUN_CONNECT_IND,
   MSG_ID_BT_DUN_CONNECT_IND_REQ,
   MSG_ID_BT_DUN_DISCONNECT_IND,
   MSG_ID_BT_DUN_ACTIVATE_CNF,
   MSG_ID_BT_DUN_DEACTIVATE_CNF,
   MSG_ID_BT_DUN_DISCONNECT_CNF,
   MSG_ID_BT_DUN_AUTH_REQ,
   MSG_ID_BT_DUN_CONNECT_CNF,    /* for DUN_CLIENT */

   /*APP <-- FAX: Add by stanley:2006-11-22*/
   MSG_ID_BT_FAX_CONNECT_IND,
   MSG_ID_BT_FAX_CONNECT_IND_REQ,
   MSG_ID_BT_FAX_DISCONNECT_IND,
   MSG_ID_BT_FAX_ACTIVATE_CNF,
   MSG_ID_BT_FAX_DEACTIVATE_CNF,
   MSG_ID_BT_FAX_DISCONNECT_CNF,
   MSG_ID_BT_FAX_AUTH_REQ,

    /*APP --> BMA*/
    MSG_TAG_BT_BM_FIRST_REQ_MSG,
    MSG_ID_BT_BM_DISCOVERY_REQ = MSG_TAG_BT_BM_FIRST_REQ_MSG,
    MSG_ID_BT_BM_DISCOVERY_CANCEL_REQ,
    MSG_ID_BT_BM_WRITE_LOCAL_NAME_REQ,
    MSG_ID_BT_BM_READ_LOCAL_NAME_REQ,
    MSG_ID_BT_BM_READ_REMOTE_NAME_REQ,
    MSG_ID_BT_BM_WRITE_SCANENABLE_MODE_REQ,
    MSG_ID_BT_BM_READ_SCANENABLE_MODE_REQ,
    MSG_ID_BT_BM_READ_LOCAL_ADDR_REQ,
    MSG_ID_BT_BM_READ_LOCAL_COD_REQ,
    MSG_ID_BT_BM_WRITE_LOCAL_COD_REQ,
    MSG_ID_BT_BM_READ_PROPERTY_REQ,
    MSG_ID_BT_BM_WRITE_AUTHENTICATION_MODE_REQ,
    MSG_ID_BT_BM_PIN_CODE_RSP,
    MSG_ID_BT_BM_SECURITY_USER_CONFIRM_RSP,
    MSG_ID_BT_BM_SECURITY_KEYPRESS_NOTIFY_RSP,
    MSG_ID_BT_BM_SECURITY_KEYPRESS_NOTIFY_CANCEL_REQ,   
    MSG_ID_BT_BM_BLOCK_ACTIVE_LINK_REQ,    
    MSG_ID_BT_BM_BLOCK_LIST_UPDATE_REQ,
    MSG_ID_BT_BM_BONDING_REQ,
    MSG_ID_BT_BM_DELETE_TRUST_REQ,
    MSG_ID_BT_BM_DELETE_TRUST_ALL_REQ,
    MSG_ID_BT_BM_BONDING_CANCEL_REQ,
    MSG_ID_BT_BM_PAIRING_CANCEL_REQ,
    MSG_ID_BT_BM_SAVE_SETTING_REQ,
    MSG_ID_BT_BM_RESTORE_SETTING_REQ,
    MSG_ID_BT_BM_SERVICE_SEARCH_REQ,
    MSG_ID_BT_BM_SEARCH_ATTRIBUTE_REQ,
    MSG_ID_BT_BM_SEARCH_RAW_REQ,
    MSG_ID_BT_BM_LINK_ALLOW_REQ,
    MSG_ID_BT_BM_LINK_DISALLOW_REQ,
    MSG_ID_BT_BM_LINK_CONNECT_ACCEPT_NOT_AUTO_REQ,
    MSG_ID_BT_BM_LINK_CONNECT_ACCEPT_RSP,    
    MSG_ID_BT_BM_GET_LINK_STATE_REQ,
    MSG_ID_BT_BM_SET_LINK_STATE_REQ,   
    MSG_TAG_BT_BM_LAST_REQ_MSG = MSG_ID_BT_BM_SET_LINK_STATE_REQ,

    /*BMA --> APP*/
    MSG_TAG_BT_BMAPP_FIRST_REQ_MSG,
    MSG_ID_BT_BM_DISCOVERY_RESULT_IND = MSG_TAG_BT_BMAPP_FIRST_REQ_MSG,
    MSG_ID_BT_BM_DISCOVERY_CNF,
    MSG_ID_BT_BM_DISCOVERY_CANCEL_CNF,
    MSG_ID_BT_BM_WRITE_LOCAL_NAME_CNF,
    MSG_ID_BT_BM_READ_LOCAL_NAME_CNF,
    MSG_ID_BT_BM_READ_REMOTE_NAME_CNF,
    MSG_ID_BT_BM_WRITE_SCANENABLE_MODE_CNF,
    MSG_ID_BT_BM_READ_SCANENABLE_MODE_CNF,
    MSG_ID_BT_BM_READ_LOCAL_ADDR_CNF,
    MSG_ID_BT_BM_READ_LOCAL_COD_CNF,
    MSG_ID_BT_BM_WRITE_LOCAL_COD_CNF,
    MSG_ID_BT_BM_READ_PROPERTY_CNF,
    MSG_ID_BT_BM_WRITE_AUTHENTICATION_MODE_CNF,
    MSG_ID_BT_BM_PIN_CODE_IND,
    MSG_ID_BT_BM_SECURITY_USER_CONFIRM_IND,
    MSG_ID_BT_BM_SECURITY_PASSKEY_NOTIFY_IND,
    MSG_ID_BT_BM_SECURITY_KEYPRESS_NOTIFY_IND,
    MSG_ID_BT_BM_BLOCK_ACTIVE_LINK_CNF,
    MSG_ID_BT_BM_BLOCK_LIST_UPDATE_CNF,
    MSG_ID_BT_BM_BONDING_CNF,
    MSG_ID_BT_BM_BONDING_RESULT_IND,
    MSG_ID_BT_BM_DELETE_TRUST_CNF,
    MSG_ID_BT_BM_DELETE_TRUST_ALL_CNF,
    MSG_ID_BT_BM_BONDING_CANCEL_CNF,
    MSG_ID_BT_BM_PAIRING_CANCEL_CNF,
    MSG_ID_BT_BM_SAVE_SETTING_CNF,
    MSG_ID_BT_BM_RESTORE_SETTING_CNF,
    MSG_ID_BT_BM_SERVICE_SEARCH_RESULT_IND,
    MSG_ID_BT_BM_SERVICE_SEARCH_CNF,
    MSG_ID_BT_BM_SEARCH_ATTRIBUTE_RESULT_IND,
    MSG_ID_BT_BM_SEARCH_ATTRIBUTE_CNF,
    MSG_ID_BT_BM_SEARCH_RAW_RESULT,    
    MSG_ID_BT_BM_SEARCH_RAW_CNF,
    MSG_ID_BT_BM_LINK_STATE_IND,
    MSG_ID_BT_BM_LINK_ALLOW_CNF,
    MSG_ID_BT_BM_LINK_DISALLOW_CNF,    
    MSG_ID_BT_BM_LINK_CONNECT_ACCEPT_IND,    
    MSG_ID_BT_BM_GET_LINK_STATE_CNF,   
    MSG_ID_BT_BM_SET_LINK_STATE_CNF,   
    MSG_TAG_BT_BMAPP_LAST_REQ_MSG = MSG_ID_BT_BM_SET_LINK_STATE_CNF,


    /* APP --> HSG */
    MSG_TAG_BT_HSG_FIRST_REQ_MSG,
    MSG_ID_BT_HSG_ACTIVATE_REQ = MSG_TAG_BT_HSG_FIRST_REQ_MSG,
    MSG_ID_BT_HSG_DEACTIVATE_REQ,
    MSG_ID_BT_HSG_CONNECT_REQ,
	MSG_ID_BT_HSG_CONNECT_IND_RES,
    MSG_ID_BT_HSG_DISCONNECT_REQ,    
    MSG_ID_BT_HSG_BUTTONPRESS_REQ,
    MSG_ID_BT_HSG_MVOLUMEDOWN_REQ,
    MSG_ID_BT_HSG_MVOLUMEUP_REQ,
    MSG_ID_BT_HSG_SVOLUMEDOWN_REQ,
    MSG_ID_BT_HSG_SVOLUMEUP_REQ,  
    MSG_ID_BT_HSG_SPEAKER_GAIN_REQ,
    MSG_ID_BT_HSG_MIC_GAIN_REQ,
    MSG_TAG_BT_HSG_LAST_REQ_MSG = MSG_ID_BT_HSG_MIC_GAIN_REQ,
	
    /* APP <-- HSG */
    MSG_ID_BT_HSG_ACTIVATE_CNF,
    MSG_ID_BT_HSG_DEACTIVATE_CNF,    
    MSG_ID_BT_HSG_CONNECT_CNF,
    MSG_ID_BT_HSG_CONNECT_IND,
	MSG_ID_BT_HSG_CONNECT_IND_REQ,
    MSG_ID_BT_HSG_DISCONNECT_CNF,
    MSG_ID_BT_HSG_DISCONNECT_IND,
    MSG_ID_BT_HSG_SPEAKER_GAIN_CNF,
    MSG_ID_BT_HSG_SPEAKER_GAIN_IND,
    MSG_ID_BT_HSG_MIC_GAIN_IND,
    MSG_ID_BT_HSG_MIC_GAIN_CNF,

   /*APP --> HFG*/
   MSG_TAG_BT_HFG_FIRST_REQ_MSG,
   MSG_ID_BT_HFG_ACTIVATE_REQ = MSG_TAG_BT_HFG_FIRST_REQ_MSG,   
   MSG_ID_BT_HFG_DEACTIVATE_REQ,
   MSG_ID_BT_HFG_DISCONNECT_REQ,
   MSG_ID_BT_HFG_CONNECT_REQ,
   MSG_ID_BT_HFG_CONNECT_IND_RES,
   MSG_ID_BT_HFG_SCO_CONNECT_REQ,
   MSG_ID_BT_HFG_SCO_DISCONNECT_REQ,
   MSG_ID_BT_HFG_SPEAKER_GAIN_REQ,
   MSG_ID_BT_HFG_MIC_GAIN_REQ,
   MSG_ID_BT_HFG_SEND_DATA_REQ,
   MSG_TAG_BT_HFG_LAST_REQ_MSG = MSG_ID_BT_HFG_SEND_DATA_REQ,

   /*APP <-- HFG*/
   MSG_ID_BT_HFG_ACTIVATE_CNF,
   MSG_ID_BT_HFG_DEACTIVATE_CNF,   
   MSG_ID_BT_HFG_CONNECT_CNF,   
   MSG_ID_BT_HFG_CONNECT_IND,
   MSG_ID_BT_HFG_SLC_FINISH_IND,
   MSG_ID_BT_HFG_CONNECT_IND_REQ,
   MSG_ID_BT_HFG_DISCONNECT_CNF,   
   MSG_ID_BT_HFG_DISCONNECT_IND,
   MSG_ID_BT_HFG_SCO_CONNECT_CNF,
   MSG_ID_BT_HFG_SCO_CONNECT_IND,
   MSG_ID_BT_HFG_SCO_DISCONNECT_CNF,
   MSG_ID_BT_HFG_SCO_DISCONNECT_IND,
   MSG_ID_BT_HFG_SPEAKER_GAIN_CNF,
   MSG_ID_BT_HFG_SPEAKER_GAIN_IND,
   MSG_ID_BT_HFG_MIC_GAIN_IND,
   MSG_ID_BT_HFG_MIC_GAIN_CNF,
   MSG_ID_BT_HF_CONNECT_IND,

   /* APP --> HF */
   MSG_TAG_BT_HF_FIRST_REQ_MSG,
   MSG_ID_BT_HF_ACTIVATE_REQ = MSG_TAG_BT_HF_FIRST_REQ_MSG,
   MSG_ID_BT_HF_DEACTIVATE_REQ,
   MSG_ID_BT_HF_CONNECT_REQ,
   MSG_ID_BT_HF_CONNECT_IND_RES,
   MSG_ID_BT_HF_DISCONNECT_REQ,
   MSG_ID_BT_HF_SCO_CONNECT_REQ,
   MSG_ID_BT_HF_SCO_DISCONNECT_REQ,
   MSG_ID_BT_HF_AT_COMMAND_REQ,
   MSG_ID_BT_HF_RESULT_CODE_CNF,
   MSG_ID_BT_HF_ATA_REQ,
   MSG_ID_BT_HF_ATD_NUM_REQ,
   MSG_ID_BT_HF_ATD_MEM_REQ,
   MSG_ID_BT_HF_BLDN_REQ,
   MSG_ID_BT_HF_CHUP_REQ,
   MSG_ID_BT_HF_CMEE_REQ,
   MSG_ID_BT_HF_NREC_REQ,
   MSG_ID_BT_HF_VTS_REQ,
   MSG_ID_BT_HF_VGS_REQ,
   MSG_ID_BT_HF_VGM_REQ,
   MSG_ID_BT_HF_CHLD_REQ,
   MSG_ID_BT_HF_CLIP_REQ,
   MSG_ID_BT_HF_CCWA_REQ,
   MSG_ID_BT_HF_COPS_SET_REQ,
   MSG_ID_BT_HF_COPS_REQ,
   MSG_ID_BT_HF_CNUM_REQ,
   MSG_ID_BT_HF_BVRA_REQ,
   MSG_ID_BT_HF_BINP_REQ,
   MSG_ID_BT_HF_BTRH_READ_REQ,
   MSG_ID_BT_HF_BTRH_SET_REQ,
   MSG_ID_BT_HF_CLCC_REQ,
   MSG_TAG_BT_HF_LAST_REQ_MSG = MSG_ID_BT_HF_CLCC_REQ,
   
   /*APP <-- HF*/
   MSG_ID_BT_HF_ACTIVATE_CNF,
   MSG_ID_BT_HF_DEACTIVATE_CNF,
   MSG_ID_BT_HF_CONNECT_CNF,
   MSG_ID_BT_HF_CONNECT_IND_REQ,
   MSG_ID_BT_HF_DISCONNECT_CNF,
   MSG_ID_BT_HF_DISCONNECT_IND,
   MSG_ID_BT_HF_SCO_CONNECT_CNF,
   MSG_ID_BT_HF_SCO_CONNECT_IND,
   MSG_ID_BT_HF_SCO_DISCONNECT_CNF,
   MSG_ID_BT_HF_SCO_DISCONNECT_IND,
   MSG_ID_BT_HF_AT_COMMAND_CNF,
   MSG_ID_BT_HF_RESULT_CODE_IND,
   MSG_ID_BT_HF_ATA_CNF,
   MSG_ID_BT_HF_ATD_NUM_CNF,
   MSG_ID_BT_HF_ATD_MEM_CNF,
   MSG_ID_BT_HF_BLDN_CNF,
   MSG_ID_BT_HF_CHUP_CNF,
   MSG_ID_BT_HF_CMEE_CNF,
   MSG_ID_BT_HF_NREC_CNF,
   MSG_ID_BT_HF_VTS_CNF,
   MSG_ID_BT_HF_VGS_CNF,
   MSG_ID_BT_HF_VGM_CNF,
   MSG_ID_BT_HF_CHLD_CNF,
   MSG_ID_BT_HF_CLIP_CNF,
   MSG_ID_BT_HF_CCWA_CNF,
   MSG_ID_BT_HF_COPS_SET_CNF,
   MSG_ID_BT_HF_COPS_CNF,
   MSG_ID_BT_HF_CNUM_CNF,
   MSG_ID_BT_HF_BVRA_CNF,
   MSG_ID_BT_HF_BINP_CNF,
   MSG_ID_BT_HF_BTRH_READ_CNF,
   MSG_ID_BT_HF_BTRH_SET_CNF,
   MSG_ID_BT_HF_CLCC_CNF,
   MSG_ID_BT_HF_VGS_IND,
   MSG_ID_BT_HF_VGM_IND,
   MSG_ID_BT_HF_BSIR_IND,
   MSG_ID_BT_HF_CIEV_SERVICE_IND,
   MSG_ID_BT_HF_CIEV_CALL_IND,
   MSG_ID_BT_HF_CIEV_CALLSETUP_IND,
   MSG_ID_BT_HF_CIEV_CALLHELD_IND,
   MSG_ID_BT_HF_CIEV_SIGNAL_IND,
   MSG_ID_BT_HF_CIEV_ROAM_IND,
   MSG_ID_BT_HF_CIEV_BATTCHG_IND,
   MSG_ID_BT_HF_RING_IND,
   MSG_ID_BT_HF_CLIP_IND,
   MSG_ID_BT_HF_CCWA_IND,
   MSG_ID_BT_HF_BVRA_IND,
   MSG_ID_BT_HF_BTRH_IND,
   
   /*APP --> HIDD*/
   MSG_TAG_BT_HIDD_FIRST_REQ_MSG,
   MSG_ID_BT_HIDD_ACTIVATE_REQ = MSG_TAG_BT_HIDD_FIRST_REQ_MSG,   
   MSG_ID_BT_HIDD_DEACTIVATE_REQ,
   MSG_ID_BT_HIDD_CONNECT_REQ,
   MSG_ID_BT_HIDD_CONNECTION_AUTHORIZE_RSP,
   MSG_ID_BT_HIDD_CONTROL_REQ,
   MSG_ID_BT_HIDD_DISCONNECT_REQ,
   MSG_ID_BT_HIDD_INTERRUPT_DATA_REQ,
   MSG_ID_BT_HIDD_GET_REPORT_RSP,
   MSG_ID_BT_HIDD_SET_REPORT_RSP,
   MSG_ID_BT_HIDD_GET_PROTOCOL_RSP,
   MSG_ID_BT_HIDD_SET_PROTOCOL_RSP,
   MSG_ID_BT_HIDD_GET_IDLE_RATE_RSP,
   MSG_ID_BT_HIDD_SET_IDLE_RATE_RSP,
   MSG_TAG_BT_HIDD_LAST_REQ_MSG = MSG_ID_BT_HIDD_SET_IDLE_RATE_RSP,

   /*APP <-- HIDD*/
   MSG_ID_BT_HIDD_ACTIVATE_CNF,
   MSG_ID_BT_HIDD_DEACTIVATE_CNF,   
   MSG_ID_BT_HIDD_CONNECT_CNF,   
   MSG_ID_BT_HIDD_CONNECT_IND,
   MSG_ID_BT_HIDD_CONNECTION_AUTHORIZE_IND,
   MSG_ID_BT_HIDD_DISCONNECT_CNF,   
   MSG_ID_BT_HIDD_DISCONNECT_IND,
   MSG_ID_BT_HIDD_CONTROL_CNF,
   MSG_ID_BT_HIDD_CONTROL_IND,
   MSG_ID_BT_HIDD_INTERRUPT_DATA_CNF,
   MSG_ID_BT_HIDD_INTERRUPT_DATA_IND,
   MSG_ID_BT_HIDD_GET_REPORT_IND,
   MSG_ID_BT_HIDD_SET_REPORT_IND,
   MSG_ID_BT_HIDD_GET_PROTOCOL_IND,
   MSG_ID_BT_HIDD_SET_PROTOCOL_IND,
   MSG_ID_BT_HIDD_GET_IDLE_RATE_IND,
   MSG_ID_BT_HIDD_SET_IDLE_RATE_IND,
   MSG_ID_BT_HIDD_UNPLUG_IND,

   /*APP --> AVRCP*/
   MSG_TAG_BT_AVCTP_FIRST_REQ_MSG,
   MSG_ID_BT_AVCTP_ACTIVATE_REQ = MSG_TAG_BT_AVCTP_FIRST_REQ_MSG,   
   MSG_ID_BT_AVCTP_INIT_REQ,
   MSG_ID_BT_AVCTP_CONNECT_REQ,
   MSG_ID_BT_AVCTP_CONNECT_RSP,            
   MSG_ID_BT_AVCTP_DISCONNECT_REQ,     
   MSG_ID_BT_AVCTP_DATA_REQ,    
   MSG_TAG_BT_AVCTP_LAST_REQ_MSG = MSG_ID_BT_AVCTP_DATA_REQ,

   
   /*A2DP*/
   // for MMI
   MSG_ID_BT_A2DP_ACTIVATE_REQ,
   MSG_ID_BT_A2DP_ACTIVATE_CNF,
   MSG_ID_BT_A2DP_DEACTIVATE_REQ,
   MSG_ID_BT_A2DP_DEACTIVATE_CNF,
   MSG_ID_BT_A2DP_SIGNAL_CONNECT_REQ,
   MSG_ID_BT_A2DP_SIGNAL_CONNECT_CNF,
   MSG_ID_BT_A2DP_SIGNAL_CONNECT_IND,
   MSG_ID_BT_A2DP_SIGNAL_DISCONNECT_REQ,
   MSG_ID_BT_A2DP_SIGNAL_DISCONNECT_CNF,
   MSG_ID_BT_A2DP_SIGNAL_DISCONNECT_IND,
   // for MED
   MSG_ID_BT_A2DP_SEP_DISCOVER_REQ,
   MSG_ID_BT_A2DP_SEP_DISCOVER_CNF,
   MSG_ID_BT_A2DP_SEP_DISCOVER_IND,
   MSG_ID_BT_A2DP_SEP_DISCOVER_RES,
   MSG_ID_BT_A2DP_CAPABILITIES_GET_REQ,
   MSG_ID_BT_A2DP_CAPABILITIES_GET_CNF,
   MSG_ID_BT_A2DP_CAPABILITIES_GET_IND,
   MSG_ID_BT_A2DP_CAPABILITIES_GET_RES,
   MSG_ID_BT_A2DP_STREAM_CONFIG_REQ,
   MSG_ID_BT_A2DP_STREAM_CONFIG_CNF,
   MSG_ID_BT_A2DP_STREAM_CONFIG_IND,
   MSG_ID_BT_A2DP_STREAM_CONFIG_RES,
   MSG_ID_BT_A2DP_STREAM_RECONFIG_REQ,
   MSG_ID_BT_A2DP_STREAM_RECONFIG_CNF,
   MSG_ID_BT_A2DP_STREAM_RECONFIG_IND,
   MSG_ID_BT_A2DP_STREAM_RECONFIG_RES,
   MSG_ID_BT_A2DP_STREAM_OPEN_REQ,
   MSG_ID_BT_A2DP_STREAM_OPEN_CNF,
   MSG_ID_BT_A2DP_STREAM_OPEN_IND,
   MSG_ID_BT_A2DP_STREAM_OPEN_RES,
   MSG_ID_BT_A2DP_STREAM_START_REQ,
   MSG_ID_BT_A2DP_STREAM_START_CNF,
   MSG_ID_BT_A2DP_STREAM_START_IND,
   MSG_ID_BT_A2DP_STREAM_START_RES,
   MSG_ID_BT_A2DP_STREAM_PAUSE_REQ,
   MSG_ID_BT_A2DP_STREAM_PAUSE_CNF,
   MSG_ID_BT_A2DP_STREAM_PAUSE_IND,
   MSG_ID_BT_A2DP_STREAM_PAUSE_RES,
   MSG_ID_BT_A2DP_STREAM_QOS_IND,
   MSG_ID_BT_A2DP_STREAM_DATA_SEND_REQ,
   MSG_ID_BT_A2DP_STREAM_CLOSE_REQ,
   MSG_ID_BT_A2DP_STREAM_CLOSE_CNF,
   MSG_ID_BT_A2DP_STREAM_CLOSE_IND,
   MSG_ID_BT_A2DP_STREAM_CLOSE_RES,
   MSG_ID_BT_A2DP_STREAM_ABORT_REQ,
   MSG_ID_BT_A2DP_STREAM_ABORT_CNF,
   MSG_ID_BT_A2DP_STREAM_ABORT_IND,
   MSG_ID_BT_A2DP_STREAM_ABORT_RES,

   /*AVRCP*/   
   MSG_ID_BT_AVRCP_ACTIVATE_REQ,
   MSG_ID_BT_AVRCP_ACTIVATE_CNF,
   MSG_ID_BT_AVRCP_DEACTIVATE_REQ,
   MSG_ID_BT_AVRCP_DEACTIVATE_CNF,
   MSG_ID_BT_AVRCP_CONNECT_REQ,
   MSG_ID_BT_AVRCP_CONNECT_CNF,
   MSG_ID_BT_AVRCP_CONNECT_IND,
   MSG_ID_BT_AVRCP_CONNECT_IND_RES,
   MSG_ID_BT_AVRCP_DISCONNECT_REQ,
   MSG_ID_BT_AVRCP_DISCONNECT_CNF, 
   MSG_ID_BT_AVRCP_DISCONNECT_IND,
   
   MSG_ID_BT_AVRCP_CMD_FRAME_REQ,
   MSG_ID_BT_AVRCP_CMD_FRAME_CNF,
   MSG_ID_BT_AVRCP_CMD_FRAME_IND,
   MSG_ID_BT_AVRCP_CMD_FRAME_IND_RES,


   MSG_TAG_BT_TEST_FIRST_REQ_MSG,

   MSG_ID_BT_SDP_TEST_ACTIVATE_REQ = MSG_TAG_BT_TEST_FIRST_REQ_MSG,
   MSG_ID_BT_SDP_TEST_CLOSE_REQ,
   MSG_ID_BT_RFCOMM_TEST_ACTIVATE_REQ,
   MSG_ID_BT_L2CAP_TEST_CMD_REQ,
   MSG_ID_BT_GAP_TEST_CMD_REQ,
   MSG_ID_BT_AVDTP_TEST_CMD_REQ,
   MSG_ID_BT_JBT_TEST_CMD_REQ,
   MSG_ID_BT_SIMAP_TEST_ACTIVATE_REQ,
   MSG_TAG_BT_TEST_LAST_REQ_MSG = MSG_ID_BT_SIMAP_TEST_ACTIVATE_REQ,
   
   MSG_TAG_BT_SDPDB_FIRST_REQ_MSG,
   MSG_ID_BT_SDPDB_REGISTER_REQ = MSG_TAG_BT_SDPDB_FIRST_REQ_MSG,
   MSG_ID_BT_SDPDB_DEREGISTER_REQ,
   MSG_TAG_BT_SDPDB_LAST_REQ_MSG = MSG_ID_BT_SDPDB_DEREGISTER_REQ,
   MSG_ID_BT_SDPDB_REGISTER_CNF,
   MSG_ID_BT_SDPDB_DEREGISTER_CNF,
   
   /* JSR82 SDPDB REGISTERATION */
   MSG_TAG_BT_APP_SDPDB_FIRST_MSG,
   MSG_ID_BT_APP_SDPDB_GET_HANDLE_REQ = MSG_TAG_BT_APP_SDPDB_FIRST_MSG,
   MSG_ID_BT_APP_SDPDB_REGISTER_REQ,
   MSG_ID_BT_APP_SDPDB_RETRIEVE_RECOED_REQ,
   MSG_ID_BT_APP_SDPDB_DEREGISTER_REQ,
   MSG_ID_BT_APP_SDPDB_GET_HANDLE_CNF,
   MSG_ID_BT_APP_SDPDB_REGISTER_CNF,
   MSG_ID_BT_APP_SDPDB_RETRIEVE_RECOED_CNF,
   MSG_ID_BT_APP_SDPDB_DEREGISTER_CNF,
   MSG_TAG_BT_APP_SDPDB_LAST_MSG = MSG_ID_BT_APP_SDPDB_DEREGISTER_CNF,

   /*GOEP*/
   MSG_ID_GOEP_REGISTER_SERVER_REQ,
   MSG_ID_GOEP_REGISTER_SERVER_RSP,
   MSG_ID_GOEP_DEREGISTER_SERVER_REQ,
   MSG_ID_GOEP_DEREGISTER_SERVER_RSP,
   MSG_ID_GOEP_CONNECT_IND,
   MSG_ID_GOEP_CONNECT_RES,
   MSG_ID_GOEP_PUSH_IND,
   MSG_ID_GOEP_PUSH_RES,
   MSG_ID_GOEP_PULL_IND,
   MSG_ID_GOEP_PULL_RES,
   MSG_ID_GOEP_SET_FOLDER_IND,
   MSG_ID_GOEP_SET_FOLDER_RES,
   MSG_ID_GOEP_ABORT_IND,
   MSG_ID_GOEP_ABORT_RES,
   MSG_ID_GOEP_AUTH_REQ,
   MSG_ID_GOEP_AUTH_RSP,
   MSG_ID_GOEP_REGISTER_CLIENT_REQ,
   MSG_ID_GOEP_REGISTER_CLIENT_RSP,
   MSG_ID_GOEP_DEREGISTER_CLIENT_REQ,
   MSG_ID_GOEP_DEREGISTER_CLIENT_RSP,
   MSG_ID_GOEP_CONNECT_REQ,
   MSG_ID_GOEP_CONNECT_RSP,
   MSG_ID_GOEP_PUSH_REQ,
   MSG_ID_GOEP_PUSH_RSP,
   MSG_ID_GOEP_PULL_REQ,
   MSG_ID_GOEP_PULL_RSP,
   MSG_ID_GOEP_SET_FOLDER_REQ,
   MSG_ID_GOEP_SET_FOLDER_RSP,
   MSG_ID_GOEP_ABORT_REQ,
   MSG_ID_GOEP_ABORT_RSP,
   MSG_ID_GOEP_DISCONNECT_REQ,
   MSG_ID_GOEP_DISCONNECT_RSP,
   MSG_ID_GOEP_DISCONNECT_IND,
   MSG_ID_GOEP_DISCONNECT_RES,
   MSG_ID_GOEP_TPDISCONNECT_REQ,
   MSG_ID_GOEP_AUTH_IND,
   MSG_ID_GOEP_AUTH_RES,
   MSG_ID_GOEP_OPP_SUPPORTED_FORMATS_IND,
   MSG_ID_GOEP_AUTHORIZE_IND,
   MSG_ID_GOEP_AUTHORIZE_RES,
      
   MSG_TAG_BT_APP_REG_SERVICE_FIRST_REQ_MSG,
   MSG_ID_BT_RECORD_REG_REQ = MSG_TAG_BT_APP_REG_SERVICE_FIRST_REQ_MSG,
   MSG_ID_BT_RECORD_UNREQ_REQ,
   MSG_ID_BT_RECORD_REQ_CNF,
   MSG_ID_BT_RECORD_UNREQ_CNF,
   MSG_TAG_BT_APP_REG_SERVICE_LAST_REQ_MSG = MSG_ID_BT_RECORD_UNREQ_CNF,

      
   /* SIM Access Profile : SIMAP */

   /* APP --> BT SIMAP */
   MSG_TAG_BT_SIMAP_FIRST_REQ_MSG,
   MSG_ID_BT_SIMAP_ACTIVATE_REQ = MSG_TAG_BT_SIMAP_FIRST_REQ_MSG,
   MSG_ID_BT_SIMAP_DEACTIVATE_REQ,
   MSG_ID_BT_SIMAP_AUTH_RSP,
   MSG_ID_BT_SIMAP_SEND_STATUS_IND_WITH_UNAVAILABLE_REQ,
   /* MSG_ID_BT_SIMAP_DISCONNECT_REQ: This msg is used to notify BT that the user wants to close the connection */
   MSG_ID_BT_SIMAP_DISCONNECT_REQ,
   MSG_TAG_BT_SIMAP_LAST_REQ_MSG = MSG_ID_BT_SIMAP_DISCONNECT_REQ,
   
   /* BT SIMAP --> APP */
   
   /* MSG_ID_BT_SIMAP_AUTH_REQ: This msg is used to let MMI ask the user to accept the remote connection or not */
   MSG_ID_BT_SIMAP_ACTIVATE_CNF,
   MSG_ID_BT_SIMAP_DEACTIVATE_CNF, 
   MSG_ID_BT_SIMAP_AUTH_REQ,
   MSG_ID_BT_SIMAP_CONNECT_CNF,
   MSG_ID_BT_SIMAP_CONNECT_IND,
   MSG_ID_BT_SIMAP_DISCONNECT_CNF,
   /* MSG_ID_BT_SIMAP_DISCONNECT_IND: This msg is used to notify MMI that the connection is closed */  
   MSG_ID_BT_SIMAP_DISCONNECT_IND,
   
   

 
	 /* Bingyi 20091225: Move BT-SIM interface to SIM header files. */

 /* JSR82 SESSION OPERATION */
   MSG_TAG_BT_JSR82_FIRST_MSG,
   MSG_ID_BT_JSR_ACTIVE_REQ = MSG_TAG_BT_JSR82_FIRST_MSG,
   MSG_ID_BT_JSR_ACTIVE_CNF,      
   MSG_ID_BT_JSR_DEACTIVE_REQ,   
   MSG_ID_BT_JSR_DEACTIVE_CNF,  
   MSG_ID_BT_JSR_POWER_OFF_IND,  
   MSG_ID_BT_JSR_POWER_OFF_REQ,   
   MSG_ID_BT_JSR_KICK_NEW_COMMAND,   
   MSG_ID_BT_JSR_PANIC,  
   MSG_ID_BT_JSR82_AUTHENTICATION_REQ,
   MSG_ID_BT_JSR82_AUTHORIZATION_REQ,
   MSG_ID_BT_JSR82_ENCRYPTION_REQ,
   MSG_ID_BT_JSR82_AUTHENTICATION_CNF,
   MSG_ID_BT_JSR82_AUTHORIZATION_CNF,
   MSG_ID_BT_JSR82_ENCRYPTION_CNF,
   MSG_ID_BT_JSR82_RESTROE_ACL_REQ,
   MSG_ID_BT_JSR82_RESTROE_ACL_CNF,   
   MSG_ID_BT_JSR82_CONNECT_REQ,
   MSG_ID_BT_JSR82_CONNECT_CNF,
   MSG_ID_BT_JSR82_ENABLE_SERVICE_REQ,
   MSG_ID_BT_JSR82_ENABLE_SERVICE_CNF,
   MSG_ID_BT_JSR82_TURNON_SERVICE_REQ,
   MSG_ID_BT_JSR82_TURNON_SERVICE_CNF,
   MSG_ID_BT_JSR82_TURNOFF_SERVICE_REQ,
   MSG_ID_BT_JSR82_TURNOFF_SERVICE_CNF,   
   MSG_ID_BT_JSR82_DISABLE_SERVICE_REQ,
   MSG_ID_BT_JSR82_DISABLE_SERVICE_CNF,   
   MSG_ID_BT_JSR82_CONNECT_IND,
   MSG_ID_BT_JSR82_CONNECT_RSP,
   MSG_ID_BT_JSR82_DISCONNECT_REQ,
   MSG_ID_BT_JSR82_DISCONNECT_IND,
   MSG_ID_BT_JSR82_TX_DATA_REQ,
   MSG_ID_BT_JSR82_TX_DATA_CFN,   
   MSG_ID_BT_JSR82_RX_DATA_IND,
   MSG_ID_BT_JSR82_RX_DATA_RSP,   
   /* Add the following SAPs for JSR82 usage: by mtk01411 2007-0916 */    
   MSG_ID_BT_JSR82_RX_READY_IND,
   MSG_ID_BT_JSR82_TX_READY_IND,
   MSG_ID_BT_JSR82_ALLOCATE_TXRX_BUF_REQ,
   MSG_ID_BT_JSR82_ALLOCATE_TXRX_BUF_CNF,
   /* Add two messages related to set acl security: 2007-1119 */
   MSG_ID_BT_JSR82_SET_ACL_SECURITY_REQ,
   MSG_ID_BT_JSR82_SET_ACL_SECURITY_CNF,
   MSG_ID_BT_JSR82_SPP_GET_DATA_REQ,
   MSG_TAG_BT_JSR82_LAST_MSG = MSG_ID_BT_JSR82_SPP_GET_DATA_REQ,   

   /* BCC Test Command */	
   MSG_ID_BT_JSR_TEST_BCC_CMD1_REQ,   
   MSG_ID_BT_JSR_TEST_BCC_CMD2_REQ,      
   MSG_ID_BT_JSR_TEST_BCC_CMD3_REQ,   
   MSG_ID_BT_JSR_TEST_BCC_CMD4_REQ,      
   MSG_ID_BT_JSR_TEST_BCC_CMD5_REQ,      
   MSG_ID_BT_JSR_TEST_BCC_CMD6_REQ,   
   MSG_ID_BT_JSR_TEST_BCC_CMD7_REQ,      
   MSG_ID_BT_JSR_TEST_BCC_CMD8_REQ,   
   MSG_ID_BT_JSR_TEST_BCC_CMD9_REQ,      
   MSG_ID_BT_JSR_TEST_BCC_CMD10_REQ,      
   MSG_ID_BT_JSR_TEST_BCC_CMD11_REQ,   
   MSG_ID_BT_JSR_TEST_BCC_CMD12_REQ,      
   MSG_ID_BT_JSR_TEST_BCC_CMD13_REQ,      
   
   /* BPP */
   MSG_ID_BT_BPP_CONNECT_REQ,
   MSG_ID_BT_BPP_CONNECT_CNF,
   MSG_ID_BT_BPP_AUTHENTICATION_IND,
   MSG_ID_BT_BPP_AUTHENTICATION_RSP,
   MSG_ID_BT_BPP_DISCONNECT_REQ,
   MSG_ID_BT_BPP_DISCONNECT_IND,
   MSG_ID_BT_BPP_GET_PRINTER_ATTR_REQ,
   MSG_ID_BT_BPP_GET_PRINTER_ATTR_CNF,
   MSG_ID_BT_BPP_CREATE_JOB_REQ,
   MSG_ID_BT_BPP_CREATE_JOB_CNF,
   MSG_ID_BT_BPP_EVENT_IND,
   MSG_ID_BT_BPP_SEND_DOC_REQ,
   MSG_ID_BT_BPP_SEND_DOC_CNF,
   MSG_ID_BT_BPP_PROG_UPDATE_IND,
   MSG_ID_BT_BPP_PROG_UPDATE_RSP,

   MSG_ID_BT_BPP_OPEN_REQ,
   MSG_ID_BT_BPP_OPEN_CNF,
   MSG_ID_BT_BPP_GET_ATTR_REQ,
   MSG_ID_BT_BPP_GET_ATTR_CNF,
   MSG_ID_BT_BPP_PRINT_DOC_REQ,
   MSG_ID_BT_BPP_PRINT_DOC_CNF,
   MSG_ID_BT_BPP_CLOSE_REQ,
   MSG_ID_BT_BPP_CLOSE_CNF,
   MSG_ID_BT_BPP_DISC_IND,
   MSG_ID_BT_BPP_OPEN_STATUS_REQ,
   MSG_ID_BT_BPP_OPEN_STATUS_CNF,
   MSG_ID_BT_BPP_JOB_STATE_IND,
   MSG_ID_BT_BPP_PROGRESS_IND,
   MSG_ID_BT_BPP_PROGRESS_RSP,
   MSG_ID_BT_BPP_AUTH_IND,
   MSG_ID_BT_BPP_AUTH_RSP,
   MSG_ID_BT_BPP_DESTORY_REQ,
   MSG_ID_BT_BPP_CHECK_STATUS,
   MSG_ID_BT_BPP_COMPOSE_CONTINUE,

   /* BIP */
   MSG_ID_BT_BIP_CONNECT_REQ,
   MSG_ID_BT_BIP_CONNECT_CNF,
   MSG_ID_BT_BIP_DISCONNECT_REQ,
   MSG_ID_BT_BIP_GET_CAPABILITIES_REQ,
   MSG_ID_BT_BIP_GET_CAPABILITIES_CNF,
   MSG_ID_BT_BIP_PUT_IMG_REQ,
   MSG_ID_BT_BIP_PUT_IMG_CNF,
   MSG_ID_BT_BIP_PUT_LINKED_THUMBNAIL_REQ,
   MSG_ID_BT_BIP_PUT_LINKED_THUMBNAIL_CNF,
   MSG_ID_BT_BIP_GET_IMG_LIST_REQ,
   MSG_ID_BT_BIP_GET_IMG_LIST_PARSING_IND,
   MSG_ID_BT_BIP_GET_IMG_LIST_CNF,
   MSG_ID_BT_BIP_GET_IMG_PROP_REQ,
   MSG_ID_BT_BIP_GET_IMG_PROP_CNF,
   MSG_ID_BT_BIP_GET_IMG_REQ,
   MSG_ID_BT_BIP_GET_IMG_CNF,
   MSG_ID_BT_BIP_GET_LINKED_THUMBNAIL_REQ,
   MSG_ID_BT_BIP_GET_LINKED_THUMBNAIL_CNF,
   MSG_ID_BT_BIP_GET_MONITORING_IMG_REQ,
   MSG_ID_BT_BIP_GET_MONITORING_IMG_CNF,
   MSG_ID_BT_BIP_ABORT_REQ,
   MSG_ID_BT_BIP_ABORT_CNF,
   MSG_ID_BT_BIP_ACTIVATE_REQ,
   MSG_ID_BT_BIP_ACTIVATE_CNF,
   MSG_ID_BT_BIP_DEACTIVATE_REQ,
   MSG_ID_BT_BIP_DEACTIVATE_CNF,
   MSG_ID_BT_BIP_ENTER_USB_MODE_REQ,
   MSG_ID_BT_BIP_ENTER_USB_MODE_CNF,
   MSG_ID_BT_BIP_AUTHORIZE_IND,
   MSG_ID_BT_BIP_AUTHORIZE_RSP,
   MSG_ID_BT_BIP_CONNECT_IND,
   MSG_ID_BT_BIP_CONNECT_RSP,
   MSG_ID_BT_BIP_GET_CAPABILITIES_IND,
   MSG_ID_BT_BIP_GET_CAPABILITIES_RSP,
   MSG_ID_BT_BIP_PUT_IMG_IND,
   MSG_ID_BT_BIP_PUT_IMG_RSP,
   MSG_ID_BT_BIP_PUT_LINKED_THUMBNAIL_IND,
   MSG_ID_BT_BIP_PUT_LINKED_THUMBNAIL_RSP,
   MSG_ID_BT_BIP_GET_IMG_LIST_IND,
   MSG_ID_BT_BIP_GET_IMG_LIST_RSP,
   MSG_ID_BT_BIP_GET_IMG_PROP_IND,
   MSG_ID_BT_BIP_GET_IMG_PROP_RSP,
   MSG_ID_BT_BIP_GET_IMG_IND,
   MSG_ID_BT_BIP_GET_IMG_RSP,
   MSG_ID_BT_BIP_GET_LINKED_THUMBNAIL_IND,
   MSG_ID_BT_BIP_GET_LINKED_THUMBNAIL_RSP,
   MSG_ID_BT_BIP_GET_MONITORING_IMG_IND,
   MSG_ID_BT_BIP_GET_MONITORING_IMG_RSP,
   MSG_ID_BT_BIP_CONTINUE_IND,
   MSG_ID_BT_BIP_CONTINUE_RSP,
   MSG_ID_BT_BIP_ABORT_IND,
   MSG_ID_BT_BIP_COMPLETE_IND,
   MSG_ID_BT_BIP_RESUME_XMLPARSE_IND,
   MSG_ID_BT_BIP_DISCONNECT_IND,

   /* csj */
   MSG_ID_BT_PBAP_FIRST_MSG_ID,
   MSG_ID_BT_PBAP_REGISTER_REQ,//ACTIVE
   MSG_ID_BT_PBAP_REGISTER_RSP,

   MSG_ID_BT_PBAP_DEREGISTER_REQ,//deactive
   MSG_ID_BT_PBAP_DEREGISTER_RSP,

   MSG_ID_BT_PBAP_DISCONNECT_REQ,
   MSG_ID_BT_PBAP_DISCONNECT_RSP,

   MSG_ID_BT_PBAP_AUTHORIZE_IND,
   MSG_ID_BT_PBAP_AUTHORIZE_RSP,

   MSG_ID_BT_PBAP_CLIENT_CONNECT_IND,
   MSG_ID_BT_PBAP_CLIENT_CONNECT_RSP,

   MSG_ID_BT_PBAP_CLIENT_AUTH_CHALLENGE_IND,
   MSG_ID_BT_PBAP_CLIENT_AUTH_CHALLENGE_CNF,

//   MSG_ID_BT_PBAP_CONTINUE_RSP,
   
   MSG_ID_BT_PBAP_CLIENT_DISCONNECT_IND,
   MSG_ID_BT_PBAP_CLIENT_DISCONNECT_RSP,

   MSG_ID_BT_PBAP_ABORT_REQ,
//   MSG_ID_BT_PBAP_ABORT_RSP,

   MSG_ID_BT_PBAP_ENTER_USB_MODE_REQ,
   MSG_ID_BT_PBAP_ENTER_USB_MODE_RSP,


   MSG_ID_BT_PBAP_SET_PATH_IND,
   MSG_ID_BT_PBAP_SET_PATH_RSP,

   MSG_ID_BT_PBAP_SETPATH_IND,
   MSG_ID_BT_PBAP_SETPATH_RSP,

   MSG_ID_BT_PBAP_READ_ENTRY_IND,
   MSG_ID_BT_PBAP_READ_ENTRY_RSP,

   MSG_ID_BT_PBAP_READ_FOLDER_IND,
   MSG_ID_BT_PBAP_READ_FOLDER_RSP,

   MSG_ID_BT_PBAP_READ_LIST_IND,
   MSG_ID_BT_PBAP_READ_LIST_RSP,

   /* for pbap client begin */
   MSG_ID_BT_PBAPC_ENABLE_REQ,
   MSG_ID_BT_PBAPC_ENABLE_CNF,
   
   MSG_ID_BT_PBAPC_DISABLE_REQ,
   MSG_ID_BT_PBAPC_DISABLE_CNF,
   
   MSG_ID_BT_PBAPC_CONNECT_REQ,
   MSG_ID_BT_PBAPC_CONNECT_CNF,
   
   MSG_ID_BT_PBAPC_DISCONNECT_REQ,
   MSG_ID_BT_PBAPC_DISCONNECT_CNF,
   MSG_ID_BT_PBAPC_DISCONNECT_IND,
   
   MSG_ID_BT_PBAPC_AUTH_CHALLENGE_IND,
   MSG_ID_BT_PBAPC_AUTH_CHALLENGE_RSP,
   
   MSG_ID_BT_PBAPC_SET_PATH_REQ,
   MSG_ID_BT_PBAPC_SET_PATH_CNF,
   
   MSG_ID_BT_PBAPC_READ_ENTRY_REQ,
   MSG_ID_BT_PBAPC_READ_ENTRY_CNF,
   
   MSG_ID_BT_PBAPC_READ_FOLDER_REQ,
   MSG_ID_BT_PBAPC_READ_FOLDER_CNF,
   
   MSG_ID_BT_PBAPC_READ_LIST_REQ,
   MSG_ID_BT_PBAPC_READ_LIST_CNF,
   
   MSG_ID_BT_PBAPC_ABORT_REQ,
   MSG_ID_BT_PBAPC_ABORT_CNF,
   MSG_ID_BT_PBAPC_ABORT_IND,   
   /* for pbap client end */

   MSG_ID_BT_PBAP_LAST_MSG_ID,

   /* for MAP */
   MSG_ID_BT_MAP_FIRST_MSG_ID,
   
   MSG_ID_BT_MAPC_ACTIVATE_REQ = MSG_ID_BT_MAP_FIRST_MSG_ID,
   MSG_ID_BT_MAPC_ACTIVATE_CNF,
   
   MSG_ID_BT_MAPC_DEACTIVATE_REQ,
   MSG_ID_BT_MAPC_DEACTIVATE_CNF,
   
   MSG_ID_BT_MAPC_CONNECT_REQ,
   MSG_ID_BT_MAPC_CONNECT_CNF,
   
   MSG_ID_BT_MAPC_DISCONNECT_REQ,
   MSG_ID_BT_MAPC_DISCONNECT_CNF,
   MSG_ID_BT_MAPC_DISCONNECT_IND,
   
   MSG_ID_BT_MAPC_SET_FOLDER_REQ,
   MSG_ID_BT_MAPC_SET_FOLDER_CNF,
   
   MSG_ID_BT_MAPC_GET_FOLDER_LISTING_SIZE_REQ,
   MSG_ID_BT_MAPC_GET_FOLDER_LISTING_SIZE_CNF,
   
   MSG_ID_BT_MAPC_GET_FOLDER_LISTING_REQ,
   MSG_ID_BT_MAPC_GET_FOLDER_LISTING_CNF,
   
   MSG_ID_BT_MAPC_GET_MESSAGE_LISTING_SIZE_REQ,
   MSG_ID_BT_MAPC_GET_MESSAGE_LISTING_SIZE_CNF,
   
   MSG_ID_BT_MAPC_GET_MESSAGE_LISTING_REQ,
   MSG_ID_BT_MAPC_GET_MESSAGE_LISTING_CNF,
   
   MSG_ID_BT_MAPC_GET_MESSAGE_REQ,
   MSG_ID_BT_MAPC_GET_MESSAGE_CNF,
   
   MSG_ID_BT_MAPC_SET_NOTIFY_REGISTRATION_REQ,
   MSG_ID_BT_MAPC_SET_NOTIFY_REGISTRATION_CNF,
   
   MSG_ID_BT_MAPC_SET_MESSAGE_STATUS_REQ,
   MSG_ID_BT_MAPC_SET_MESSAGE_STATUS_CNF,
   
   MSG_ID_BT_MAPC_PUSH_MESSAGE_REQ,
   MSG_ID_BT_MAPC_PUSH_MESSAGE_CNF,
   
   MSG_ID_BT_MAPC_UPDATE_INBOX_REQ,
   MSG_ID_BT_MAPC_UPDATE_INBOX_CNF,
   
   MSG_ID_BT_MAPC_ABORT_REQ,
   MSG_ID_BT_MAPC_ABORT_CNF,
   
   MSG_ID_BT_MAPC_MNS_AUTHORIZE_IND,
   MSG_ID_BT_MAPC_MNS_AUTHORIZE_RSP,
   
   MSG_ID_BT_MAPC_MNS_DISCONNECT_REQ,
   MSG_ID_BT_MAPC_MNS_DISCONNECT_CNF,
   
   MSG_ID_BT_MAPC_MNS_SEND_EVENT_IND,
   MSG_ID_BT_MAPC_MNS_SEND_EVENT_RSP,
   
   MSG_ID_BT_MAP_LAST_MSG_ID = MSG_ID_BT_MAPC_MNS_SEND_EVENT_RSP,

   MSG_TAG_BT_SAP_END_MSG,
   MSG_ID_BT_SET_SCO_ACCEPT_REQ,
   MSG_ID_BT_SET_SCO_ACCEPT_CNF,
   MSG_ID_BT_SET_DUAL_PCM_SETTING_REQ,
   MSG_ID_BT_SET_DUAL_PCM_SETTING_CNF,
   MSG_ID_BT_SET_DUAL_PCM_SWITCH_REQ,
   MSG_ID_BT_SET_DUAL_PCM_SWITCH_CNF,
   MSG_ID_BT_WAKEUP_BT_CONTROLLER,

   // radiomod.c -> btstack, radiomod.c -> fmr 
   MSG_ID_BT_FORCE_RESET_START,
   MSG_ID_BT_FORCE_RESET_END,

   /*NON_SIGNALING_RX_TEST LCH, 20110808*/ 
   MSG_ID_BT_ENGINEER_MODE_NSR_TEST_ENTER_REQ,
   MSG_ID_BT_ENGINEER_MODE_NSR_TEST_ENTER_CNF,   
   MSG_ID_BT_ENGINEER_MODE_NSR_TEST_EXIT_REQ,   
   MSG_ID_BT_ATA_POWER_ON_REQ,
   MSG_ID_BT_ATA_POWER_ON_CNF,   
   MSG_ID_BT_ATA_POWER_OFF_REQ,
   MSG_ID_BT_ATA_POWER_OFF_CNF,   
   MSG_ID_BT_ENGINEER_MODE_NSR_TEST_EXIT_CNF,
   MSG_ID_BT_ENGINEER_MODE_TXRX_TEST_EXIT_REQ,
   MSG_ID_BT_ENGINEER_MODE_TXRX_TEST_EXIT_CNF,

