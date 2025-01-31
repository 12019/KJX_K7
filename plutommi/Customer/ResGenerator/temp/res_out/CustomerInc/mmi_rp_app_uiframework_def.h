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
 *   mmi_rp_app_uiframework_def.h
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


#ifndef _MMI_RP_APP_UIFRAMEWORK_DEF_H
#define _MMI_RP_APP_UIFRAMEWORK_DEF_H




/******************** String resource IDs - begin ********************/
typedef enum
{
    WGUI_UCE_SMS_STRING_ID = 10737 + 1, /* BASE_ID + 1 */
    WGUI_UCE_MMS_STRING_ID,
    WGUI_CATEGORY_ABC_STRING_ID,
    WGUI_CATEGORY_abc_STRING_ID,
    WGUI_CATEGORY_Abc_STRING_ID,
    WGUI_CATEGORY_123_STRING_ID,
    STR_DOW_SUNDAY,
    STR_DOW_MONDAY,
    STR_DOW_TUESDAY,
    STR_DOW_WEDNESDAY,
    STR_DOW_THURSDAY,
    STR_DOW_FRIDAY,
    STR_DOW_SATURDAY,
    WGUI_CATEGORY_ON_STRING_ID,
    STR_ID_MTE_PIN,
    MMI_RP_APP_UIFRAMEWORK_STR_MAX
}mmi_rp_app_uiframework_str_enum;
/******************** String resource IDs - finish ********************/


/******************** Timer resource IDs - begin ********************/
typedef enum
{
    BLINKING_CURSOR = 10737 + 1, /* BASE_ID + 1 */
    FMGR_DELAY_DECODE_0,
    CAT9010_TIMER,
    MMI_RP_APP_UIFRAMEWORK_TIMER_MAX
}mmi_rp_app_uiframework_timer_enum;
/******************** Timer resource IDs - finish ********************/


/******************** Events resource IDs - begin ********************/
typedef enum
{
    EVT_ID_GUI_INPUTS_CURSOR_CHANGED = 10737 + 1, /* BASE_ID + 1 */
    EVT_ID_IME_CURSOR_UPDATED,
    EVT_ID_IME_INVOKE_SPELL_WORD_SCREEN,
    EVT_ID_IME_ENTRY_INPUT_METHOD_SCREEN,
    EVT_ID_INLINE_IMAGETEXT_PEN_UP,
    MMI_RP_APP_UIFRAMEWORK_EVENT_MAX
}mmi_rp_app_uiframework_event_enum;
/******************** Events resource IDs - begin ********************/


/******************** Audio resource IDs - begin ********************/
typedef enum
{
    AUD_ID_EMS_CHIMES_HIGH = 10737 + 1, /* BASE_ID + 1 */
    AUD_ID_EMS_CHIMES_LOW,
    AUD_ID_EMS_DING,
    AUD_ID_EMS_TADA,
    AUD_ID_EMS_NOTIFY,
    AUD_ID_EMS_DRUM,
    AUD_ID_EMS_CLAPS,
    AUD_ID_EMS_FANFAR,
    AUD_ID_EMS_CHORE_HGH,
    AUD_ID_EMS_CHORE_LOW,
    MMI_RP_APP_UIFRAMEWORK_AUD_MAX
}mmi_rp_app_uiframework_aud_enum;
/******************** Audio resource IDs - finish ********************/
/******************** Template resource IDs - Begin ********************/
/******************** Template resource IDs - End ********************/

/******************** Venus XML resource IDs - Begin ********************/
typedef enum 
{

    MMI_RP_APP_UIFRAMEWORK_VXML_LAYOUT_MAX
} mmi_rp_app_uiframework_vxml_layout_enum;
/******************** Venus XML resource IDs - End ********************/



