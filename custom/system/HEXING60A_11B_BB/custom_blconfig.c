/*****************************************************************************
*  Copyright Statement:
*  --------------------
*  This software is protected by Copyright and the information contained
*  herein is confidential. The software may not be copied and the information
*  contained herein may not be used or disclosed except with the written
*  permission of MediaTek Inc. (C) 2006
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
 *   custom_blconfig.c
 *
 * Project:
 * --------
 *   Maui_Software
 *
 * Description:
 * ------------
 *   This file provides the custom configurable APIs for Boot Loader
 *
 * Author:
 * -------
 *   Carlos Yeh (mtk02377)     system auto generator v1.66 + sysGenUtility v0.40
 *
 *============================================================================
 *             HISTORY
 * Below this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *------------------------------------------------------------------------------
 * $Revision$
 * $Modtime$
 * $Log$
 *
 * 05 14 2012 carlos.yeh
 *  [Change Feature] Support BROM USBDL v2 flow
 * .
 *
 * 01 30 2012 qmei.yang
 *  [SystemService][Auto-Gen][Sys Gen][scatGen][Internal Refinement] Refactory sysgen2.pl
 * sysgen2.pl v1.42
 * scatInfo.pm v0.01
 * sysgenUtility.pm v0.15
 * FileInfo.pm v0.04
 * custom_demp.h.template
 * custom_scatstruct.c.template
 * custom_scatstruct.h.template
 * custom_blconfig.c.template
 *
 * 01 30 2012 qmei.yang
 *  [SystemService][Auto-Gen][Sys Gen][scatGen][Internal Refinement] Refactory sysgen2.pl
 * sysgen2.pl v1.42
 * scatInfo.pm v0.01
 * sysgenUtility.pm v0.15
 * FileInfo.pm v0.04
 * custom_demp.h.template
 * custom_scatstruct.c.template
 * custom_scatstruct.h.template
 * custom_blconfig.c.template
 *
 *------------------------------------------------------------------------------
 * Upper this line, this part is controlled by PVCS VM. DO NOT MODIFY!!
 *============================================================================
 ****************************************************************************/

#include "kal_general_types.h"
#include "kbd_table.h"
#include "custom_fota.h"
#include "bl_custom.h"
#include "bl_common.h"
#include "SST_secure.h"
#include <string.h>

#ifdef __SV5_ENABLED__
#include "br_GFH.h"
#include "br_GFH_maui_info.h"
#endif

#include "custom_FeatureConfig.h"

#ifdef __MTK_TARGET__

/*****************************************************************************
*
*                          Facilities
*
*****************************************************************************/

/* Plese do not modify the following content: ----- START ----- */

#define CS0_BASE_ADDRESS 0x00000000
#define CS1_BASE_ADDRESS 0x10000000

#define REMAPPING_ADDR (CS1_BASE_ADDRESS)
#define REMAPPING_MASK (REMAPPING_ADDR-1)

/* -------------------------------------------------
 * Tell the Bootloader where the address is
 * Default value : generated based on scatter file
 * -------------------------------------------------*/
kal_uint32 custom_EXTBL_baseaddr(void)
{
   return 0x4400;
}

/* -------------------------------------------------
 * Tell the Bootloader where the address is
 * Default value : generated based on scatter file
 * -------------------------------------------------*/
kal_uint32 custom_ROM_baseaddr(void)
{
   return 0x10010000;
}

/* -------------------------------------------------
 * Tell the Bootloader where the address is
 * Default value : generated based on scatter file, if feature disable , generate 0xFFFFFFFF
 * -------------------------------------------------*/
kal_uint32 custom_FACTORY_ROM_baseaddr(void)
{
   return 0xFFFFFFFF;
}

/* -------------------------------------------------
 * Tell the Bootloader what the /CS1 base address is
 * Default value : generated based on scatter file
 * -------------------------------------------------*/
kal_uint32 custom_RAM_baseaddr(void)
{
   /* RAM base address BEFORE remapping */
   return CS1_BASE_ADDRESS;
}
/* Plese do not modify the following content: ----- END ----- */



