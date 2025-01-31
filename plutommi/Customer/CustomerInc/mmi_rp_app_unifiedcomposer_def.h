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
 * Filename:
 * ---------
 *   mmi_rp_app_unifiedcomposer_def.h
 *
 * Project:
 * --------
 *   MAUI
 *
 * Description:
 * ------------
 *   Resource populate function generated by XML resgen
 *
 * Author:
 * -------
 *   MTK resgenerator XML parser
 *
 *******************************************************************************/


#ifndef _MMI_RP_APP_UNIFIEDCOMPOSER_DEF_H
#define _MMI_RP_APP_UNIFIEDCOMPOSER_DEF_H




/******************** Menu resource IDs - begin ********************/
typedef enum
{
    MENU_ID_UC_OPT = 38111 + 1, /* BASE_ID + 1 */
    MENU_ID_UC_OPT_SEND,
    MENU_ID_UC_OPT_ADD_RECIPIENT,
    MENU_ID_UC_OPT_HEADER_OPTIONS,
    MENU_ID_UC_OPT_HEADER_OPT_CC,
    MENU_ID_UC_OPT_HEADER_OPT_BCC,
    MENU_ID_UC_OPT_HEADER_OPT_SUBJECT,
    MENU_ID_UC_OPT_PICTURE_OPTIONS,
    MENU_ID_UC_OPT_PICTURE_OPT_IMAGE_REMOVE,
    MENU_ID_UC_OPT_SOUND_OPTIONS,
    MENU_ID_UC_OPT_AUDIO_OPT_AUDIO_REMOVE,
    MENU_ID_UC_OPT_VIDEO_OPTIONS,
    MENU_ID_UC_OPT_VIDEO_OPT_VIDEO_REMOVE,
    MENU_ID_UC_OPT_ATTACHMENT_OPTIONS,
    MENU_ID_UC_OPT_ATTACH_OPT_ATTACHMENT_REMOVE,
    MENU_ID_UC_OPT_ADD_PICTURE,
    MENU_ID_UC_OPT_INSERT_IMAGE,
    MENU_ID_UC_OPT_ADD_SOUND,
    MENU_ID_UC_OPT_INSERT_AUDIO,
    MENU_ID_UC_OPT_ADD_VIDEO,
    MENU_ID_UC_OPT_INSERT_VIDEO,
    MENU_ID_UC_OPT_PREVIEW,
    MENU_ID_UC_OPT_SLIDE_OPT,
    MENU_ID_UC_OPT_SLIDE_OPT_INSERT,
    MENU_ID_UC_OPT_SLIDE_OPT_INSERT_BEFORE,
    MENU_ID_UC_OPT_SLIDE_OPT_TIMING,
    MENU_ID_UC_OPT_SLIDE_OPT_DELETE,
    MENU_ID_UC_OPT_SLIDE_OPT_NEXT,
    MENU_ID_UC_OPT_SLIDE_OPT_PREVIOUS,
    MENU_ID_UC_OPT_ADVANCED,
    MENU_ID_UC_OPT_INSERT_TEXT_TEMPLATE,
    MENU_ID_UC_OPT_INSERT_ATTACHMENT,
    MENU_ID_UC_OPT_SAVE_TO_DRAFT,
    MENU_ID_UC_OPT_SEND_OPT,
    MENU_ID_UC_EDITOR_OPTION,
    MENU_ID_UC_EDITOR_OPTION_DONE,
    MENU_ID_UC_EDITOR_OPTION_CANCEL,
    MENU_ID_UC_OPT_REMOVE,
    MENU_ID_UC_OPT_REMOVE_IMAGE,
    MENU_ID_UC_OPT_REMOVE_AUDIO,
    MENU_ID_UC_OPT_REMOVE_VIDEO,
    MENU_ID_UC_OPT_REMOVE_ATTACHMENT,
    MENU_ID_UC_OPT_DONE_SEND,
    MENU_ID_UC_EXIT_OPT,
    MENU_ID_UC_EXIT_OPT_SAVE,
    MENU_ID_UC_EXIT_OPT_EXIT,
    MENU_ID_UC_OPT_MSG_TYPE_OPT,
    MMI_RP_APP_UNIFIEDCOMPOSER_MENU_MAX
}mmi_rp_app_unifiedcomposer_menu_enum;
/******************** Menu resource IDs - finish ********************/


