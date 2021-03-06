/*
 *  Copyright (c) 2000-2001 LSI Logic Corporation.
 *
 *
 *           Name:  MPI_CNFG.H
 *          Title:  MPI Config message, structures, and Pages
 *  Creation Date:  July 27, 2000
 *
 *    MPI Version:  01.01.09
 *
 *  Version History
 *  ---------------
 *
 *  Date      Version   Description
 *  --------  --------  ------------------------------------------------------
 *  05-08-00  00.10.01  Original release for 0.10 spec dated 4/26/2000.
 *  06-06-00  01.00.01  Update version number for 1.0 release.
 *  06-08-00  01.00.02  Added _PAGEVERSION definitions for all pages.
 *                      Added FcPhLowestVersion, FcPhHighestVersion, Reserved2
 *                      fields to FC_DEVICE_0 page, updated the page version.
 *                      Changed _FREE_RUNNING_CLOCK to _PACING_TRANSFERS in
 *                      SCSI_PORT_0, SCSI_DEVICE_0 and SCSI_DEVICE_1 pages
 *                      and updated the page versions.
 *                      Added _RESPONSE_ID_MASK definition to SCSI_PORT_1
 *                      page and updated the page version.
 *                      Added Information field and _INFO_PARAMS_NEGOTIATED
 *                      definitionto SCSI_DEVICE_0 page.
 *  06-22-00  01.00.03  Removed batch controls from LAN_0 page and updated the
 *                      page version.
 *                      Added BucketsRemaining to LAN_1 page, redefined the
 *                      state values, and updated the page version.
 *                      Revised bus width definitions in SCSI_PORT_0,
 *                      SCSI_DEVICE_0 and SCSI_DEVICE_1 pages.
 *  06-30-00  01.00.04  Added MaxReplySize to LAN_1 page and updated the page
 *                      version.
 *                      Moved FC_DEVICE_0 PageAddress description to spec.
 *  07-27-00  01.00.05  Corrected the SubsystemVendorID and SubsystemID field
 *                      widths in IOC_0 page and updated the page version.
 *  11-02-00  01.01.01  Original release for post 1.0 work
 *                      Added Manufacturing pages, IO Unit Page 2, SCSI SPI
 *                      Port Page 2, FC Port Page 4, FC Port Page 5
 *  11-15-00  01.01.02  Interim changes to match proposals
 *  12-04-00  01.01.03  Config page changes to match MPI rev 1.00.01.
 *  12-05-00  01.01.04  Modified config page actions.
 *  01-09-01  01.01.05  Added defines for page address formats.
 *                      Data size for Manufacturing pages 2 and 3 no longer
 *                      defined here.
 *                      Io Unit Page 2 size is fixed at 4 adapters and some
 *                      flags were changed.
 *                      SCSI Port Page 2 Device Settings modified.
 *                      New fields added to FC Port Page 0 and some flags
 *                      cleaned up.
 *                      Removed impedance flash from FC Port Page 1.
 *                      Added FC Port pages 6 and 7.
 *  01-25-01  01.01.06  Added MaxInitiators field to FcPortPage0.
 *  01-29-01  01.01.07  Changed some defines to make them 32 character unique.
 *                      Added some LinkType defines for FcPortPage0.
 *  02-20-01  01.01.08  Started using MPI_POINTER.
 *  02-27-01  01.01.09  Replaced MPI_CONFIG_PAGETYPE_SCSI_LUN with
 *                      MPI_CONFIG_PAGETYPE_RAID_VOLUME.
 *                      Added definitions and structures for IOC Page 2 and
 *                      RAID Volume Page 2.
 *  --------------------------------------------------------------------------
 */

#ifndef MPI_CNFG_H
#define MPI_CNFG_H


/*****************************************************************************
*
*       C o n f i g    M e s s a g e    a n d    S t r u c t u r e s
*
*****************************************************************************/

typedef struct _CONFIG_PAGE_HEADER
{
    U8                      PageVersion;
    U8                      PageLength;
    U8                      PageNumber;
    U8                      PageType;
} fCONFIG_PAGE_HEADER, MPI_POINTER PTR_CONFIG_PAGE_HEADER,
  ConfigPageHeader_t, MPI_POINTER pConfigPageHeader_t;

typedef union _CONFIG_PAGE_HEADER_UNION
{
   ConfigPageHeader_t  Struct;
   U8                  Bytes[4];
   U16                 Word16[2];
   U32                 Word32;
} ConfigPageHeaderUnion, MPI_POINTER pConfigPageHeaderUnion,
  fCONFIG_PAGE_HEADER_UNION, MPI_POINTER PTR_CONFIG_PAGE_HEADER_UNION;


/****************************************************************************/
/*  PageType field values                                                   */
/****************************************************************************/
#define MPI_CONFIG_PAGEATTR_READ_ONLY               (0x00)
#define MPI_CONFIG_PAGEATTR_CHANGEABLE              (0x10)
#define MPI_CONFIG_PAGEATTR_PERSISTENT              (0x20)
#define MPI_CONFIG_PAGEATTR_MASK                    (0xF0)

#define MPI_CONFIG_PAGETYPE_IO_UNIT                 (0x00)
#define MPI_CONFIG_PAGETYPE_IOC                     (0x01)
#define MPI_CONFIG_PAGETYPE_BIOS                    (0x02)
#define MPI_CONFIG_PAGETYPE_SCSI_PORT               (0x03)
#define MPI_CONFIG_PAGETYPE_SCSI_DEVICE             (0x04)
#define MPI_CONFIG_PAGETYPE_FC_PORT                 (0x05)
#define MPI_CONFIG_PAGETYPE_FC_DEVICE               (0x06)
#define MPI_CONFIG_PAGETYPE_LAN                     (0x07)
#define MPI_CONFIG_PAGETYPE_RAID_VOLUME             (0x08)
#define MPI_CONFIG_PAGETYPE_MANUFACTURING           (0x09)
#define MPI_CONFIG_PAGETYPE_MASK                    (0x0F)

#define MPI_CONFIG_TYPENUM_MASK                     (0x0FFF)


/****************************************************************************
 *  PageAddres field values
 ****************************************************************************/
#define MPI_SCSI_PORT_PGAD_PORT_MASK                (0x000000FF)

#define MPI_SCSI_DEVICE_TARGET_ID_MASK              (0x000000FF)
#define MPI_SCSI_DEVICE_TARGET_ID_SHIFT             (0)
#define MPI_SCSI_DEVICE_BUS_MASK                    (0x0000FF00)
#define MPI_SCSI_DEVICE_BUS_SHIFT                   (8)