/*****************************************************************************
*
*                          Common options
*
*****************************************************************************/

/* --------------------------------------------------------------------
 * Define what kinds of messages can be dumped to UART
 * --------------------------------------------------------------------*/
#if defined(BOOTLOADER_DEBUG_LEVEL)
const LOG_LEVEL bootloader_debug_level = BOOTLOADER_DEBUG_LEVEL;
#else  /* BOOTLOADER_DEBUG_LEVEL */
#if defined(__TC01__)
const LOG_LEVEL bootloader_debug_level = LOG_NONE;
#else  /* __TC01__ */
const LOG_LEVEL bootloader_debug_level = LOG_DEBUG;
#endif  /* __TC01__ */
#endif  /* BOOTLOADER_DEBUG_LEVEL */

/* --------------------------------------------------------------------
 * Define bootloader version string getter
 * --------------------------------------------------------------------*/
kal_uint32 custom_get_bootloader_version(kal_uint8 *version, kal_uint32 len)
{
   const kal_uint8 blVersionStr[] = "BL Ver Str 0.1";

   if(len >= sizeof(blVersionStr)-1)
   {
      memcpy(version, blVersionStr, sizeof(blVersionStr)-1);
      return sizeof(blVersionStr)-1;
   }

   return 0;
}

/*****************************************************************************
*
*                          USB/UART DL part
*
*****************************************************************************/

extern const char gpio_camera_reset_pin;

/* -------------------------------------------------
 * USB Download GPIO Configure
 * The setting of USBDL GPIO has been integrated to Drv Tool
 * Set gpio_usbdl_pin directly in Drv Tool to enable USBDL trigger by GPIO
 * -------------------------------------------------*/

/* -------------------------------------------------
 * USB Download Key Configure
 * Default : Right Softkey
 * To disable USBDL by key press, set it NO_USBDL_KEY
 * -------------------------------------------------*/
#if defined(USBDL_KEY_POSITION)
const kal_uint8 usbdlkey_position = USBDL_KEY_POSITION;
#else  /* USBDL_KEY_POSITION */
#ifndef __COSMOS_MMI_PACKAGE__
const kal_uint8 usbdlkey_position = DEVICE_KEY_SK_RIGHT;
#else  /* __COSMOS_MMI_PACKAGE__ */
const kal_uint8 usbdlkey_position = DEVICE_KEY_BACK;
#endif  /* __COSMOS_MMI_PACKAGE__ */
#endif  /* USBDL_KEY_POSITION */

#if defined(USBDL_KEY_POSITION2)
const kal_uint8 usbdlkey_position2 = USBDL_KEY_POSITION2;
#else  /* USBDL_KEY_POSITION2 */
const kal_uint8 usbdlkey_position2 = NO_USBDL_KEY;
#endif  /* USBDL_KEY_POSITION2 */

#if defined(USBDL_KEY_RESCUE_POSITION)
const kal_uint8 usbdlkey_rescue_position = USBDL_KEY_RESCUE_POSITION;
#else  /* USBDL_KEY_RESCUE_POSITION */
const kal_uint8 usbdlkey_rescue_position = DEVICE_KEY_0;
#endif  /* USBDL_KEY_RESCUE_POSITION */

#if defined(USBDL_KEY_RESCUE_POSITION2)
const kal_uint8 usbdlkey_rescue_position2 = USBDL_KEY_RESCUE_POSITION2;
#else  /* USBDL_KEY_RESCUE_POSITION2 */
const kal_uint8 usbdlkey_rescue_position2 = DEVICE_KEY_1;
#endif  /* USBDL_KEY_RESCUE_POSITION2 */

/* -------------------------------------------------
 * USB Download Auto Mode Configure, in ms
 * Default : NO_USBDL_AUTO_TIMEOUT
 * To disable USBDL by key press, set it NO_USBDL_AUTO_TIMEOUT
 * Maximum is 65535
 * -------------------------------------------------*/