/******************** String resource IDs - begin ********************/
typedef enum
{
    STR_UC_SLIDE_OPTION_ID = 38111 + 1, /* BASE_ID + 1 */
    STR_UC_SEND_OPTION_ID,
    STR_UC_MESSAGE_TYPE_ID,
    STR_UC_RESEND_ID,
    STR_UC_ATTACHMENT_LIST_ID,
    STR_UC_DELETE_SLIDE_ID,
    STR_UC_SLIDE_TIMING_ID,
    STR_UC_CC_ID,
    STR_UC_BCC_ID,
    STR_UC_MSG_SIZE_EXCEED_ID,
    STR_UC_RESTRICTED_MODE_MSG_SIZE_EXCEED_ID,
    STR_UC_SIZE_NOT_ENOUGH_FOR_REC_VIDEO_ID,
    STR_UC_ADDR_LENGTH_EXCEED_ID,
    STR_UC_NUMBER_LENGTH_EXCEED_ID,
    STR_UC_PROHIBIT_BY_CREATION_MODE_ID,
    STR_UC_NO_SPACE_ID,
    STR_UC_READ_REPORT_ID,
    STR_UC_DELIVERY_REPORT_ID,
    STR_UC_VALIDITY_PERIOD_ID,
    STR_UC_DELIVERY_TIME_ID,
    STR_UC_VALIDITY_PERIOD_1_HOUR_ID,
    STR_UC_VALIDITY_PERIOD_6_HOUR_ID,
    STR_UC_VALIDITY_PERIOD_12_HOUR_ID,
    STR_UC_VALIDITY_PERIOD_1_DAY_ID,
    STR_UC_VALIDITY_PERIOD_1_WEEK_ID,
    STR_UC_DELIVERY_TIME_IMMEDIATE_ID,
    STR_UC_DELIVERY_TIME_1_HOUR_ID,
    STR_UC_DELIVERY_TIME_12_HOUR_ID,
    STR_UC_DELIVERY_TIME_24_HOUR_ID,
    STR_UC_FAIL_TO_INSERT_SIGNATURE_ID,
    STR_UC_DISCARD_EDITED_MSG_ID,
    STR_UC_WRITE_MSG_ID,
    STR_UC_STORAGE_FILE_IO_ERROR_ID,
    STR_UC_STORAGE_FULL_MSG_CONTENT_LOSS_ID,
    STR_UC_NO_RECIPIENT_ID,
    STR_ID_UC_INVALID_RECIPIENT,
    STR_ID_UC_INVALID_RECIPIENTS_REMOVED,
    STR_UC_PLS_ADD_RECIPIENT_ID,
    STR_UC_CREATING_ID,
    STR_UC_ABORTED_ID,
    STR_UC_SEND_SUCCESS_SAVE_SUCCESS,
    STR_UC_SEND_SUCCESS_SAVE_FAIL,
    STR_UC_CONTENT_ERROR_ID,
    STR_UC_RECIPIENT_NUMBER_EXCEED_ID,
    STR_UC_CAN_NOT_PLAY_COMPLETE,
    STR_UC_UNSUPPORT_CONTENT_ID,
    STR_UC_NO_ENOUGH_WORKING_SPACE_ID,
    STR_UC_CREATION_MODE_MAX_MSG_SIZE_REACHED_ID,
    STR_UC_MAX_SLIDE_NUM_REACHED_ID,
    STR_UC_TOO_MANY_MSG_ID,
    STR_UC_CONFIG_ERROR_ID,
    STR_UC_SERVER_TIMEOUT_ID,
    STR_UC_SERVER_ERROR_ID,
    STR_UC_SERVICE_DENIED_ID,
    STR_UC_UNSUPPORT_CONTENT_BY_SERVER_ID,
    STR_UC_UNKNOWN_APN_ID,
    STR_UC_UNAUTHORIZED_ID,
    STR_UC_SEND_FAIL_ID,
    STR_UC_SEND_FAIL_NO_BOX_ID,
    STR_UC_SEND_FAIL_NO_BOX_ID_LOWER,
    STR_UC_SYSTEM_RESOURCES_EXHAUSTED_ID,
    STR_UC_FILE_CORRUPT_ID,
    STR_UC_FAILED_TO_ADD_MEDIA_ID,
    STR_UC_FILE_EMPTY_ID,
    STR_UC_RE_ID,
    STR_UC_FW_ID,
    STR_UC_SIGNATURE_OBJECT_MISSED_ID,
    STR_UC_FAIL_TO_RESIZE_IMAGE_ID,
    STR_UC_START_TIME_ID,
    STR_UC_END_TIME_ID,
    STR_UC_EXCEED_SLIDE_TIME_ID,
    STR_UC_LESS_THAN_MEDIA_TIME_ID,
    STR_UC_INTERVAL_PREFIX_ID,
    STR_UC_INTERVAL_INFIX_ID,
    STR_UC_SERVER_ID,
    STR_UC_KB_ID,
    STR_UC_RESIZE_IMAGE_UNCHANGED_ID,
    STR_UC_WARNING_MODE_CONFIRM,
    STR_UC_WARNING_MODE_SIG_CONFIRM,
    STR_UC_INSERT_CARD,
    STR_UC_CARD_NOT_PRESENT_CONFIRM,
    STR_UC_MAX_MSG_CARD_CONFIRM,
    STR_UC_MAX_MSG_PHONE_CONFIRM,
    STR_UC_DELETE_ASK_ID,
    STR_UC_DELETE_ALL_ASK_ID,
    STR_UC_CONN_TYPE_MAX_SIZE_REACHED_ID,
    STR_UC_SEND_FRM_SIM1,
    STR_UC_SEND_FRM_SIM2,
    STR_UC_SEND_FRM_SIM3,
    STR_UC_SEND_FRM_SIM4,
    STR_UC_SEND_TO_ID,
    STR_UC_ADD_RECIPIENT,
    STR_UC_ADD_SUBJECT_ID,
    STR_UC_EDIT_SUBJECT_ID,
    STR_UC_ENTER_RECIPIENT_ID,
    STR_UC_ADD_FROM_CONTACTS_ID,
    STR_UC_EDIT_RECIPIENT_ID,
    STR_UC_REMOVE_RECIPIENT_ID,
    STR_UC_REMOVE_ALL_RECIPIENTS_ID,
    STR_UC_CHANGE_TO_TO_ID,
    STR_UC_CHANGE_TO_CC_ID,
    STR_UC_CHANGE_TO_BCC_ID,
    STR_UC_SAVE_TO_DRAFT_ID,
    STR_UC_ADD_RECIPIENT_ID,
    STR_UC_WRITE_MSG_SUBJECT_ID,
    STR_UC_PICTURE_OPTIONS_ID,
    STR_UC_REMOVE_PICTURE_ID,
    STR_UC_SOUND_OPTIONS_ID,
    STR_UC_REMOVE_AUDIO_ID,
    STR_UC_VIDEO_OPTIONS_ID,
    STR_UC_REMOVE_VIDEO_ID,
    STR_UC_ATTACHMENT_OPTIONS_ID,
    STR_UC_REMOVE_ATTACHMENT_ID,
    STR_UC_ADD_MY_PICTURES_ID,
    STR_UC_ADD_MY_SOUNDS_ID,
    STR_UC_ADD_MY_VIDEOS_ID,
    STR_UC_ADD_PICTURE_ID,
    STR_UC_ADD_SOUND_ID,
    STR_UC_ADD_VIDEO_ID,
    STR_UC_ADVANCED_ID,
    STR_UC_PREVIEW_MMS_ID,
    STR_UC_ADD_NEW_SLIDE_AFTER_ID,
    STR_UC_ADD_NEW_SLIDE_BEFORE_ID,
    STR_UC_GO_TO_PREVIOUS_SLIDE_ID,
    STR_UC_GO_TO_NEXT_SLIDE_ID,
    STR_UC_SLIDE_TIMING_NEW_ID,
    STR_UC_INSERT_TEXT_TEMPLATE_ID,
    STR_UC_INSERT_ATTACHMENT_ID,
    STR_UC_TRUNCATE_NUMBER_ID,
    STR_UC_IMAGE_TOO_LARGE,
    STR_UC_SOME_OBJECT_WITHDREW,
    STR_UC_REMOVED_ID,
    STR_UC_HEADER_OPTIONS_ID,
    STR_UC_WRITE_SMS_ID,
    STR_UC_WRITE_MMS_ID,
    STR_UC_MAX_RECIPIENT_FIELDS_ID,
    STR_UC_SEND_CONT_ID,
    STR_UC_SAVE_CONT_ID,
    STR_ID_POSTCARD_ADD_RECIPIENT,
    MMI_RP_APP_UNIFIEDCOMPOSER_STR_MAX
}mmi_rp_app_unifiedcomposer_str_enum;
/******************** String resource IDs - finish ********************/