#define MPI_SCSI_LUN_TARGET_ID_MASK                 (0x000000FF)
#define MPI_SCSI_LUN_TARGET_ID_SHIFT                (0)
#define MPI_SCSI_LUN_BUS_MASK                       (0x0000FF00)
#define MPI_SCSI_LUN_BUS_SHIFT                      (8)
#define MPI_SCSI_LUN_LUN_MASK                       (0x00FF0000)
#define MPI_SCSI_LUN_LUN_SHIFT                      (16)

#define MPI_FC_PORT_PGAD_PORT_MASK                  (0xF0000000)
#define MPI_FC_PORT_PGAD_PORT_SHIFT                 (28)
#define MPI_FC_PORT_PGAD_FORM_MASK                  (0x0F000000)
#define MPI_FC_PORT_PGAD_FORM_INDEX                 (0x01000000)
#define MPI_FC_PORT_PGAD_INDEX_MASK                 (0x0000FFFF)
#define MPI_FC_PORT_PGAD_INDEX_SHIFT                (0)

#define MPI_FC_DEVICE_PGAD_PORT_MASK                (0xF0000000)
#define MPI_FC_DEVICE_PGAD_PORT_SHIFT               (28)
#define MPI_FC_DEVICE_PGAD_FORM_MASK                (0x0F000000)
#define MPI_FC_DEVICE_PGAD_FORM_NEXT_DID            (0x00000000)
#define MPI_FC_DEVICE_PGAD_ND_PORT_MASK             (0xF0000000)
#define MPI_FC_DEVICE_PGAD_ND_PORT_SHIFT            (28)
#define MPI_FC_DEVICE_PGAD_ND_DID_MASK              (0x00FFFFFF)
#define MPI_FC_DEVICE_PGAD_ND_DID_SHIFT             (0)
#define MPI_FC_DEVICE_PGAD_FORM_BUS_TID             (0x01000000)
#define MPI_FC_DEVICE_PGAD_BT_BUS_MASK              (0x0000FF00)
#define MPI_FC_DEVICE_PGAD_BT_BUS_SHIFT             (8)
#define MPI_FC_DEVICE_PGAD_BT_TID_MASK              (0x000000FF)
#define MPI_FC_DEVICE_PGAD_BT_TID_SHIFT             (0)


/****************************************************************************/
/*  Config Request Message                                                          */
/****************************************************************************/
typedef struct _MSG_CONFIG
{
    U8                      Action;
    U8                      Reserved;
    U8                      ChainOffset;
    U8                      Function;
    U8                      Reserved1[3];
    U8                      MsgFlags;
    U32                     MsgContext;
    U8                      Reserved2[8];
   fCONFIG_PAGE_HEADER      Header;
    U32                     PageAddress;
    SGE_IO_UNION            PageBufferSGE;
} MSG_CONFIG, MPI_POINTER PTR_MSG_CONFIG,
  Config_t, MPI_POINTER pConfig_t;


/****************************************************************************/
/*  Action field values                                                     */
/****************************************************************************/
#define MPI_CONFIG_ACTION_PAGE_HEADER               (0x00)
/*#define MPI_CONFIG_ACTION_PAGE_READ                 (0x01) *//* obsolete */
#define MPI_CONFIG_ACTION_PAGE_READ_CURRENT         (0x01)
/*#define MPI_CONFIG_ACTION_PAGE_WRITE                (0x02) *//* obsolete */
#define MPI_CONFIG_ACTION_PAGE_WRITE_CURRENT        (0x02)
#define MPI_CONFIG_ACTION_PAGE_DEFAULT              (0x03)
/*#define MPI_CONFIG_ACTION_PAGE_WRITE_COMMIT         (0x04) */ /* obsolete */
#define MPI_CONFIG_ACTION_PAGE_WRITE_NVRAM          (0x04)
#define MPI_CONFIG_ACTION_PAGE_READ_DEFAULT         (0x05)
#define MPI_CONFIG_ACTION_PAGE_READ_NVRAM           (0x06)


/* Config Reply Message */
typedef struct _MSG_CONFIG_REPLY
{
    U8                      Action;
    U8                      Reserved;
    U8                      MsgLength;
    U8                      Function;
    U8                      Reserved1[3];
    U8                      MsgFlags;
    U32                     MsgContext;
    U8                      Reserved2[2];
    U16                     IOCStatus;
    U32                     IOCLogInfo;
   fCONFIG_PAGE_HEADER      Header;
} MSG_CONFIG_REPLY, MPI_POINTER PTR_MSG_CONFIG_REPLY,
  ConfigReply_t, MPI_POINTER pConfigReply_t;



/*****************************************************************************
*
*               C o n f i g u r a t i o n    P a g e s
*
*****************************************************************************/

/****************************************************************************/
/*  Manufacturing Config pages                                              */
/****************************************************************************/
#define MPI_MANUFACTPAGE_DEVICEID_FC909             (0x0621)
#define MPI_MANUFACTPAGE_DEVICEID_FC919             (0x0624)
#define MPI_MANUFACTPAGE_DEVICEID_FC929             (0x0622)
#define MPI_MANUFACTPAGE_DEVID_53C1030              (0x0030)
#define MPI_MANUFACTPAGE_DEVID_53C1030ZC            (0x0031)
#define MPI_MANUFACTPAGE_DEVID_53C1035              (0x0035)

typedef struct _CONFIG_PAGE_MANUFACTURING_0
{
   fCONFIG_PAGE_HEADER      Header;
    U8                      ChipName[16];
    U8                      ChipRevision[8];
    U8                      BoardName[16];
    U8                      BoardAssembly[16];
    U8                      BoardTracerNumber[16];

} fCONFIG_PAGE_MANUFACTURING_0, MPI_POINTER PTR_CONFIG_PAGE_MANUFACTURING_0,
  ManufacturingPage0_t, MPI_POINTER pManufacturingPage0_t;

#define MPI_MANUFACTURING0_PAGEVERSION                 (0x00)


typedef struct _CONFIG_PAGE_MANUFACTURING_1
{
   fCONFIG_PAGE_HEADER      Header;
    U8                      VPD[256];
} fCONFIG_PAGE_MANUFACTURING_1, MPI_POINTER PTR_CONFIG_PAGE_MANUFACTURING_1,
  ManufacturingPage1_t, MPI_POINTER pManufacturingPage1_t;

#define MPI_MANUFACTURING1_PAGEVERSION                 (0x00)


typedef struct _MPI_CHIP_REVISION_ID
{
    U16 DeviceID;
    U8  PCIRevisionID;
    U8  Reserved;
} MPI_CHIP_REVISION_ID, MPI_POINTER PTR_MPI_CHIP_REVISION_ID,
  MpiChipRevisionId_t, MPI_POINTER pMpiChipRevisionId_t;


typedef struct _CONFIG_PAGE_MANUFACTURING_2
{
   fCONFIG_PAGE_HEADER                  Header;
    MPI_CHIP_REVISION_ID                ChipId;
    U32                                 HwSettings[1];
} fCONFIG_PAGE_MANUFACTURING_2, MPI_POINTER PTR_CONFIG_PAGE_MANUFACTURING_2,
  ManufacturingPage2_t, MPI_POINTER pManufacturingPage2_t;

