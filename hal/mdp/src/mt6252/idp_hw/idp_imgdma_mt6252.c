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
 *    idp_imgdma_mt6252.c
 *
 * Project:
 * --------
 *    MAUI
 *
 * Description:
 * ------------
 *
 *
 * Author:
 * -------
 * -------
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by ClearCase. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Log$
 *
 * 05 11 2011 peter.wang
 * removed!
 * .
 *
 * 05 09 2011 peter.wang
 * removed!
 * .
 *
 * 04 26 2011 peter.wang
 * removed!
 * .
 *
 * 04 22 2011 peter.wang
 * removed!
 * .
 *
 * 11 23 2010 cm.huang
 * removed!
 * .
 *
 * 11 15 2010 cm.huang
 * NULL
 * .
 *
 * 11 13 2010 cm.huang
 * NULL
 * .
 *
 * 11 01 2010 cm.huang
 * NULL
 * .
 *
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by ClearCase. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#define THIS_FILE_BELONGS_TO_IMAGE_DATA_PATH_MODULE_INTERNAL

#include <idp_define.h>

#if defined(DRV_IDP_6252_SERIES)

#include "IntrCtrl.h"

#include <mt6252\idp_hw\idp_imgdma_rotdma0.h>

/**
 * \brief Initialize the image DMA subsystem.
 *
 * \ingroup imgdma
 *
 * This functino will setup the interrupt for the image DMA
 * to level sensitive, and unmask all the interrupts for the
 * image DMA.
 */

#if defined(IDP_FULL_ISR_SUPPORT)
static
#endif
void idp_imgdma_LISR(void);

void
idp_imgdma_init(void)
{
#ifndef MDP_C_MODEL

#if defined(IDP_FULL_ISR_SUPPORT)
    IRQ_Register_LISR(IRQ_ROT_DMA_CODE, idp_imgdma_LISR, "IMGDMA");
#endif

    IRQSensitivity(IRQ_ROT_DMA_CODE, LEVEL_SENSITIVE);
    IRQUnmask(IRQ_ROT_DMA_CODE);

#endif // #ifndef MDP_C_MODEL

    // Initial the owner structure.
    idp_imgdma_rotdma0_init();
}

#if defined(IDP_FULL_ISR_SUPPORT)
static
#endif
void
idp_imgdma_LISR(void)
{
    idp_imgdma_rotdma0_LISR();
}


kal_uint32
idp_get_imgdma_status_reg_value(void)
{
    return 0;
}

#endif // #if defined(DRV_IDP_6252_SERIES)