/******************** Screen resource IDs - begin ********************/
typedef enum
{
    SCR_ID_UC_START = 38111 + 1, /* BASE_ID + 1 */
    SCR_ID_UC_DUMMY,
    SCR_ID_UC_PROCESSING,
    SCR_ID_UC_EDITOR,
    SCR_ID_UC_OPT,
    SCR_ID_UC_MSG_DETAIL,
    SCR_ID_UC_MSG_PREVIEW,
    SCR_ID_UC_OPT_INSERT,
    SCR_ID_ADD_PICTURE_OPTIONS,
    SCR_ID_ADD_SOUND_OPTIONS,
    SCR_ID_ADD_VIDEO_OPTIONS,
    SCR_ID_ADVANCED_OPTIONS,
    SCR_ID_UC_OPT_REMOVE,
    SCR_ID_UC_OPT_REPLACE,
    SCR_ID_PICTURE_OPTIONS,
    SCR_ID_SOUND_OPTIONS,
    SCR_ID_VIDEO_OPTIONS,
    SCR_ID_ATTACHMENT_OPTIONS,
    SCR_ID_TEXT_OPTIONS,
    SCR_ID_UC_OPT_ADD_RECIPIENT,
    SCR_ID_UC_OPT_ADD_RECIPIENT_OPTIONS,
    SCR_ID_UC_OPT_ENTER_RECIPIENT,
    SCR_ID_UC_OPT_EDIT_RECIPIENT,
    SCR_ID_UC_OPT_ATTACHMENT_LIST,
    SCR_ID_UC_OPT_ATTACHMENT_REMOVE,
    SCR_ID_UC_OPT_ATTACHMENT_REPLACE,
    SCR_ID_UC_OPT_SLIDE_OPT,
    SCR_ID_UC_OPT_SLIDE_OPT_SLIDE_TIMING,
    SCR_ID_UC_OPT_SLIDE_OPT_GOTO,
    SCR_ID_UC_OPT_MSG_TYPE_OPT,
    SCR_ID_UC_OPT_SEND_OPT,
    SCR_ID_UC_PREFERRED_MSG_TYPE,
    SCR_ID_UC_SENDING,
    SCR_ID_UC_EXIT_OPT,
    SCR_ID_UC_PREVIEW_SLIDE_LIST,
    SCR_ID_UC_OPT_INSERT_NEW_MM_OBJECT,
    SCR_ID_UC_SUBJECT_EDITOR,
    SCR_ID_UC_CONFIRM,
    SCR_ID_UC_SIG_CONFIRM,
    SCR_ID_UC_WRITE_MSG_SELECTION,
    SCR_ID_UC_SIM_OPT,
    SCR_ID_UC_INPUT_METHOD_AND_DONE,
    SCR_ID_POSTCARD_RECIPIENT_OPTION,
    SCR_ID_POSTCARD_ADDRESS,
    SCR_ID_POSTCARD_RECIPIENT_LIST,
    SCR_ID_UC_END,
    MMI_RP_APP_UNIFIEDCOMPOSER_SCR_MAX
}mmi_rp_app_unifiedcomposer_scr_enum;
/******************** Screen resource IDs - finish ********************/