#define MPI_MANUFACTURING2_PAGEVERSION                  (0x00)


typedef struct _CONFIG_PAGE_MANUFACTURING_3
{
   fCONFIG_PAGE_HEADER                  Header;
    MPI_CHIP_REVISION_ID                ChipId;
    U32                                 Info[1];
} fCONFIG_PAGE_MANUFACTURING_3, MPI_POINTER PTR_CONFIG_PAGE_MANUFACTURING_3,
  ManufacturingPage3_t, MPI_POINTER pManufacturingPage3_t;

#define MPI_MANUFACTURING3_PAGEVERSION                  (0x00)


/****************************************************************************/
/*  IO Unit Config Pages                                                    */
/****************************************************************************/

typedef struct _CONFIG_PAGE_IO_UNIT_0
{
   fCONFIG_PAGE_HEADER      Header;
    U64                     UniqueValue;
} fCONFIG_PAGE_IO_UNIT_0, MPI_POINTER PTR_CONFIG_PAGE_IO_UNIT_0,
  IOUnitPage0_t, MPI_POINTER pIOUnitPage0_t;

#define MPI_IOUNITPAGE0_PAGEVERSION                     (0x00)


typedef struct _CONFIG_PAGE_IO_UNIT_1
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Flags;
} fCONFIG_PAGE_IO_UNIT_1, MPI_POINTER PTR_CONFIG_PAGE_IO_UNIT_1,
  IOUnitPage1_t, MPI_POINTER pIOUnitPage1_t;

#define MPI_IOUNITPAGE1_PAGEVERSION                     (0x00)

#define MPI_IOUNITPAGE1_MULTI_FUNCTION                  (0x00000000)
#define MPI_IOUNITPAGE1_SINGLE_FUNCTION                 (0x00000001)
#define MPI_IOUNITPAGE1_MULTI_PATHING                   (0x00000002)
#define MPI_IOUNITPAGE1_SINGLE_PATHING                  (0x00000000)

#define MPI_IOUNITPAGE1_FORCE_32                        (0x00000080)


typedef struct _MPI_ADAPTER_INFO
{
    U8      PciBusNumber;
    U8      PciDeviceAndFunctionNumber;
    U16     AdapterFlags;
} MPI_ADAPTER_INFO, MPI_POINTER PTR_MPI_ADAPTER_INFO,
  MpiAdapterInfo_t, MPI_POINTER pMpiAdapterInfo_t;

#define MPI_ADAPTER_INFO_FLAGS_EMBEDDED                 (0x0001)
#define MPI_ADAPTER_INFO_FLAGS_INIT_STATUS              (0x0002)

typedef struct _CONFIG_PAGE_IO_UNIT_2
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Flags;
    U32                     BiosVersion;
    MPI_ADAPTER_INFO        AdapterOrder[4];
} fCONFIG_PAGE_IO_UNIT_2, MPI_POINTER PTR_CONFIG_PAGE_IO_UNIT_2,
  IOUnitPage2_t, MPI_POINTER pIOUnitPage2_t;

#define MPI_IOUNITPAGE2_PAGEVERSION                     (0x00)

#define MPI_IOUNITPAGE2_FLAGS_RAID_DISABLE              (0x00000001)
#define MPI_IOUNITPAGE2_FLAGS_PAUSE_ON_ERROR            (0x00000002)
#define MPI_IOUNITPAGE2_FLAGS_VERBOSE_ENABLE            (0x00000004)
#define MPI_IOUNITPAGE2_FLAGS_COLOR_VIDEO_DISABLE       (0x00000008)
#define MPI_IOUNITPAGE2_FLAGS_DONT_HOOK_INT_40          (0x00000010)


/****************************************************************************/
/*  IOC Config Pages                                                        */
/****************************************************************************/

typedef struct _CONFIG_PAGE_IOC_0
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     TotalNVStore;
    U32                     FreeNVStore;
    U16                     VendorID;
    U16                     DeviceID;
    U8                      RevisionID;
    U8                      Reserved[3];
    U32                     ClassCode;
    U16                     SubsystemVendorID;
    U16                     SubsystemID;
} fCONFIG_PAGE_IOC_0, MPI_POINTER PTR_CONFIG_PAGE_IOC_0,
  IOCPage0_t, MPI_POINTER pIOCPage0_t;

#define MPI_IOCPAGE0_PAGEVERSION                        (0x01)

typedef struct _CONFIG_PAGE_IOC_1
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Flags;
    U32                     CoalescingTimeout;
    U8                      CoalescingDepth;
    U8                      Reserved[3];
} fCONFIG_PAGE_IOC_1, MPI_POINTER PTR_CONFIG_PAGE_IOC_1,
  IOCPage1_t, MPI_POINTER pIOCPage1_t;

#define MPI_IOCPAGE1_PAGEVERSION                        (0x00)

#define MPI_IOCPAGE1_REPLY_COALESCING                   (0x00000001)

typedef struct _CONFIG_PAGE_IOC_2_RAID_VOL
{
    U8                      VolumeTargetID;
    U8                      VolumeBus;
    U16                     Reserved;
    U8                      VolumeVersionMinor;
    U8                      VolumeVersionMajor;
    U8                      VolumeRaidType;
    U8                      Reserved1;
} fCONFIG_PAGE_IOC_2_RAID_VOL, MPI_POINTER PTR_CONFIG_PAGE_IOC_2_RAID_VOL,
  ConfigPageIoc2RaidVol_t, MPI_POINTER pConfigPageIoc2RaidVol_t;

typedef struct _CONFIG_PAGE_IOC_2
{
   fCONFIG_PAGE_HEADER          Header;
    U32                         CapabilitiesFlags;
    U8                          NumActiveVolumes;
    U8                          MaxVolumes;
    U16                         Reserved;
   fCONFIG_PAGE_IOC_2_RAID_VOL  RaidVolume[1];
} fCONFIG_PAGE_IOC_2, MPI_POINTER PTR_CONFIG_PAGE_IOC_2,
  IOCPage2_t, MPI_POINTER pIOCPage2_t;

#define MPI_IOCPAGE2_PAGEVERSION                        (0x00)

/* IOC Page 2 Capabilities flags */

#define MPI_IOCPAGE2_CAP_FLAGS_RAID_0_SUPPORT           (0x00000001)
#define MPI_IOCPAGE2_CAP_FLAGS_RAID_1_SUPPORT           (0x00000002)
#define MPI_IOCPAGE2_CAP_FLAGS_LSI_MIRROR_SUPPORT       (0x00000004)
#define MPI_IOCPAGE2_CAP_FLAGS_RAID_5_SUPPORT           (0x00000008)
#define MPI_IOCPAGE2_CAP_FLAGS_RAID_10_SUPPORT          (0x00000010)