#if defined(USBDL_AUTO_TIMEOUT)
const kal_uint16 usbdlauto_timeout    = USBDL_AUTO_TIMEOUT;
#else  /* USBDL_AUTO_TIMEOUT */
#if defined(__TC01__)
const kal_uint16 usbdlauto_timeout    = 3000;
#elif defined(__BROM_USBDL_V2__)
const kal_uint16 usbdlauto_timeout    = 3000;
#else  /* __TC01__ */
const kal_uint16 usbdlauto_timeout    = NO_USBDL_AUTO_TIMEOUT;
#endif  /* __TC01__ */
#endif  /* USBDL_AUTO_TIMEOUT */

/* -------------------------------------------------
 * USB Download Holding mode
 * Default : KAL_FALSE
 * When holding mode is enabled, Bootloader will wait for USB connection forever once USBDL is triggered
 * Note: Should not used with USBDL AUTO
 * -------------------------------------------------*/
#if defined(USBDL_HOLDING_MODE)
const kal_bool usbdl_holding_mode = USBDL_HOLDING_MODE;
#else  /* USBDL_HOLDING_MODE */
const kal_bool usbdl_holding_mode = KAL_FALSE;
#endif  /* USBDL_HOLDING_MODE */

/* --------------------------------------------------------------------
 * Customization of USB Cable detection function
 * If the default detection methods are not suitable for the customized device, it is possible 
 * to use the function to override the original detection
 * When bootloader needs to know whether the USB cabel exists or not, it will call this function
 * Note: This function may be called several times during the USBDL procedure
 * Return values:
 *    0xffffffff:    Customized USB cable detection flow is not defined
 *    0x00000001:    Customized USB cable detection flow is defined and USB cable exists
 *    0x00000000:    Customized USB cable detection flow is defined and USB cable doesn't exist
 * Default value:
 *	   MTK original USB detection flow is used
 * --------------------------------------------------------------------*/
kal_uint32 custom_USB_Cable_Detection(void)
{
	return 0xffffffff;
}

/* -------------------------------------------------
 * USB Fast Meta key
 * Default : NO_META_KEY
 * When press Fast Meta Key, Bootloader will not try to open USB COM port but switch to
 * USB Meta mode directly in order to speed up the ready of Meta mode 
 * -------------------------------------------------*/
#if defined(FAST_META_KEY_POSITION)
const kal_uint8 metakey_position = FAST_META_KEY_POSITION;
#else  /* FAST_META_KEY_POSITION */
const kal_uint8 metakey_position = NO_META_KEY;
#endif  /* FAST_META_KEY_POSITION */


/*****************************************************************************
*
*                          Secure USB/UART DL part
*
*****************************************************************************/

#ifdef __UBL__

/* --------------------------------------------------------------------
 * USB Download for End User: DA version check customization function
 * --------------------------------------------------------------------*/
#ifdef __EXT_BOOTLOADER__
kal_bool custom_DA_version_check(kal_uint32 daVersion, kal_uint32 daVersionCust, kal_uint32 daVersionCriteria, kal_uint32 daVersionCustCriteria)
{
#if defined(__SECURE_USB_DOWNLOAD__) || defined(__SECURE_UART_DOWNLOAD__)   
   if( (daVersionCriteria != 0xffffffff && daVersion < daVersionCriteria) ||
       (daVersionCustCriteria != 0xffffffff && daVersionCust < daVersionCustCriteria) )
   {
      return KAL_FALSE;
   }
#endif /* __SECURE_USB_DOWNLOAD__ || __SECURE_UART_DOWNLOAD__ */

   return KAL_TRUE;
}
#endif /* __EXT_BOOTLOADER__ */


/* Plese do not modify the following content: ----- START ----- */
#ifdef __SECURE_USB_DOWNLOAD__
#include "custom_nvram_sec.h"

