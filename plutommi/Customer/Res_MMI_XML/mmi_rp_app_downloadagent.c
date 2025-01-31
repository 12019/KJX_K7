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
 *   mmi_rp_app_downloadagent.c
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
#include "CustDataProts.h"
#include "mmi_rp_app_downloadagent_def.h"

/* Application specified header files for using old res IDs */
#include "MMI_features.h"
#include "MMIDataType.h"    /* for resource base */

#include "CustResDef.h"         /* for image/audio path */
#include "GlobalMenuItems.h"    /* for menu resource */

#include "GlobalResDef.h"


/*****************************************************************************
* FUNCTION
*  mmi_rp_app_downloadagent_populate
* DESCRIPTION
*  Automatically generated populate function for mmi_rp_app_downloadagent_populate
* PARAMETERS
*  void
* RETURNS
*  void
*****************************************************************************/
void mmi_rp_app_downloadagent_populate(void)
{
    /*----------------------------------------------------------------*/
    /* Local Variables                                                */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /* Code Body                                                      */
    /*----------------------------------------------------------------*/

/******************** Menu resource IDs - begin ********************/
    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_OMA_DL_OPTION,
        0,
        2,
        MENU_ID_DA_OMA_DL_OPTION_DOWNLOAD_NOW,
        MENU_ID_DA_OMA_DL_OPTION_VIEW_DD,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_OPTION,
        STR_GLOBAL_OPTIONS,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_OMA_DL_OPTION_DOWNLOAD_NOW,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_DOWNLOAD,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_OMA_DL_OPTION_VIEW_DD,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_ID_DA_OMA_VIEW_DD,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION,
        0,
        10,
        MENU_ID_DA_JOB_OPTION_VIEW_DETAIL,
        MENU_ID_DA_JOB_OPTION_PLAY,
        MENU_ID_DA_JOB_OPTION_USE_NOW,
        MENU_ID_DA_JOB_OPTION_SUSPEND,
        MENU_ID_DA_JOB_OPTION_RESUME,
        MENU_ID_DA_JOB_OPTION_MOVE,
        MENU_ID_DA_JOB_OPTION_RENAME,
        MENU_ID_DA_JOB_OPTION_CANCEL,
        MENU_ID_DA_JOB_OPTION_REMOVE,
        MENU_ID_DA_JOB_OPTION_REMOVE_ALL,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_OPTION,
        STR_GLOBAL_OPTIONS,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_PLAY,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_PLAY,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_VIEW_DETAIL,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_DETAILS,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_CANCEL,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_CANCEL,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_SUSPEND,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_PAUSE,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_RESUME,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_ID_DA_JOB_RESUME,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_USE_NOW,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_ID_DA_JOB_USE,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_MOVE,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_ID_DA_JOB_MOVE,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_RENAME,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_RENAME,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_REMOVE,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_REMOVE,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_JOB_OPTION_REMOVE_ALL,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_ID_DA_JOB_REMOVE_ALL,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_DOWNLOAD_CNF_OPT,
        0,
        2,
        MENU_ID_DA_DOWNLOAD_CNF_OPT_SAVE,
        MENU_ID_DA_DOWNLOAD_CNF_OPT_SAVE_TO,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_OPTION,
        STR_GLOBAL_OPTIONS,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_DOWNLOAD_CNF_OPT_SAVE,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_GLOBAL_SAVE,
        0));

    ADD_APPLICATION_MENUITEM5((
        MENU_ID_DA_DOWNLOAD_CNF_OPT_SAVE_TO,
        0,
        0,
        SHOW,
        NONMOVEABLE,
        MMI_RG_MENU_TYPE_ORIGINAL,
        STR_ID_DA_SELECT_FOLDER,
        0));

/******************** Menu resource IDs - finish ********************/

/******************** Menu Hilite/Hint Handlers - begin ********************/
/******************** Menu Hilite/Hint Handlers - finish ********************/
}