/* IOC Page 2 Volume RAID Type values */

#define MPI_IOCPAGE2_VOL_TYPE_RAID_0                    (0x00)
#define MPI_IOCPAGE2_VOL_TYPE_RAID_1                    (0x01)
#define MPI_IOCPAGE2_VOL_TYPE_LSI_MIRROR                (0x02)
#define MPI_IOCPAGE2_VOL_TYPE_RAID_5                    (0x05)
#define MPI_IOCPAGE2_VOL_TYPE_RAID_10                   (0x0A)


/****************************************************************************/
/*  SCSI Port Config Pages                                                  */
/****************************************************************************/

typedef struct _CONFIG_PAGE_SCSI_PORT_0
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Capabilities;
    U32                     PhysicalInterface;
} fCONFIG_PAGE_SCSI_PORT_0, MPI_POINTER PTR_CONFIG_PAGE_SCSI_PORT_0,
  SCSIPortPage0_t, MPI_POINTER pSCSIPortPage0_t;

#define MPI_SCSIPORTPAGE0_PAGEVERSION                   (0x01)

#define MPI_SCSIPORTPAGE0_CAP_IU                        (0x00000001)
#define MPI_SCSIPORTPAGE0_CAP_DT                        (0x00000002)
#define MPI_SCSIPORTPAGE0_CAP_QAS                       (0x00000004)
#define MPI_SCSIPORTPAGE0_CAP_PACING_TRANSFERS          (0x00000008)
#define MPI_SCSIPORTPAGE0_CAP_MIN_SYNC_PERIOD_MASK      (0x0000FF00)
#define MPI_SCSIPORTPAGE0_CAP_MAX_SYNC_OFFSET_MASK      (0x00FF0000)
#define MPI_SCSIPORTPAGE0_CAP_WIDE                      (0x20000000)
#define MPI_SCSIPORTPAGE0_CAP_AIP                       (0x80000000)

#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_TYPE_MASK          (0x00000003)
#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_HVD                (0x01)
#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_SE                 (0x02)
#define MPI_SCSIPORTPAGE0_PHY_SIGNAL_LVD                (0x03)

typedef struct _CONFIG_PAGE_SCSI_PORT_1
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Configuration;
} fCONFIG_PAGE_SCSI_PORT_1, MPI_POINTER PTR_CONFIG_PAGE_SCSI_PORT_1,
  SCSIPortPage1_t, MPI_POINTER pSCSIPortPage1_t;

#define MPI_SCSIPORTPAGE1_PAGEVERSION                   (0x01)

#define MPI_SCSIPORTPAGE1_CFG_PORT_SCSI_ID_MASK         (0x000000FF)
#define MPI_SCSIPORTPAGE1_CFG_PORT_RESPONSE_ID_MASK     (0xFFFF0000)

typedef struct _MPI_DEVICE_INFO
{
    U8      Timeout;
    U8      SyncFactor;
    U16     DeviceFlags;
} MPI_DEVICE_INFO, MPI_POINTER PTR_MPI_DEVICE_INFO,
  MpiDeviceInfo_t, MPI_POINTER pMpiDeviceInfo_t;

typedef struct _CONFIG_PAGE_SCSI_PORT_2
{
   fCONFIG_PAGE_HEADER  Header;
    U32                 PortFlags;
    U32                 PortSettings;
    MPI_DEVICE_INFO     DeviceSettings[16];
} fCONFIG_PAGE_SCSI_PORT_2, MPI_POINTER PTR_CONFIG_PAGE_SCSI_PORT_2,
  SCSIPortPage2_t, MPI_POINTER pSCSIPortPage2_t;

#define MPI_SCSIPORTPAGE2_PAGEVERSION                       (0x01)

#define MPI_SCSIPORTPAGE2_PORT_FLAGS_SCAN_HIGH_TO_LOW       (0x00000001)
#define MPI_SCSIPORTPAGE2_PORT_FLAGS_PARITY_ENABLE          (0x00000002)
#define MPI_SCSIPORTPAGE2_PORT_FLAGS_AVOID_SCSI_RESET       (0x00000004)
#define MPI_SCSIPORTPAGE2_PORT_FLAGS_ALTERNATE_CHS          (0x00000008)
#define MPI_SCSIPORTPAGE2_PORT_FLAGS_TERMINATION_DISABLE    (0x00000010)

#define MPI_SCSIPORTPAGE2_PORT_HOST_ID_MASK                 (0x0000000F)
#define MPI_SCSIPORTPAGE2_PORT_MASK_INIT_HBA                (0x00000030)
#define MPI_SCSIPORTPAGE2_PORT_DISABLE_INIT_HBA             (0x00000000)
#define MPI_SCSIPORTPAGE2_PORT_BIOS_INIT_HBA                (0x00000010)
#define MPI_SCSIPORTPAGE2_PORT_OS_INIT_HBA                  (0x00000020)
#define MPI_SCSIPORTPAGE2_PORT_BIOS_OS_INIT_HBA             (0x00000030)
#define MPI_SCSIPORTPAGE2_PORT_REMOVABLE_MEDIA              (0x000000C0)
#define MPI_SCSIPORTPAGE2_PORT_SPINUP_DELAY_MASK            (0x00000F00)
#define MPI_SCSIPORTPAGE2_PORT_MASK_NEGO_MASTER_SETTINGS    (0x00003000)
#define MPI_SCSIPORTPAGE2_PORT_NEGO_MASTER_SETTINGS         (0x00000000)
#define MPI_SCSIPORTPAGE2_PORT_NONE_MASTER_SETTINGS         (0x00000001)
#define MPI_SCSIPORTPAGE2_PORT_ALL_MASTER_SETTINGS          (0x00000003)

#define MPI_SCSIPORTPAGE2_DEVICE_DISCONNECT_ENABLE          (0x00000001)
#define MPI_SCSIPORTPAGE2_DEVICE_ID_SCAN_ENABLE             (0x00000002)
#define MPI_SCSIPORTPAGE2_DEVICE_LUN_SCAN_ENABLE            (0x00000004)
#define MPI_SCSIPORTPAGE2_DEVICE_TAG_QUEUE_ENABLE           (0x00000008)
#define MPI_SCSIPORTPAGE2_DEVICE_WIDE_DISABLE               (0x00000010)
#define MPI_SCSIPORTPAGE2_DEVICE_BOOT_CHOICE                (0x00000020)


/****************************************************************************/
/*  SCSI Target Device Config Pages                                         */
/****************************************************************************/

typedef struct _CONFIG_PAGE_SCSI_DEVICE_0
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     NegotiatedParameters;
    U32                     Information;
} fCONFIG_PAGE_SCSI_DEVICE_0, MPI_POINTER PTR_CONFIG_PAGE_SCSI_DEVICE_0,
  SCSIDevicePage0_t, MPI_POINTER pSCSIDevicePage0_t;