extern kal_uint32 SST_Get_SW_Version(kal_uint32 rom_base, kal_uint8 *ver_buf, kal_uint32 len);
extern kal_bool bl_Get_Secure_RO(kal_uint32 dest, kal_uint32 len, kal_uint32 rom_base, kal_uint32 rom_length);
extern kal_uint32 custom_get_NORFLASH_Size(void);

#pragma arm section rwdata = "EXTRAM_RW", zidata = "EXTRAM_ZI"
kal_uint32 g_custom_SEC_RO_buf[(sizeof(SEC_RO_ST) + SECURE_RO_SIZE_OVERHEAD)>>2] = {0};
#define CUSTOM_SEC_RO      (*((SEC_RO_ST*)g_custom_SEC_RO_buf))
#pragma arm section rwdata, zidata

#ifdef __EXT_BOOTLOADER__
/* --------------------------------------------------------------------
 * USB Download for End User: get the secure RO
 * --------------------------------------------------------------------*/
kal_bool custom_get_secureRO(void)
{
#ifdef __SV5_ENABLED__

   if ( CUSTOM_SEC_RO.m_sec_ro_ver != 0 )
   {
      return KAL_TRUE;
   }

   if(bl_Get_Secure_RO((kal_uint32)g_custom_SEC_RO_buf, sizeof(g_custom_SEC_RO_buf), 0, 0) == KAL_TRUE)
   {
      kal_uint32 *pSecureRoAddr = (kal_uint32*) bl_Allocate_BL_DA_SharedData(BL_DA_SHARED_DATA_ID_SECURE_RO_ADDR, 8);

      *pSecureRoAddr = (kal_uint32)g_custom_SEC_RO_buf;
      pSecureRoAddr++;
      
      *pSecureRoAddr = sizeof(SEC_RO_ST);
      
      return KAL_TRUE;
   }

#else
   kal_int32 i;
   kal_uint32 secInfoSearchAddr[2];
      
   if ( CUSTOM_SEC_RO.m_sec_ro_ver != 0 )
   {
      return KAL_TRUE;
   }

   secInfoSearchAddr[0] = custom_ROM_baseaddr() & REMAPPING_MASK;     //SecInfo
   secInfoSearchAddr[1] = 0x100000;                                      //SecInfo Tail

   for ( i=0; i<sizeof(secInfoSearchAddr)/sizeof(*secInfoSearchAddr); i++ )
   {
      bl_Get_Secure_RO((kal_uint32)&g_custom_SEC_RO_buf, sizeof(g_custom_SEC_RO_buf), secInfoSearchAddr[i], custom_get_NORFLASH_Size());

      if (NVRAM_SECRET_KEY_SIZE == CUSTOM_SEC_RO.m_custom_secret_key_len )
      {
         if (memcmp(CUSTOM_SEC_RO.m_custom_magic_tail, SEC_RO_MAGIC_TAIL_VALUE, strlen(SEC_RO_MAGIC_TAIL_VALUE)) == 0)
         {
            return KAL_TRUE;
         }
      }
   }
#endif

   //Not found any SecInfo
   CUSTOM_SEC_RO.m_sec_ro_ver = 0;
   return KAL_FALSE;
}

/* --------------------------------------------------------------------
 * USB Download for End User: get the symmetric key
 * Default : the key is in the SEC_RO region 
 * --------------------------------------------------------------------*/
kal_uint32 custom_get_symmetric_key(kal_uint8 *key, kal_uint32 len)
{
   custom_get_secureRO();

   if (NVRAM_SECRET_KEY_SIZE == CUSTOM_SEC_RO.m_custom_secret_key_len )
   {
      if (len >= CUSTOM_SEC_RO.m_custom_symmetric_key_len)
      {
         memcpy(key, CUSTOM_SEC_RO.m_custom_symmetric_key,
              CUSTOM_SEC_RO.m_custom_symmetric_key_len);
         return CUSTOM_SEC_RO.m_custom_symmetric_key_len;
      }
   }

   return 0;
}

/* --------------------------------------------------------------------
 * USB Download for End User: get the asymmetric key
 * Default : the key is in the SEC_RO region 
 * --------------------------------------------------------------------*/
