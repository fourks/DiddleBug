/*******************************************************************************
 * Copyright (c) 2004-2006 palmOne, Inc. or its subsidiaries.
 * All rights reserved.
 ******************************************************************************/
/**
 * @defgroup    PmSysGadgetLib Gadget Library
 * @brief       This library provides supports for application that wants to
 *              manage system gadgets or support big buttons in the applications.
 *
 * Application that wishes to update/ retrieve the status of system gadget such
 * as the battery indicator, signal strength or bluetooth indicator can use this
 * library to do so. This library also provides APIs for application that wants
 * to include big button resource.
 *
 * @{
 * @}
 */
/**
 * @ingroup PmSysGadgetLib
 */

/**
 * @file  PmSysGadgetLibCommon.h
 * @brief Public 68k header file for system Library that exports system gadget related APIs.
 *
 * This file contains the common definitions and structures for the gadget-related APIs.
 * <hr>
 */

#ifndef __PM_SYS_GADGET_LIB_COMMON_H__
#define __PM_SYS_GADGET_LIB_COMMON_H__

/********************************************************************
 * Constants
 ********************************************************************/

#define kPmSysGadgetLibType     sysFileTLibrary       /**< Library type */
#define kPmSysGadgetLibCreator  pmFileCSysGadgetLib   /**< Library creator ID */
#define kPmSysGadgetLibName     "PmSysGadgetLib-PmSg" /**< Library name */

/**
 * This selector gets sent with a frmGadgetMiscEvent to let you know that the
 * gadget has been selected.  The numbers are picked semi-randomly so that generic
 * code (like PmUIUtilFrmDoDialogWithCallback()) can tell that this is actually
 * a button press without doing the wrong thing for other people's gadget events.
 *
 * Note that in most code, you shouldn't need to worry about checking the data,
 * since you know exactly what gadgets are on your form and what kind of events
 * they send.
 **/
#define kPmSysGadgetBbutGadgetMiscSelectSelector  7014                  /**< Randomish number so people can
                                                                             easily detect big button presses */
#define kPmSysGadgetBbutGadgetMiscSelectData      ((void*)0xBADC0DE1)   /**< Magic # to make conflicts even less
                                                                             likely for  detecting big  button presses.*/


/**
 * This is the type of big button resources.  The ID should match the ID of
 * the form...
 **/
#define kPmSysGadgetBbutRscType                   'bBut'           /**< Registered: yes */

/**
 * Feature that says that status gadget API exists and what revision it is
 **/
/*@{*/
#define kPmSysGadgetFtrIDStatusGadgetRev          1
#define kPmSysGadgetFtrValStatusGadgetRev1        0x0001  // Revision 1 of API
/*@}*/

/**
 *  Constants added for PTT Notification
 */
#define kPttNotificationEvent                     'pPTT'
#define kPttNotificationStatusOffset              (0xF00)

/********************************************************************
 * Enums
 ********************************************************************/
/**
 * Equates for supporting system handled status gadgets
 **/
typedef enum
  {
    pmSysGadgetStatusGadgetNone = 0,       /**< No type specified for status gadget */
    pmSysGadgetStatusGadgetBattery = 1,    /**< Status gadget is a battery meter */
    pmSysGadgetStatusGadgetSignal = 2,     /**< Status gadget is a signal strength indicator */
    pmSysGadgetStatusGadgetBt = 3,         /**< Status gadget is a Bluetooth status indicator */
    pmSysGadgetStatusGadgetEvdo = 4,       /**< Status gadget is an EVDO status indicator */
    pmSysGadgetStatusGadgetLine = 5,       /**< Status gadget is an Active line status indicator */
    pmSysGadgetStatusGadgetRoaming = 6,    /**< Status gadget is a Roaming status indicator */
    pmSysGadgetStatusGadgetCallFwd = 7,    /**< Status gadget is a Call Forwarding status indicator */
    pmSysGadgetStatusGadgetVm = 8,         /**< Status gadget is a Voicemail status indicator */
    pmSysGadgetStatusGadgetOperator = 9,   /**< Status gadget is an Operator status indicator */
    pmSysGadgetStatusGadgetPhoneCall = 10, /**< Status gadget is an Operator status indicator */
    pmSysGadgetStatusGadgetTty = 11,       /**< Status gadget is a TTY status indicator */
    pmSysGadgetStatusGadgetPtt = 12        /**< Status gadget is a PTT status indicator, RJS added 22May06 */
  } PmSysGadgetStatusGadgetTypeEnum;

/** Bluetooth radio status */
typedef enum
  {
    kIndicatorBtOff       = 0x0700, /**< Bt Radio turned off */
    kIndicatorBtOn,                 /**< Bt radio turned on */
    kIndicatorBtConnectHeadset,     /**< Connected to Headset */
    kIndicatorBtConnectOther,       /**< Connected to other Bt devices */
    kIndicatorBtDUN,                /**< Connected to DUN */
    kIndicatorBtConnectAudio,       /**< Connected audio **/
    kIndicatorBtConnectStereo       /**< Connected stereo **/
  } PmSysGadgetBtStatusTypeEnum;


/********************************************************************
 * Structures
 ********************************************************************/

/**
 * @brief This is the structure of a single big button mapping...
 **/
typedef struct
  {
    UInt8 flags;
    UInt8 font;

    UInt16 gadgetID;

    UInt16 bitmapID;
    UInt16 stringID;
  }
PmSysGadgetBbutMappingType;

/**
 * @brief This is the structure of a big button resource...
 **/
typedef struct
  {
    UInt16 version;
    PmSysGadgetBbutMappingType mapArr[0];
  }
PmSysGadgetBbutResourceType;

/**
*   @brief This is the structure used by the PTT notification event
**/
typedef struct
{
    UInt32 creatorId;     // creator ID where bitmap can be found
    UInt16 uBitmapId;     // bitmap to show in PTT gadget
    UInt16 uStatus;       // add the kPttNotificationStatusOffset to the PTT status
}
PmSysGadgetPttNotificationType;


/********************************************************************
 * Traps
 ********************************************************************/
/**
 * @name Function Traps
 */
/*@{*/
#define kPmSysGadgetLibTrapOpen                     sysLibTrapOpen
#define kPmSysGadgetLibTrapClose                    sysLibTrapClose
#define kPmSysGadgetLibTrapStatusGadgetTypeSet      (sysLibTrapCustom)
#define kPmSysGadgetLibTrapStatusGadgetsUpdate      (sysLibTrapCustom+1)
#define kPmSysGadgetLibTrapBbutInstallFromResource  (sysLibTrapCustom+2)
#define kPmSysGadgetLibTrapBbutInstallNewButton     (sysLibTrapCustom+3)
#define kPmSysGadgetLibTrapBbutSetLabel             (sysLibTrapCustom+4)
#define kPmSysGadgetLibTrapBbutSetBitmap            (sysLibTrapCustom+5)
#define kPmSysGadgetLibTrapBbutHitBigButton         (sysLibTrapCustom+6)
/*@}*/

#endif // __PM_SYS_GADGET_LIB_COMMON_H__