#define MPI_SCSIDEVPAGE0_PAGEVERSION                    (0x01)

#define MPI_SCSIDEVPAGE0_NP_IU                          (0x00000001)
#define MPI_SCSIDEVPAGE0_NP_DT                          (0x00000002)
#define MPI_SCSIDEVPAGE0_NP_QAS                         (0x00000004)
#define MPI_SCSIDEVPAGE0_NP_PACING_TRANSFERS            (0x00000008)
#define MPI_SCSIDEVPAGE0_NP_NEG_SYNC_PERIOD_MASK        (0x0000FF00)
#define MPI_SCSIDEVPAGE0_NP_NEG_SYNC_OFFSET_MASK        (0x00FF0000)
#define MPI_SCSIDEVPAGE0_NP_WIDE                        (0x20000000)
#define MPI_SCSIDEVPAGE0_NP_AIP                         (0x80000000)

#define MPI_SCSIDEVPAGE0_INFO_PARAMS_NEGOTIATED         (0x00000001)

typedef struct _CONFIG_PAGE_SCSI_DEVICE_1
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     RequestedParameters;
    U32                     DomainValidation;
    U32                     Configuration;
} fCONFIG_PAGE_SCSI_DEVICE_1, MPI_POINTER PTR_CONFIG_PAGE_SCSI_DEVICE_1,
  SCSIDevicePage1_t, MPI_POINTER pSCSIDevicePage1_t;

#define MPI_SCSIDEVPAGE1_PAGEVERSION                    (0x01)

#define MPI_SCSIDEVPAGE1_RP_IU                          (0x00000001)
#define MPI_SCSIDEVPAGE1_RP_DT                          (0x00000002)
#define MPI_SCSIDEVPAGE1_RP_QAS                         (0x00000004)
#define MPI_SCSIDEVPAGE1_RP_PACING_TRANSFERS            (0x00000008)
#define MPI_SCSIDEVPAGE1_RP_MIN_SYNC_PERIOD_MASK        (0x0000FF00)
#define MPI_SCSIDEVPAGE1_RP_MAX_SYNC_OFFSET_MASK        (0x00FF0000)
#define MPI_SCSIDEVPAGE1_RP_WIDE                        (0x20000000)
#define MPI_SCSIDEVPAGE1_RP_AIP                         (0x80000000)

#define MPI_SCSIDEVPAGE1_DV_LVD_DRIVE_STRENGTH_MASK     (0x00000003)
#define MPI_SCSIDEVPAGE1_DV_SE_SLEW_RATE_MASK           (0x00000300)

#define MPI_SCSIDEVPAGE1_CONF_PPR_ALLOWED               (0x00000001)

/****************************************************************************/
/*  FC Port Config Pages                                                    */
/****************************************************************************/

typedef struct _CONFIG_PAGE_FC_PORT_0
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Flags;
    U8                      MPIPortNumber;
    U8                      LinkType;
    U8                      PortState;
    U8                      Reserved;
    U32                     PortIdentifier;
    U64                     WWNN;
    U64                     WWPN;
    U32                     SupportedServiceClass;
    U32                     SupportedSpeeds;
    U32                     CurrentSpeed;
    U32                     MaxFrameSize;
    U64                     FabricWWNN;
    U64                     FabricWWPN;
    U32                     DiscoveredPortsCount;
    U32                     MaxInitiators;
} fCONFIG_PAGE_FC_PORT_0, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_0,
  FCPortPage0_t, MPI_POINTER pFCPortPage0_t;

#define MPI_FCPORTPAGE0_PAGEVERSION                     (0x01)

#define MPI_FCPORTPAGE0_FLAGS_PROT_MASK                 (0x0000000F)
#define MPI_FCPORTPAGE0_FLAGS_PROT_FCP_INIT             (MPI_PORTFACTS_PROTOCOL_INITIATOR)
#define MPI_FCPORTPAGE0_FLAGS_PROT_FCP_TARG             (MPI_PORTFACTS_PROTOCOL_TARGET)
#define MPI_FCPORTPAGE0_FLAGS_PROT_LAN                  (MPI_PORTFACTS_PROTOCOL_LAN)
#define MPI_FCPORTPAGE0_FLAGS_PROT_LOGBUSADDR           (MPI_PORTFACTS_PROTOCOL_LOGBUSADDR)

#define MPI_FCPORTPAGE0_FLAGS_ALIAS_ALPA_SUPPORTED      (0x00000010)
#define MPI_FCPORTPAGE0_FLAGS_ALIAS_WWN_SUPPORTED       (0x00000020)
#define MPI_FCPORTPAGE0_FLAGS_FABRIC_WWN_VALID          (0x00000030)

#define MPI_FCPORTPAGE0_FLAGS_ATTACH_TYPE_MASK          (0x00000700)
#define MPI_FCPORTPAGE0_FLAGS_ATTACH_POINT_TO_POINT     (0x00000000)
#define MPI_FCPORTPAGE0_FLAGS_ATTACH_PRIVATE_LOOP       (0x00000100)
#define MPI_FCPORTPAGE0_FLAGS_ATTACH_FABRIC_DIRECT      (0x00000200)
#define MPI_FCPORTPAGE0_FLAGS_ATTACH_PUBLIC_LOOP        (0x00000300)
#define MPI_FCPORTPAGE0_FLAGS_ATTACH_NO_INIT            (0x00000700)

#define MPI_FCPORTPAGE0_LTYPE_RESERVED                  (0x00)
#define MPI_FCPORTPAGE0_LTYPE_OTHER                     (0x01)
#define MPI_FCPORTPAGE0_LTYPE_UNKNOWN                   (0x02)
#define MPI_FCPORTPAGE0_LTYPE_COPPER                    (0x03)
#define MPI_FCPORTPAGE0_LTYPE_SINGLE_1300               (0x04)
#define MPI_FCPORTPAGE0_LTYPE_SINGLE_1500               (0x05)
#define MPI_FCPORTPAGE0_LTYPE_50_LASER_MULTI            (0x06)
#define MPI_FCPORTPAGE0_LTYPE_50_LED_MULTI              (0x07)
#define MPI_FCPORTPAGE0_LTYPE_62_LASER_MULTI            (0x08)
#define MPI_FCPORTPAGE0_LTYPE_62_LED_MULTI              (0x09)
#define MPI_FCPORTPAGE0_LTYPE_MULTI_LONG_WAVE           (0x0A)
#define MPI_FCPORTPAGE0_LTYPE_MULTI_SHORT_WAVE          (0x0B)
#define MPI_FCPORTPAGE0_LTYPE_LASER_SHORT_WAVE          (0x0C)
#define MPI_FCPORTPAGE0_LTYPE_LED_SHORT_WAVE            (0x0D)
#define MPI_FCPORTPAGE0_LTYPE_1300_LONG_WAVE            (0x0E)
#define MPI_FCPORTPAGE0_LTYPE_1500_LONG_WAVE            (0x0F)

