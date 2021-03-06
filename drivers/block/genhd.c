/*
 *  Code extracted from
 *  linux/kernel/hd.c
 *
 *  Copyright (C) 1991-1998  Linus Torvalds
 *
 *  devfs support - jj, rgooch, 980122
 *
 *  Moved partition checking code to fs/partitions* - Russell King
 *  (linux@arm.uk.linux.org)
 */

#include <linux/config.h>
#include <linux/fs.h>
#include <linux/genhd.h>
#include <linux/kernel.h>
#include <linux/blk.h>
#include <linux/init.h>

extern int blk_dev_init(void);
#ifdef CONFIG_BLK_DEV_DAC960
extern void DAC960_Initialize(void);
#endif
#ifdef CONFIG_FUSION_BOOT
extern int fusion_init(void);
#endif
extern int net_dev_init(void);
extern void console_map_init(void);
extern int soc_probe(void);
extern int atmdev_init(void);
extern int i2o_init(void);
extern int cpqarray_init(void);

int __init device_init(void)
{
	blk_dev_init();
	sti();
#ifdef CONFIG_I2O
	i2o_init();
#endif
#ifdef CONFIG_BLK_DEV_DAC960
	DAC960_Initialize();
#endif
#ifdef CONFIG_FUSION_BOOT
	fusion_init();
#endif
#ifdef CONFIG_FC4_SOC
	/* This has to be done before scsi_dev_init */
	soc_probe();
#endif
#ifdef CONFIG_BLK_CPQ_DA
	cpqarray_init();
#endif
#ifdef CONFIG_NET
	net_dev_init();
#endif
#ifdef CONFIG_ATM
	(void) atmdev_init();
#endif
#ifdef CONFIG_VT
	console_map_init();
#endif
	return 0;
}

__initcall(device_init);