/******************** Timer resource IDs - begin ********************/
typedef enum
{
    UC_INPROGRESS_TIMER_ID = 38111 + 1, /* BASE_ID + 1 */
    UC_MSG_TYPE_CHECK_TIMER_ID,
    UM_BATTERY_LOW_CHECK_TIMER_ID,
    UC_IMG_RESIZE_TIMER_ID,
    UC_CREATE_RSP_RETRY_TIMER_ID,
    UC_CREATE_RSP_REENTRY_RETRY_TIMER_ID,
    MMI_RP_APP_UNIFIEDCOMPOSER_TIMER_MAX
}mmi_rp_app_unifiedcomposer_timer_enum;
/******************** Timer resource IDs - finish ********************/
/******************** Template resource IDs - Begin ********************/
/******************** Template resource IDs - End ********************/

/******************** Venus XML resource IDs - Begin ********************/
typedef enum 
{

    MMI_RP_APP_UNIFIEDCOMPOSER_VXML_LAYOUT_MAX
} mmi_rp_app_unifiedcomposer_vxml_layout_enum;
/******************** Venus XML resource IDs - End ********************/



/******************** MMI Cache IDs - Begin ********************/
typedef enum
{
    NVRAM_UC_PREFERRED_MSG_TYPE = 38111 + 1, /* BASE_ID + 1 */   /*         BYTE */ 
    MMI_RP_APP_UNIFIEDCOMPOSER_MMI_CACHE_MAX
} mmi_rp_app_unifiedcomposer_mmi_cache_enum;
/******************** MMI Cache IDs - End ********************/


/******************** Image resource IDs - begin ********************/
typedef enum
{
    IMG_UC_ENTRY_SCRN_CAPTION_ID = 38111 + 1, /* BASE_ID + 1 */
    IMG_UC_TO_NUMBER_ID,
    IMG_UC_CC_NUMBER_ID,
    IMG_UC_BCC_NUMBER_ID,
    IMG_UC_TO_EMAIL_ID,
    IMG_UC_CC_EMAIL_ID,
    IMG_UC_BCC_EMAIL_ID,
    IMG_UC_DRM_THUMBNAIL_ID,
    IMG_UC_TO_BUTTON_ID,
    IMG_UC_CC_BUTTON_ID,
    IMG_UC_BCC_BUTTON_ID,
    IMG_UC_AUDIO_BUTTON_ID,
    MMI_RP_APP_UNIFIEDCOMPOSER_IMG_MAX
}mmi_rp_app_unifiedcomposer_img_enum;
/******************** Image resource IDs - finish ********************/


#endif /* _MMI_RP_APP_UNIFIEDCOMPOSER_DEF_H */