kal_uint32 custom_get_asymmetric_key(kal_uint8 *key, kal_uint32 len)
{
   custom_get_secureRO();

   if (NVRAM_SECRET_KEY_SIZE == CUSTOM_SEC_RO.m_custom_secret_key_len )
   {
      if (len >= NVRAM_ASYMMETRIC_KEY_MAX_SIZE)
      {
         memcpy(key, (void *)(&(CUSTOM_SEC_RO.m_custom_asymmetric_key)),
         					NVRAM_ASYMMETRIC_KEY_MAX_SIZE);
         return NVRAM_ASYMMETRIC_KEY_MAX_SIZE;
      }
   }

   return 0;
}
#endif /* __EXT_BOOTLOADER__ */
#endif /* __SECURE_USB_DOWNLOAD__ */

#endif /* __UBL__ */

/* --------------------------------------------------------------------
 * USB Download for End User: get the software version in FLASH
 * --------------------------------------------------------------------*/
const kal_uint32 g_custom_secure_ro_addr = 0 & REMAPPING_MASK;

kal_uint32 custom_get_software_version(kal_uint8 *version, kal_uint32 len)
{
#ifdef __EXT_BOOTLOADER__
#ifdef __SECURE_USB_DOWNLOAD__
#ifdef __SV5_ENABLED__
      extern kal_uint32 g_maui_load_addr;
      GFH_MAUI_INFO_v1 *pMauiInfo;
      kal_uint32 status;
      

      if(g_maui_load_addr != INVALID_START_ADDR)
      {
         status = GFH_Find(g_maui_load_addr, GFH_MAUI_INFO, &pMauiInfo);
         if(status == 0 && len >= sizeof(pMauiInfo->m_project_id))
         {
            memcpy(version, pMauiInfo->m_project_id, sizeof(pMauiInfo->m_project_id));
            return sizeof(pMauiInfo->m_project_id);
         }
      }
#else
      return SST_Get_SW_Version(custom_ROM_baseaddr() & REMAPPING_MASK, version, len);
#endif
#endif /* __SECURE_USB_DOWNLOAD__ */
#endif /* __EXT_BOOTLOADER__ */

 return 0;
}

/* --------------------------------------------------------------------
 * USB Download for End User: check whether the SEC_RO is valid or not
 * --------------------------------------------------------------------*/
kal_bool custom_check_valid_secro(void)
{
#ifdef __EXT_BOOTLOADER__
#ifdef __SECURE_USB_DOWNLOAD__
   if ( custom_get_secureRO() == KAL_TRUE )
      {
         return KAL_TRUE;
      }
#endif /* __SECURE_USB_DOWNLOAD__ */
#endif /* __EXT_BOOTLOADER__ */

   return KAL_FALSE;
}

/* Plese do not modify the following content: ----- END ----- */



/*****************************************************************************
*
*                          FOTA support
*
*****************************************************************************/

/* Plese do not modify the following content: ----- START ----- */

#ifdef __FOTA_DM__
#ifdef __EXT_BOOTLOADER__
#if !defined(_NAND_FLASH_BOOTING_) && !defined(__EMMC_BOOTING__)

#include "drvflash.h"
extern NOR_FLASH_DRV_Data  FlashDriveData;

/* -------------------------------------------------
 * Tell the block index of the specified address
 * Default value : generated based on scatter file
 * -------------------------------------------------*/
kal_uint32 custom_Block_Size(kal_uint32 nor_addr)
{
   kal_uint32 blk_idx = 0;
   NOR_Flash_MTD_Data *mtdflash     = (NOR_Flash_MTD_Data *)FlashDriveData.MTDData;

   blk_idx = BlockIndex((void *)mtdflash, nor_addr & (~((kal_uint32)mtdflash->BaseAddr)));

   return BlockSize((void *)mtdflash, blk_idx);
}