/******************** Image resource IDs - begin ********************/
typedef enum
{
    WGUI_UCE_ATTACHFILE_ICON_IMAGE_ID = 10737 + 1, /* BASE_ID + 1 */
    WGUI_UCE_AUDIO_ICON_IMAGE_ID,
    WGUI_UCE_PICTURE_ICON_IMAGE_ID,
    WGUI_UCE_VIDEO_ICON_IMAGE_ID,
    WGUI_UCE_PRE_BUTTON_ID,
    WGUI_UCE_PRE_BUTTON_DISABLE_ID,
    WGUI_UCE_NEXT_BUTTON_ID,
    WGUI_UCE_NEXT_BUTTON_DISABLE_ID,
    WGUI_UCE_FTE_ATTACHE_BUTTON_NORMAL,
    WGUI_UCE_FTE_ATTACHE_BUTTON_PRESSED,
    WGUI_DEFAULT_PREVIEW_IMAGE_ID,
    WGUI_DEFAULT_PREVIEW_AVIDEO_ID,
    WGUI_MV_ATTACHFILE_ICON_IMAGE_ID,
    WGUI_MV_REFERENCE_ICON_IMAGE_ID,
    WGUI_MV_RING_ICON_IMAGE_ID,
    WGUI_MV_BAR_ICON_IMAGE_ID,
    WGUI_MV_RING_STOP_ICON_IMAGE_ID,
    WGUI_MV_LEFT_ARROW_ICON_IMAGE_ID,
    WGUI_MV_LEFT_ARROW_DOWN_ICON_IMAGE_ID,
    WGUI_MV_RIGHT_ARROW_ICON_IMAGE_ID,
    WGUI_MV_RIGHT_ARROW_DOWN_ICON_IMAGE_ID,
    WGUI_MV_DRM_IMAGE_LOCK_ID,
    WGUI_MV_DRM_VIDEO_LOCK_ID,
    WGUI_VOLUME_LEVEL0,
    WGUI_VOLUME_LEVEL1,
    WGUI_VOLUME_LEVEL2,
    WGUI_VOLUME_LEVEL3,
    WGUI_VOLUME_LEVEL4,
    WGUI_VOLUME_LEVEL5,
    WGUI_VOLUME_LEVEL6,
    WGUI_VOLUME_LEVEL7,
    WGUI_VOLUME_UP_UP_IMAGE_ID,
    WGUI_VOLUME_UP_DOWN_IMAGE_ID,
    WGUI_VOLUME_UP_DISABLE_IMAGE_ID,
    WGUI_VOLUME_DOWN_UP_IMAGE_ID,
    WGUI_VOLUME_DOWN_DOWN_IMAGE_ID,
    WGUI_VOLUME_DOWN_DISABLE_IMAGE_ID,
    WGUI_SLIDE_CONTROL_BG_IMAGE_ID,
    WGUI_SLIDE_CONTROL_SI_IMAGE_ID,
    IMG_SELECTOR_FILLER,
    WGUI_INPUT_INFORMATION_ICON1,
    IMG_IME_QWERTY_FN,
    IMG_IME_QWERTY_FN_LOCK,
    IMG_IME_QWERTY_SHIFT,
    IMG_IME_QWERTY_SHIFT_LOCK,
    IMG_INLINE_BUTTON_HIGHLIGHT_UP_BG,
    IMG_INLINE_BUTTON_NORMAL_UP_BG,
    IMG_INLINE_BUTTON_HIGHLIGHT_DOWN_BG,
    IMG_INLINE_BUTTON_NORMAL_DOWN_BG,
    IMG_H_SELECT_LEFT,
    IMG_H_SELECT_RIGHT,
    RIGHT_RED_ARROW,
    LEFT_RED_ARROW,
    RIGHT_RED_ARROW_NORMAL,
    LEFT_RED_ARROW_NORMAL,
    RIGHT_RED_ARROW_PRESSED,
    LEFT_RED_ARROW_PRESSED,
    RIGHT_RED_ARROW_DISABLED,
    LEFT_RED_ARROW_DISABLED,
    LEFT_ARROW_DOWN,
    LEFT_ARROW_UP,
    RIGHT_ARROW_DOWN,
    RIGHT_ARROW_UP,
    IMG_LEFT_DISABLED_ARROW,
    IMG_RIGHT_DISABLED_ARROW,
    IMG_DIALING_SCREEN_BG_UP,
    IMG_DIALING_SCREEN_BG_DOWN,
    IMG_DIALING_SCREEN_BG_LEFT,
    IMG_DIALING_SCREEN_BG_RIGHT,
    IMG_CSK_DIAL_ICON,
    CAL_LEFT_ARROW_UP_IMAGE,
    CAL_LEFT_ARROW_DOWN_IMAGE,
    CAL_RIGHT_ARROW_UP_IMAGE,
    CAL_RIGHT_ARROW_DOWN_IMAGE,
    CAL_LEFT_ARROW_DISABLE_IMAGE,
    CAL_RIGHT_ARROW_DISABLE_IMAGE,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_0,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_1,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_2,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_3,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_4,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_5,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_6,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_7,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_8,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_9,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_AM,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_PM,
    IMG_TECHNO_DIGITAL_SMALL_CLOCK_COLON,
    IMAGE_VIEW_TITLEBAR_BG,
    IMG_FLEXIBLE_TITLEBAR_BG,
    IMG_HORIZONTAL_NORMAL_TAB,
    IMG_HORIZONTAL_NORMAL_LEFT_TAB,
    IMG_HORIZONTAL_NORMAL_RIGHT_TAB,
    IMG_HORIZONTAL_FOCUSED_TAB,
    IMG_HORIZONTAL_FOCUSED_LEFT_TAB,
    IMG_HORIZONTAL_FOCUSED_RIGHT_TAB,
    IMG_HORIZONTAL_BLINKING_TAB,
    IMG_HORIZONTAL_BLINKING_LEFT_TAB,
    IMG_HORIZONTAL_BLINKING_RIGHT_TAB,
    IMG_HORIZONTAL_TAB_L_ARROW,
    IMG_HORIZONTAL_TAB_R_ARROW,
    IMG_HORIZONTAL_TAB_HINT_AREA,
    IMG_HORIZONTAL_DISABLED_TAB,
    IMG_PERCENTAGE_BAR_LEFT_IMAGE,
    IMG_PERCENTAGE_BAR_RIGHT_IMAGE,
    IMG_PERCENTAGE_BAR_BG_IMAGE,
    GUI_COLOR_SLIDER_ARROW_IMAGE_ID,
    WGUI_IMG_TEXT_BG_TOP,
    WGUI_IMG_TEXT_BG_MID,
    WGUI_IMG_TEXT_BG_BOTTOM,
    WGUI_IMG_TEXT_BG_PREVIEW,
    IMG_CAT412_PROG_BAR_BG,
    IMG_CAT412_PROG_BAR_FULL,
    IMG_STATUS_ICON_TIME_AM,
    IMG_STATUS_ICON_TIME_PM,
    IMG_STATUS_ICON_TIME_AM_CH,
    IMG_STATUS_ICON_TIME_PM_CH,
    IMG_BOOTUP_SCANNING_LOGO,
    RADIO_ON_IMAGE_ID,
    RADIO_OFF_IMAGE_ID,
    CHECKBOX_ON_IMAGE_ID,
    CHECKBOX_OFF_IMAGE_ID,
    MMI_RP_APP_UIFRAMEWORK_IMG_MAX
}mmi_rp_app_uiframework_img_enum;
/******************** Image resource IDs - finish ********************/


#endif /* _MMI_RP_APP_UIFRAMEWORK_DEF_H */