#define MPI_FCPORTPAGE0_PORTSTATE_UNKNOWN               (0x01)      /*(SNIA)HBA_PORTSTATE_UNKNOWN       1 Unknown */
#define MPI_FCPORTPAGE0_PORTSTATE_ONLINE                (0x02)      /*(SNIA)HBA_PORTSTATE_ONLINE        2 Operational */
#define MPI_FCPORTPAGE0_PORTSTATE_OFFLINE               (0x03)      /*(SNIA)HBA_PORTSTATE_OFFLINE       3 User Offline */
#define MPI_FCPORTPAGE0_PORTSTATE_BYPASSED              (0x04)      /*(SNIA)HBA_PORTSTATE_BYPASSED      4 Bypassed */
#define MPI_FCPORTPAGE0_PORTSTATE_DIAGNOST              (0x05)      /*(SNIA)HBA_PORTSTATE_DIAGNOSTICS   5 In diagnostics mode */
#define MPI_FCPORTPAGE0_PORTSTATE_LINKDOWN              (0x06)      /*(SNIA)HBA_PORTSTATE_LINKDOWN      6 Link Down */
#define MPI_FCPORTPAGE0_PORTSTATE_ERROR                 (0x07)      /*(SNIA)HBA_PORTSTATE_ERROR         7 Port Error */
#define MPI_FCPORTPAGE0_PORTSTATE_LOOPBACK              (0x08)      /*(SNIA)HBA_PORTSTATE_LOOPBACK      8 Loopback */

#define MPI_FCPORTPAGE0_SUPPORT_CLASS_1                 (0x00000001)
#define MPI_FCPORTPAGE0_SUPPORT_CLASS_2                 (0x00000002)
#define MPI_FCPORTPAGE0_SUPPORT_CLASS_3                 (0x00000004)

#define MPI_FCPORTPAGE0_SUPPORT_1GBIT_SPEED             (0x00000001) /* (SNIA)HBA_PORTSPEED_1GBIT 1  1 GBit/sec  */
#define MPI_FCPORTPAGE0_SUPPORT_2GBIT_SPEED             (0x00000002) /* (SNIA)HBA_PORTSPEED_2GBIT 2  2 GBit/sec  */
#define MPI_FCPORTPAGE0_SUPPORT_10GBIT_SPEED            (0x00000004) /* (SNIA)HBA_PORTSPEED_10GBIT 4 10 GBit/sec */

#define MPI_FCPORTPAGE0_CURRENT_SPEED_1GBIT             MPI_FCPORTPAGE0_SUPPORT_1GBIT_SPEED
#define MPI_FCPORTPAGE0_CURRENT_SPEED_2GBIT             MPI_FCPORTPAGE0_SUPPORT_2GBIT_SPEED
#define MPI_FCPORTPAGE0_CURRENT_SPEED_10GBIT            MPI_FCPORTPAGE0_SUPPORT_10GBIT_SPEED


typedef struct _CONFIG_PAGE_FC_PORT_1
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Flags;
    U64                     NoSEEPROMWWNN;
    U64                     NoSEEPROMWWPN;
    U8                      HardALPA;
    U8                      LinkConfig;
    U8                      TopologyConfig;
    U8                      Reserved;
} fCONFIG_PAGE_FC_PORT_1, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_1,
  FCPortPage1_t, MPI_POINTER pFCPortPage1_t;

#define MPI_FCPORTPAGE1_PAGEVERSION                     (0x01)

#define MPI_FCPORTPAGE1_FLAGS_SORT_BY_DID               (0x00000001)
#define MPI_FCPORTPAGE1_FLAGS_SORT_BY_WWN               (0x00000000)

#define MPI_FCPORTPAGE1_FLAGS_PROT_MASK                 (0xF0000000)
#define MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT                (28)
#define MPI_FCPORTPAGE1_FLAGS_PROT_FCP_INIT             ((U32)MPI_PORTFACTS_PROTOCOL_INITIATOR << MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)
#define MPI_FCPORTPAGE1_FLAGS_PROT_FCP_TARG             ((U32)MPI_PORTFACTS_PROTOCOL_TARGET << MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)
#define MPI_FCPORTPAGE1_FLAGS_PROT_LAN                  ((U32)MPI_PORTFACTS_PROTOCOL_LAN << MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)
#define MPI_FCPORTPAGE1_FLAGS_PROT_LOGBUSADDR           ((U32)MPI_PORTFACTS_PROTOCOL_LOGBUSADDR << MPI_FCPORTPAGE1_FLAGS_PROT_SHIFT)

#define MPI_FCPORTPAGE1_HARD_ALPA_NOT_USED              (0xFF)

#define MPI_FCPORTPAGE1_LCONFIG_SPEED_MASK              (0x0F)
#define MPI_FCPORTPAGE1_LCONFIG_SPEED_1GIG              (0x00)
#define MPI_FCPORTPAGE1_LCONFIG_SPEED_2GIG              (0x01)
#define MPI_FCPORTPAGE1_LCONFIG_SPEED_4GIG              (0x02)
#define MPI_FCPORTPAGE1_LCONFIG_SPEED_10GIG             (0x03)
#define MPI_FCPORTPAGE1_LCONFIG_SPEED_AUTO              (0x0F)

#define MPI_FCPORTPAGE1_TOPOLGY_MASK                    (0x0F)
#define MPI_FCPORTPAGE1_TOPOLGY_NLPORT                  (0x01)
#define MPI_FCPORTPAGE1_TOPOLGY_NPORT                   (0x02)
#define MPI_FCPORTPAGE1_TOPOLGY_AUTO                    (0x0F)


typedef struct _CONFIG_PAGE_FC_PORT_2
{
   fCONFIG_PAGE_HEADER      Header;
    U8                      NumberActive;
    U8                      ALPA[126];
    U8                      Reserved;
} fCONFIG_PAGE_FC_PORT_2, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_2,
  FCPortPage2_t, MPI_POINTER pFCPortPage2_t;

#define MPI_FCPORTPAGE2_PAGEVERSION                     (0x00)


typedef struct _FC_PORT_PERSISTENT
{
    U64                     WWNN;
    U64                     WWPN;
    U8                      TargetID;
    U8                      Bus;
    U16                     Flags;
} FC_PORT_PERSISTENT, MPI_POINTER PTR_FC_PORT_PERSISTENT,
  PersistentData_t, MPI_POINTER pPersistentData_t;