/* -------------------------------------------------
 * Tell the execution address after remapping from load address
 * Default value : generated based on scatter file
 * -------------------------------------------------*/
kal_uint32 custom_Convert_to_execution(kal_uint32 nor_addr)
{
   kal_uint32 target_addr = 0;

#if defined(__UBL__)
   target_addr = nor_addr & (CS1_BASE_ADDRESS - 1);
#elif defined(__FUE__)
   extern kal_uint32 Image$$UA_INIT$$Base;
   target_addr = (kal_uint32)&Image$$UA_INIT$$Base;
#else
   target_addr = 0;
#endif

   return target_addr;

}

/* -------------------------------------------------
 * Tell the block base address of the specified address
 * Default value : generated based on scatter file
 * -------------------------------------------------*/
kal_uint32 custom_Block_Base(kal_uint32 nor_addr)
{
   kal_uint32 blk_idx = 0;
   NOR_Flash_MTD_Data *mtdflash     = (NOR_Flash_MTD_Data *)FlashDriveData.MTDData;

   blk_idx = BlockIndex((void *)mtdflash, nor_addr & (~((kal_uint32)mtdflash->BaseAddr)));
   return (kal_uint32)BlockAddress((void *)mtdflash, blk_idx);


}
#endif /* !_NAND_FLASH_BOOTING_ && !__EMMC_BOOTING__ */
#endif /* __EXT_BOOTLOADER__ */
#endif /* __FOTA_DM__ */

/* Plese do not modify the following content: ----- END ----- */


/*****************************************************************************
*
*                          Card Download Support
*
*****************************************************************************/
#ifdef __CARD_DOWNLOAD__
#ifdef __UBL__

#ifdef __EXT_BOOTLOADER__

/* -------------------------------------------------
 * Key and key structure should be defined by customers
 * -------------------------------------------------*/
#if 0
#ifndef __MTK_INTERNAL__

const kal_uint32 CDL_PublicKey[64] = {0};

#else

#define  M1_MAX_KEY_LEN                         128
typedef struct t_Customer_Public_Key
{
   kal_uint32 nELen;
   kal_uint32 nNLen;
   kal_uint16 MCoeff;
   kal_uint16 nCutLength;
   kal_uint16 E_Key[M1_MAX_KEY_LEN];
   kal_uint16 N_Key[M1_MAX_KEY_LEN]; /* 256, 512, 1024 bit */
} T_Customer_Public_Key;

const T_Customer_Public_Key CDL_PublicKey = 
{
   2,64,0x0051,8,
   {
      0x0001, 0x0001
   },
   {
      0x002A, 0x178D, 0xBCB4, 0xC985, 0xD21E, 0x2A71, 0xDBE4, 0x1E27, 
      0x29CD, 0x2285, 0x65B3, 0x6596, 0x2B4C, 0x8266, 0x057B, 0xB911, 
      0x283D, 0x1912, 0xB02D, 0x2B15, 0xB61D, 0x8DB9, 0xC1D9, 0x069C, 
      0xA352, 0xD7F6, 0x0EAB, 0x46EB, 0xB0CE, 0xAEC5, 0x842C, 0x92B1, 
      0x94FC, 0xD410, 0x60F5, 0x8F2C, 0x186A, 0x9527, 0xF40A, 0x4DF9, 
      0xA31D, 0x86C0, 0x7464, 0xB57C, 0x600A, 0xB37A, 0x02FB, 0xD0A6, 
      0x6399, 0xB779, 0x96A7, 0x9B5E, 0x2E8D, 0x0247, 0xA844, 0x28EE, 
      0x26B6, 0xAF64, 0x7C49, 0xC924, 0xD8DF, 0x5FBA, 0xEBAA, 0xB74F
   },
};

#endif /* __MTK_INTERNAL__ */
#endif
const kal_uint16 CDL_PublicKey[512] = 
{
   0x0002, 0x0000, 0x0040, 0x0000, 0x0051, 0x0008,
   0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
   0x002A, 0x178D, 0xBCB4, 0xC985, 0xD21E, 0x2A71, 0xDBE4, 0x1E27, 
   0x29CD, 0x2285, 0x65B3, 0x6596, 0x2B4C, 0x8266, 0x057B, 0xB911, 
   0x283D, 0x1912, 0xB02D, 0x2B15, 0xB61D, 0x8DB9, 0xC1D9, 0x069C, 
   0xA352, 0xD7F6, 0x0EAB, 0x46EB, 0xB0CE, 0xAEC5, 0x842C, 0x92B1, 
   0x94FC, 0xD410, 0x60F5, 0x8F2C, 0x186A, 0x9527, 0xF40A, 0x4DF9, 
   0xA31D, 0x86C0, 0x7464, 0xB57C, 0x600A, 0xB37A, 0x02FB, 0xD0A6, 
   0x6399, 0xB779, 0x96A7, 0x9B5E, 0x2E8D, 0x0247, 0xA844, 0x28EE, 
   0x26B6, 0xAF64, 0x7C49, 0xC924, 0xD8DF, 0x5FBA, 0xEBAA, 0xB74F  
};
/* --------------------------------------------------------------------
 * Card download: get the length of asymmetric key for card download
 * if this function returns 0, no signature check will be done
 * --------------------------------------------------------------------*/
kal_uint32 custom_get_CDL_asymmetric_key_len(void)
{
   return sizeof(CDL_PublicKey);
}

/* --------------------------------------------------------------------
 * Card download: get the asymmetric key for card download
 * Default : the key is defined in this file
 * --------------------------------------------------------------------*/
const kal_uint8* custom_get_CDL_asymmetric_key(void)
{
   return (const kal_uint8*)&CDL_PublicKey;
}

/* --------------------------------------------------------------------
 * Card download: version check function
 * --------------------------------------------------------------------*/
kal_bool custom_CDL_check_dl_package_version(kal_uint8 *romSwVer, kal_uint8 *pkgSwVer, kal_uint8 *pkgLimit)
{
   dbg_print("Rom SW=%s\n\rPkg SW=%s\n\r", romSwVer, pkgSwVer);

   //No update/downgrade policy
   
   if(*pkgLimit)
   {
      dbg_print("Pkg SW limit=%s\n\r", pkgLimit);
      if(strcmp((kal_char*)romSwVer, (kal_char*)pkgLimit))
      {
         dbg_print("This package should not be applied to this ROM\n\r");
         return KAL_FALSE;
      }
   }

   return KAL_TRUE;
}

/* --------------------------------------------------------------------
 * Card download: platform check function
 * --------------------------------------------------------------------*/
kal_bool custom_CDL_check_dl_platform_id(kal_uint8 *romPID, kal_uint8 *pkgPID, kal_uint8 *pkgLimit)
{
   kal_uint8 *p = (kal_uint8*)strchr((kal_char*)romPID, '.');
   
   dbg_print("Rom PID=%s\n\rPkg PID=%s\n\r", romPID, pkgPID);
   
   if(!p || strncmp((kal_char*)romPID, (kal_char*)pkgPID, p-romPID))
   {
      dbg_print("Mismatched platform\n\r");
      return KAL_FALSE;
   }
   
   if(*pkgLimit)
   {
      dbg_print("Pkg SW limit=%s\n\r", pkgLimit);
      if(strcmp((kal_char*)romPID, (kal_char*)pkgLimit))
      {
         dbg_print("This package should not be applied to this ROM\n\r");
         return KAL_FALSE;
      }
   }

   return KAL_TRUE;
}

/* --------------------------------------------------------------------
 * Card download: Customer's own check
 * --------------------------------------------------------------------*/
kal_bool custom_CDL_customer_info_check(kal_uint32 *pCustomerInfo, kal_uint32 len)
{
   return KAL_TRUE;
}
   
#endif /* __EXT_BOOTLOADER__ */

#endif /* __UBL__ */
#endif /* __CARD_DOWNLOAD__ */



#endif /* __MTK_TARGET__ */