#define MPI_PERSISTENT_FLAGS_SHIFT                      (16)
#define MPI_PERSISTENT_FLAGS_ENTRY_VALID                (0x0001)
#define MPI_PERSISTENT_FLAGS_SCAN_ID                    (0x0002)
#define MPI_PERSISTENT_FLAGS_SCAN_LUNS                  (0x0004)
#define MPI_PERSISTENT_FLAGS_BOOT_DEVICE                (0x0008)

typedef struct _CONFIG_PAGE_FC_PORT_3
{
   fCONFIG_PAGE_HEADER      Header;
    FC_PORT_PERSISTENT      Entry[1];
} fCONFIG_PAGE_FC_PORT_3, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_3,
  FCPortPage3_t, MPI_POINTER pFCPortPage3_t;

#define MPI_FCPORTPAGE3_PAGEVERSION                     (0x00)


typedef struct _CONFIG_PAGE_FC_PORT_4
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     PortFlags;
    U32                     PortSettings;
} fCONFIG_PAGE_FC_PORT_4, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_4,
  FCPortPage4_t, MPI_POINTER pFCPortPage4_t;

#define MPI_FCPORTPAGE4_PAGEVERSION                     (0x00)

#define MPI_FCPORTPAGE4_PORT_FLAGS_ALTERNATE_CHS        (0x00000008)

#define MPI_FCPORTPAGE4_PORT_MASK_INIT_HBA              (0x00000030)
#define MPI_FCPORTPAGE4_PORT_DISABLE_INIT_HBA           (0x00000000)
#define MPI_FCPORTPAGE4_PORT_BIOS_INIT_HBA              (0x00000010)
#define MPI_FCPORTPAGE4_PORT_OS_INIT_HBA                (0x00000020)
#define MPI_FCPORTPAGE4_PORT_BIOS_OS_INIT_HBA           (0x00000030)
#define MPI_FCPORTPAGE4_PORT_REMOVABLE_MEDIA            (0x000000C0)
#define MPI_FCPORTPAGE4_PORT_SPINUP_DELAY_MASK          (0x00000F00)


typedef struct _CONFIG_PAGE_FC_PORT_5_ALIAS_INFO
{
    U8      Flags;
    U8      AliasAlpa;
    U16     Reserved;
    U64     AliasWWNN;
    U64     AliasWWPN;
} fCONFIG_PAGE_FC_PORT_5_ALIAS_INFO, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_5_ALIAS_INFO,
  FcPortPage5AliasInfo_t, MPI_POINTER pFcPortPage5AliasInfo_t;

typedef struct _CONFIG_PAGE_FC_PORT_5
{
   fCONFIG_PAGE_HEADER                  Header;
   fCONFIG_PAGE_FC_PORT_5_ALIAS_INFO    AliasInfo[1];
} fCONFIG_PAGE_FC_PORT_5, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_5,
  FCPortPage5_t, MPI_POINTER pFCPortPage5_t;

#define MPI_FCPORTPAGE5_PAGEVERSION                     (0x00)

#define MPI_FCPORTPAGE5_FLAGS_ALIAS_ALPA_VALID          (0x01)
#define MPI_FCPORTPAGE5_FLAGS_ALIAS_WWN_VALID           (0x02)


typedef struct _CONFIG_PAGE_FC_PORT_6
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Reserved;
    U64                     TimeSinceReset;
    U64                     TxFrames;
    U64                     RxFrames;
    U64                     TxWords;
    U64                     RxWords;
    U64                     LipCount;
    U64                     NosCount;
    U64                     ErrorFrames;
    U64                     DumpedFrames;
    U64                     LinkFailureCount;
    U64                     LossOfSyncCount;
    U64                     LossOfSignalCount;
    U64                     PrimativeSeqErrCount;
    U64                     InvalidTxWordCount;
    U64                     InvalidCrcCount;
    U64                     FcpInitiatorIoCount;
} fCONFIG_PAGE_FC_PORT_6, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_6,
  FCPortPage6_t, MPI_POINTER pFCPortPage6_t;

#define MPI_FCPORTPAGE6_PAGEVERSION                     (0x00)


typedef struct _CONFIG_PAGE_FC_PORT_7
{
   fCONFIG_PAGE_HEADER      Header;
    U32                     Reserved;
    U8                      PortSymbolicName[256];
} fCONFIG_PAGE_FC_PORT_7, MPI_POINTER PTR_CONFIG_PAGE_FC_PORT_7,
  FCPortPage7_t, MPI_POINTER pFCPortPage7_t;

#define MPI_FCPORTPAGE7_PAGEVERSION                     (0x00)


/****************************************************************************/
/*  FC Device Config Pages                                                  */
/****************************************************************************/

typedef struct _CONFIG_PAGE_FC_DEVICE_0
{
   fCONFIG_PAGE_HEADER      Header;
    U64                     WWNN;
    U64                     WWPN;
    U32                     PortIdentifier;
    U8                      Protocol;
    U8                      Flags;
    U16                     BBCredit;
    U16                     MaxRxFrameSize;
    U8                      Reserved1;
    U8                      PortNumber;
    U8                      FcPhLowestVersion;
    U8                      FcPhHighestVersion;
    U8                      CurrentTargetID;
    U8                      CurrentBus;
} fCONFIG_PAGE_FC_DEVICE_0, MPI_POINTER PTR_CONFIG_PAGE_FC_DEVICE_0,
  FCDevicePage0_t, MPI_POINTER pFCDevicePage0_t;

#define MPI_FC_DEVICE_PAGE0_PAGEVERSION                 (0x02)

#define MPI_FC_DEVICE_PAGE0_FLAGS_TARGETID_BUS_VALID    (0x01)

#define MPI_FC_DEVICE_PAGE0_PROT_IP                     (0x01)
#define MPI_FC_DEVICE_PAGE0_PROT_FCP_TARGET             (0x02)
#define MPI_FC_DEVICE_PAGE0_PROT_FCP_INITIATOR          (0x04)

#define MPI_FC_DEVICE_PAGE0_PGAD_PORT_MASK              (MPI_FC_DEVICE_PGAD_PORT_MASK)
#define MPI_FC_DEVICE_PAGE0_PGAD_FORM_MASK              (MPI_FC_DEVICE_PGAD_FORM_MASK)
#define MPI_FC_DEVICE_PAGE0_PGAD_FORM_NEXT_DID          (MPI_FC_DEVICE_PGAD_FORM_NEXT_DID)
#define MPI_FC_DEVICE_PAGE0_PGAD_FORM_BUS_TID           (MPI_FC_DEVICE_PGAD_FORM_BUS_TID)
#define MPI_FC_DEVICE_PAGE0_PGAD_DID_MASK               (MPI_FC_DEVICE_PGAD_ND_DID_MASK)
#define MPI_FC_DEVICE_PAGE0_PGAD_BUS_MASK               (MPI_FC_DEVICE_PGAD_BT_BUS_MASK)
#define MPI_FC_DEVICE_PAGE0_PGAD_BUS_SHIFT              (MPI_FC_DEVICE_PGAD_BT_BUS_SHIFT)
#define MPI_FC_DEVICE_PAGE0_PGAD_TID_MASK               (MPI_FC_DEVICE_PGAD_BT_TID_MASK)


/****************************************************************************/
/*  RAID Volume Config Pages                                                  */
/****************************************************************************/

typedef struct _RAIDVOL2_EM_PHYS_ID
{
    U8                      TargetID;
    U8                      Bus;
    U8                      IocNumber;
    U8                      PhysDiskNumber;
    U8                      Reserved[8];
    U8                      PhysicalDiskIdentifier[16];
    U8                      ProductId[16];
    U8                      InfoOffset0;
    U8                      InfoSize0;
    U8                      InfoOffset1;
    U8                      InfoSize1;
    U8                      Info[32];
} RAIDVOL2_EM_PHYS_ID, MPI_POINTER PTR_RAIDVOL2_EM_PHYS_ID,
  RaidVol2EmPhysicalID_t, MPI_POINTER pRaidVol2EmPhysicalID_t;

typedef struct _RAIDVOL2_EM_DISK_INFO
{
    U32                     DiskStatus;
    U32                     DeviceSettings;
    U16                     ErrorCount;
    U16                     Reserved;
    U8                      ErrorCdbByte;
    U8                      ErrorSenseKey;
    U8                      ErrorASC;
    U8                      ErrorASCQ;
    U16                     SmartCount;
    U8                      SmartASC;
    U8                      SmartASCQ;
} RAIDVOL2_EM_DISK_INFO, MPI_POINTER PTR_RAIDVOL2_EM_DISK_INFO,
  RaidVol2EmDiskInfo_t, MPI_POINTER pRaidVol2EmDiskInfo_t;

/* RAID Volume 2 EM Physical Disk DiskStatus flags */

#define MPI_RAIDVOLPAGE2_PHYS_DISK_PRIMARY              (0x00000001)
#define MPI_RAIDVOLPAGE2_PHYS_DISK_SECONDARY            (0x00000002)
#define MPI_RAIDVOLPAGE2_PHYS_DISK_HOT_SPARE            (0x00000004)
#define MPI_RAIDVOLPAGE2_PHYS_DISK_OUT_OF_SYNC          (0x00000008)
#define MPI_RAIDVOLPAGE2_PHYS_DISK_OFFLINE              (0x00000010)
#define MPI_RAIDVOLPAGE2_PHYS_DISK_NOT_RESPONDING       (0x00000020)

typedef struct _RAIDVOL2_EM_PHYSICAL_DISK
{
    RAIDVOL2_EM_PHYS_ID     Id;
    RAIDVOL2_EM_DISK_INFO   Info;
} RAIDVOL2_EM_PHYSICAL_DISK, MPI_POINTER PTR_RAIDVOL2_EM_PHYSICAL_DISK,
  RaidVol2EmPhysicalDisk_t, MPI_POINTER pRaidVol2EmPhysicalDisk_t;

#define MPI_RAIDVOLPAGE2_MAX_DISKS                      (3)

typedef struct _CONFIG_PAGE_RAID_VOL_2
{
   fCONFIG_PAGE_HEADER          Header;
    U32                         VolumeStatus;
    U32                         VolumeSettings;
    U32                         Reserved;
    U64                         MaxLba;
    U32                         BlockSize;
    U8                          InquirySize;
    U8                          NumPhysicalDisks;
    U16                         Reserved1;
    U8                          InquiryData[56];
    RAIDVOL2_EM_PHYSICAL_DISK   EMPhysicalDisk[MPI_RAIDVOLPAGE2_MAX_DISKS];
} fCONFIG_PAGE_RAID_VOL_2, MPI_POINTER PTR_CONFIG_PAGE_RAID_VOL_2,
  RaidVolumePage2_t, MPI_POINTER pRaidVolumePage2_t;

#define MPI_RAIDVOLPAGE2_PAGEVERSION                    (0x00)

/* RAID Volume Page 2 VolumeStatus defines */

#define MPI_RAIDVOLPAGE2_STATUS_ENABLED                 (0x00000001)
#define MPI_RAIDVOLPAGE2_STATUS_QUIESCED                (0x00000002)
#define MPI_RAIDVOLPAGE2_STATUS_RESYNC_IN_PROGRESS      (0x00000004)
#define MPI_RAIDVOLPAGE2_STATUS_DEGRADED                (0x00000008)

/* RAID Volume Page 2 VolumeSettings defines */

#define MPI_RAIDVOLPAGE2_SETTING_WRITE_CACHING_ENABLE   (0x00000001)
#define MPI_RAIDVOLPAGE2_SETTING_OFFLINE_ON_SMART       (0x00000002)
#define MPI_RAIDVOLPAGE2_SETTING_AUTO_CONFIGURE         (0x00000004)


/****************************************************************************/
/* LAN Config Pages                                                         */
/****************************************************************************/

typedef struct _CONFIG_PAGE_LAN_0
{
    ConfigPageHeader_t      Header;
    U16                     TxRxModes;
    U16                     Reserved;
    U32                     PacketPrePad;
} fCONFIG_PAGE_LAN_0, MPI_POINTER PTR_CONFIG_PAGE_LAN_0,
  LANPage0_t, MPI_POINTER pLANPage0_t;

#define MPI_LAN_PAGE0_PAGEVERSION                       (0x01)

#define MPI_LAN_PAGE0_RETURN_LOOPBACK                   (0x0000)
#define MPI_LAN_PAGE0_SUPPRESS_LOOPBACK                 (0x0001)
#define MPI_LAN_PAGE0_LOOPBACK_MASK                     (0x0001)

typedef struct _CONFIG_PAGE_LAN_1
{
    ConfigPageHeader_t      Header;
    U16                     Reserved;
    U8                      CurrentDeviceState;
    U8                      Reserved1;
    U32                     MinPacketSize;
    U32                     MaxPacketSize;
    U32                     HardwareAddressLow;
    U32                     HardwareAddressHigh;
    U32                     MaxWireSpeedLow;
    U32                     MaxWireSpeedHigh;
    U32                     BucketsRemaining;
    U32                     MaxReplySize;
    U32                     NegWireSpeedHigh;
    U32                     NegWireSpeedLow;
} fCONFIG_PAGE_LAN_1, MPI_POINTER PTR_CONFIG_PAGE_LAN_1,
  LANPage1_t, MPI_POINTER pLANPage1_t;

#define MPI_LAN_PAGE1_PAGEVERSION                       (0x03)

#define MPI_LAN_PAGE1_DEV_STATE_RESET                   (0x00)
#define MPI_LAN_PAGE1_DEV_STATE_OPERATIONAL             (0x01)

#endif

