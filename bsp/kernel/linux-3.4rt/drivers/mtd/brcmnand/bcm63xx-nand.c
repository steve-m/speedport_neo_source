#if defined(CONFIG_BCM_KF_MTD_BCMNAND)
/*
 *
 *  drivers/mtd/brcmnand/bcm7xxx-nand.c
 *
    <:copyright-BRCM:2011:DUAL/GPL:standard
    
       Copyright (c) 2011 Broadcom Corporation
       All Rights Reserved
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation (the "GPL").
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    
    A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
    writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
    
    :> 


    File: bcm7xxx-nand.c

    Description: 
    This is a device driver for the Broadcom NAND flash for bcm97xxx boards.
when    who what
-----   --- ----
051011  tht codings derived from OneNand generic.c implementation.

 * THIS DRIVER WAS PORTED FROM THE 2.6.18-7.2 KERNEL RELEASE
 */
 
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
#include <asm/io.h>
#include <bcm_map_part.h>
#include <board.h>
#include "brcmnand_priv.h"
#include <linux/slab.h> 
#include <flash_api.h>

#define PRINTK(...)
//#define PRINTK printk

#define DRIVER_NAME     "brcmnand"
#define DRIVER_INFO     "Broadcom NAND controller"
#define SC_NAND_FLASH_SIZE 128

extern bool kerSysIsRootfsSet(void);

static int __devinit brcmnanddrv_probe(struct platform_device *pdev);
static int __devexit brcmnanddrv_remove(struct platform_device *pdev);

static struct mtd_partition bcm63XX_nand_parts[] = 
{
    {name: "cferom",        offset: 0, size: 0},
    {name: "mmap",          offset: 0, size: 0, mask_flags: MTD_WRITEABLE},
    {name: "cferam1",       offset: 0, size: 0},
    {name: "cferam2",       offset: 0, size: 0},
    {name: "serial",        offset: 0, size: 0},
    {name: "protect",       offset: 0, size: 0},
    {name: "kfs1",          offset: 0, size: 0},
    {name: "kfs2",          offset: 0, size: 0},
    {name: "bootflag1",     offset: 0, size: 0},
    {name: "bootflag2",     offset: 0, size: 0},
    {name: "xml_cfg",       offset: 0, size: 0},
    {name: "app_dat",       offset: 0, size: 0},
    {name: NULL,            offset: 0, size: 0}
};

static struct platform_driver brcmnand_platform_driver =
{
    .probe      = brcmnanddrv_probe,
    .remove     = __devexit_p(brcmnanddrv_remove),
    .driver     =
     {
        .name   = DRIVER_NAME,
     },
};

static struct resource brcmnand_resources[] =
{
    [0] = {
            .name   = DRIVER_NAME,
            .start  = BPHYSADDR(BCHP_NAND_REG_START),
            .end    = BPHYSADDR(BCHP_NAND_REG_END) + 3,
            .flags  = IORESOURCE_MEM,
          },
};

static struct brcmnand_info
{
    struct mtd_info mtd;
    struct brcmnand_chip brcmnand;
    int nr_parts;
    struct mtd_partition* parts;
} *gNandInfo[NUM_NAND_CS];

int gNandCS[NAND_MAX_CS];
/* Number of NAND chips, only applicable to v1.0+ NAND controller */
int gNumNand = 0;
int gClearBBT = 0;
char gClearCET = 0;
uint32_t gNandTiming1[NAND_MAX_CS], gNandTiming2[NAND_MAX_CS];
uint32_t gAccControl[NAND_MAX_CS], gNandConfig[NAND_MAX_CS];

static unsigned long t1[NAND_MAX_CS] = {0};
static int nt1 = 0;
static unsigned long t2[NAND_MAX_CS] = {0};
static int nt2 = 0;
static unsigned long acc[NAND_MAX_CS] = {0};
static int nacc = 0;
static unsigned long nandcfg[NAND_MAX_CS] = {0};
static int ncfg = 0;
static void* gPageBuffer = NULL;

#ifdef _SC_BUILD_

struct _sc_mmap_info {
    __u32   idx; /* start from 0 */
    __u32   oft;
    __u32   size;
};
#define SC_MMAP(x) ((struct _sc_mmap_info *)(x))

enum {
    SC_MMAP_CFEROM,
    SC_MMAP_MMAP,
    SC_MMAP_CFERAM1,
    SC_MMAP_CFERAM2,
    SC_MMAP_SN,
    SC_MMAP_PROTECT,
    SC_MMAP_KFS1,
    SC_MMAP_KFS2,
    SC_MMAP_BOOTFLAG1,
    SC_MMAP_BOOTFLAG2,
    SC_MMAP_CONFIG,
    SC_MMAP_APPDATA,
    SC_MMAP_NR
};

#if SC_NAND_FLASH_SIZE == 128

#define FLASH_BLOCK_SIZE    (128 * 1024)
#define FLASH_PAGE_SIZE     (2048)

#elif SC_NAND_FLASH_SIZE == 64

#define FLASH_BLOCK_SIZE    (16 * 1024)
#define FLASH_PAGE_SIZE     (512)

#else

#error "SC_NAND_FLASH_SIZE not defined!!!!"

#endif

static void __devinit
sc_set_running_rootfs(struct brcmnand_info *nandinfo, struct _sc_mmap_info *mmap)
{
        struct mtd_info *mtd = &nandinfo->mtd;
        size_t retlen;
        loff_t oft = 0x0;
        __u8 bf1[16] = {0};
        __u8 bf2[16] = {0};

        printk("=====> %s\n", __FUNCTION__);

        /*
         * Read bootflag1
         */
        oft = mmap[SC_MMAP_BOOTFLAG1].oft;
        while(mtd->_block_isbad(mtd, oft)) {
                printk("!!! oft = 0x%llx is in bad block.\n", oft);
                oft += FLASH_BLOCK_SIZE;
                /*
                 * TODO
                 * check out of boundary
                 */
        }

        if(mtd->_read(mtd, oft, sizeof(bf1), &retlen, bf1) < 0) {
                printk("%s read mtd failed, oft = 0x%llx\n",
                       __FUNCTION__, oft);
                return;
        }

        printk("bootflags 1 = %s", bf1);

        /*
         * Read bootflag2
         */
        oft = mmap[SC_MMAP_BOOTFLAG2].oft;
        while(mtd->_block_isbad(mtd, oft)) {
                printk("!!! oft = 0x%llx is in bad block.\n", oft);
                oft += FLASH_BLOCK_SIZE;
                /*
                 * TODO
                 * check out of boundary
                 */
        }

        if(mtd->_read(mtd, oft, sizeof(bf2), &retlen, bf2) < 0) {
                printk("%s read mtd failed, oft = 0x%llx\n",
                       __FUNCTION__, oft);
                return;
        }

        printk("bootflags 2 = %s", bf2);

        if(memcmp(bf1, bf2, sizeof(bf1)) < 0) {
                printk("set booting from kfs 2\n");
                bcm63XX_nand_parts[SC_MMAP_KFS1].name = "rootfs_inactive";
                bcm63XX_nand_parts[SC_MMAP_KFS2].name = "rootfs";
        } else {
                printk("set booting from kfs 1\n");
                bcm63XX_nand_parts[SC_MMAP_KFS1].name = "rootfs";
                bcm63XX_nand_parts[SC_MMAP_KFS2].name = "rootfs_inactive";
        }

        printk("<===== %s\n", __FUNCTION__);

        return;
}

static void __devinit
sc_setup_mtd_partitions(struct brcmnand_info *nandinfo)
{
        struct mtd_info *mtd = &nandinfo->mtd;
        size_t retlen;
        static __u8 buf[FLASH_PAGE_SIZE];
        __u8 mmap_flag_found = 0;
        loff_t oft = FLASH_BLOCK_SIZE; /* search from 2nd block */
        int i = 0;

        printk("==> %s\n", __FUNCTION__);

        while(1) {

                while(mtd->_block_isbad(mtd, oft)) {
                        printk("!!! oft = 0x%llx is in bad block.\n", oft);
                        oft += FLASH_BLOCK_SIZE;
                        if(unlikely(oft >= mtd->size)) {
                                printk("%s read beyond device size = %llu\n",
                                       __FUNCTION__, mtd->size);
                                return;
                        }
                }

                printk("[%s] try read a page at offset = 0x%llx\n", __FUNCTION__, oft);

                if(mtd->_read(mtd, oft, sizeof(buf), &retlen, buf) < 0) {
                        printk("%s read mtd failed, oft = 0x%llx\n",
                               __FUNCTION__, oft);
                        return;
                }

                printk("[%s] read page OK at offset = 0x%llx\n", __FUNCTION__, oft);

                if(!mmap_flag_found) {
                        if(memcmp(&buf, "SCFLMAPOK", 9) == 0) {
                                mmap_flag_found = 1;
                                printk("mmap flag found on oft = 0x%llx\n", oft);
                                oft += FLASH_PAGE_SIZE; /* data saved in next page */
                                continue;
                        }
                        /*
                         * Magic not there, read next block.
                         */
                        oft += FLASH_BLOCK_SIZE;
                } else {
                        break;
                }
        }

        nandinfo->nr_parts = SC_MMAP_NR;
        for(i = 0; i < nandinfo->nr_parts; ++i) {
                bcm63XX_nand_parts[i].offset     = SC_MMAP(buf)[i].oft;
                bcm63XX_nand_parts[i].size       = SC_MMAP(buf)[i].size;
                bcm63XX_nand_parts[i].ecclayout  = mtd->ecclayout;
        }

        sc_set_running_rootfs(nandinfo, SC_MMAP(buf));

        printk("<== %s\n", __FUNCTION__);

        return;
}
#endif

#ifndef _SC_BUILD_
static int __devinit 
is_split_partition (struct mtd_info* mtd, unsigned long offset, unsigned long size, unsigned long *split_offset)
{
    uint8_t buf[0x100];
    size_t retlen;
    int split_found = 0;

    /* Search RootFS partion for split marker.
     * Marker is located in the last 0x100 bytes of the last BootFS Erase Block
     * If marker is found, we have separate Boot and Root Partitions.
     */
    for (*split_offset = offset + mtd->erasesize; *split_offset <= offset + size; *split_offset += mtd->erasesize)
    {
        if (mtd->_block_isbad(mtd, *split_offset - mtd->erasesize)) {
            continue;
        }
        mtd->_read(mtd, *split_offset - 0x100, 0x100, &retlen, buf);

        if (!strncmp (BCM_BCMFS_TAG, buf, strlen (BCM_BCMFS_TAG))) {
            if (!strncmp (BCM_BCMFS_TYPE_UBIFS, &buf[strlen (BCM_BCMFS_TAG)], strlen (BCM_BCMFS_TYPE_UBIFS)))
            {
                printk("***** Found UBIFS Marker at 0x%08lx\n", *split_offset - 0x100); 
                split_found = 1;
                break;
            }
        }
    }

    return split_found;
}
#endif

static void __devinit 
brcmnanddrv_setup_mtd_partitions(struct brcmnand_info* nandinfo)
{
    int boot_from_nand;

    if (flash_get_flash_type() == FLASH_IFC_NAND)
        boot_from_nand = 1;
    else
        boot_from_nand = 0;

    if( boot_from_nand == 0 )
    {
        nandinfo->nr_parts = 1;
        nandinfo->parts = bcm63XX_nand_parts;

        bcm63XX_nand_parts[0].name = "data";
        bcm63XX_nand_parts[0].offset = 0;
        if( device_size(&(nandinfo->mtd)) < NAND_BBT_THRESHOLD_KB )
        {
            bcm63XX_nand_parts[0].size =
                device_size(&(nandinfo->mtd)) - (NAND_BBT_SMALL_SIZE_KB*1024);
        }
        else
        {
            bcm63XX_nand_parts[0].size =
                device_size(&(nandinfo->mtd)) - (NAND_BBT_BIG_SIZE_KB*1024);
        }
        bcm63XX_nand_parts[0].ecclayout = nandinfo->mtd.ecclayout;

        PRINTK("Part[0] name=%s, size=%llx, ofs=%llx\n", bcm63XX_nand_parts[0].name,
            bcm63XX_nand_parts[0].size, bcm63XX_nand_parts[0].offset);
    }
    else
    {
        static NVRAM_DATA nvram;
        //struct mtd_info* mtd = &nandinfo->mtd;
        unsigned long rootfs_ofs;
        int rootfs, rootfs_update;
        //unsigned long  split_offset;

        kerSysBlParmsGetInt(NAND_RFS_OFS_NAME, (int *) &rootfs_ofs);
        kerSysNvRamGet((char *)&nvram, sizeof(nvram), 0);
        nandinfo->nr_parts = 4;
        nandinfo->parts = bcm63XX_nand_parts;

        /* Root FS.  The CFE RAM boot loader saved the rootfs offset that the
         * Linux image was loaded from.
         */
#if 0
        PRINTK("rootfs_ofs=0x%8.8lx, part1ofs=0x%8.8lx, part2ofs=0x%8.8lx\n",
	       rootfs_ofs, (unsigned long)nvram.ulNandPartOfsKb[NP_ROOTFS_1],
	       (unsigned long)nvram.ulNandPartOfsKb[NP_ROOTFS_2]);
        if( rootfs_ofs == nvram.ulNandPartOfsKb[NP_ROOTFS_1] )
        {
            rootfs = NP_ROOTFS_1;
            rootfs_update = NP_ROOTFS_2;
        }
        else
        {
            if( rootfs_ofs == nvram.ulNandPartOfsKb[NP_ROOTFS_2] )
            {
                rootfs = NP_ROOTFS_2;
                rootfs_update = NP_ROOTFS_1;
            }
            else
            {
                /* Backward compatibility with old cferam. */
                extern unsigned char _text;
                unsigned long rootfs_ofs = *(unsigned long *) (&_text - 4);

                if( rootfs_ofs == nvram.ulNandPartOfsKb[NP_ROOTFS_1] )
                {
                    rootfs = NP_ROOTFS_1;
                    rootfs_update = NP_ROOTFS_2;
                }
                else
                {
                    rootfs = NP_ROOTFS_2;
                    rootfs_update = NP_ROOTFS_1;
                }
            }
        }
#else
        rootfs = NP_ROOTFS_2;
        rootfs_update = NP_ROOTFS_1;//cferam

#endif

#ifndef _SC_BUILD_
        /* RootFS partition */
        bcm63XX_nand_parts[0].offset = nvram.ulNandPartOfsKb[rootfs]*1024;
        bcm63XX_nand_parts[0].size = nvram.ulNandPartSizeKb[rootfs]*1024;
        bcm63XX_nand_parts[0].ecclayout = mtd->ecclayout;

        /* This partition is used for flashing images */
        bcm63XX_nand_parts[4].offset = bcm63XX_nand_parts[0].offset;
        bcm63XX_nand_parts[4].size = bcm63XX_nand_parts[0].size;
        bcm63XX_nand_parts[4].ecclayout = mtd->ecclayout;

        if (is_split_partition (mtd, bcm63XX_nand_parts[0].offset, bcm63XX_nand_parts[0].size, &split_offset))
        {
            /* RootFS partition */
            bcm63XX_nand_parts[0].offset = split_offset;
            bcm63XX_nand_parts[0].size -= (split_offset - nvram.ulNandPartOfsKb[rootfs]*1024);

            /* BootFS partition */
            bcm63XX_nand_parts[nandinfo->nr_parts].name = "bootfs";
            bcm63XX_nand_parts[nandinfo->nr_parts].offset = nvram.ulNandPartOfsKb[rootfs]*1024;
            bcm63XX_nand_parts[nandinfo->nr_parts].size = split_offset - nvram.ulNandPartOfsKb[rootfs]*1024;
            bcm63XX_nand_parts[nandinfo->nr_parts].ecclayout = mtd->ecclayout;
            nandinfo->nr_parts++;

            if (kerSysIsRootfsSet() == false) {
                kerSysSetBootParm("ubi.mtd", "0");
                kerSysSetBootParm("root=", "ubi:rootfs_ubifs");
                kerSysSetBootParm("rootfstype=", "ubifs");
            }
        }
        else {
            if (kerSysIsRootfsSet() == false) {
                kerSysSetBootParm("root=", "mtd:rootfs");
                kerSysSetBootParm("rootfstype=", "jffs2");
            }
        }

        /* RootFS_update partition */
        bcm63XX_nand_parts[1].offset = nvram.ulNandPartOfsKb[rootfs_update]*1024;
        bcm63XX_nand_parts[1].size = nvram.ulNandPartSizeKb[rootfs_update]*1024;
        bcm63XX_nand_parts[1].ecclayout = mtd->ecclayout;

        /* This partition is used for flashing images */
        bcm63XX_nand_parts[5].offset = bcm63XX_nand_parts[1].offset;
        bcm63XX_nand_parts[5].size = bcm63XX_nand_parts[1].size;
        bcm63XX_nand_parts[5].ecclayout = mtd->ecclayout;

        if (is_split_partition (mtd, bcm63XX_nand_parts[1].offset, bcm63XX_nand_parts[1].size, &split_offset))
        {
            /* rootfs_update partition */
            bcm63XX_nand_parts[1].offset = split_offset;
            bcm63XX_nand_parts[1].size -= (split_offset - nvram.ulNandPartOfsKb[rootfs_update]*1024);

            /* bootfs_update partition */
            bcm63XX_nand_parts[nandinfo->nr_parts].name = "bootfs_update";
            bcm63XX_nand_parts[nandinfo->nr_parts].offset = nvram.ulNandPartOfsKb[rootfs_update]*1024;
            bcm63XX_nand_parts[nandinfo->nr_parts].size = split_offset - nvram.ulNandPartOfsKb[rootfs_update]*1024;
            bcm63XX_nand_parts[nandinfo->nr_parts].ecclayout = mtd->ecclayout;
            nandinfo->nr_parts++;
        }

        /* Data (psi, scratch pad) */
        bcm63XX_nand_parts[2].offset = nvram.ulNandPartOfsKb[NP_DATA] * 1024;
        bcm63XX_nand_parts[2].size = nvram.ulNandPartSizeKb[NP_DATA] * 1024;
        bcm63XX_nand_parts[2].ecclayout = mtd->ecclayout;

        /* Boot and NVRAM data */
        bcm63XX_nand_parts[3].offset = nvram.ulNandPartOfsKb[NP_BOOT] * 1024;
        bcm63XX_nand_parts[3].size = nvram.ulNandPartSizeKb[NP_BOOT] * 1024;
        bcm63XX_nand_parts[3].ecclayout = mtd->ecclayout;
#else

        sc_setup_mtd_partitions(nandinfo);

#if 0
#define BOOTLOADER_OFFSET           0x0000000
#define BOOTLOADER_SIZE             0x0004000   //16K, ROM only
#define ROOTFS_OFFSET               0x0080000   //512K
#define ROOTFS_SIZE                 0x1ac0000
#define NVRAM_OFFSET                0x1b00000
#define NVRAM_SIZE                  0x02b0000   // 2M
        
        /*
         * Rootfs + Kernel
         */
        nandinfo->nr_parts = 3;
        bcm63XX_nand_parts[0].offset = ROOTFS_OFFSET;
        bcm63XX_nand_parts[0].size = ROOTFS_SIZE ;
        bcm63XX_nand_parts[0].ecclayout = mtd->ecclayout;

        /* Bootloader */
        bcm63XX_nand_parts[1].offset = BOOTLOADER_OFFSET;
        bcm63XX_nand_parts[1].size = BOOTLOADER_SIZE;
        bcm63XX_nand_parts[1].ecclayout = mtd->ecclayout;
        
        /* Configuration */
        bcm63XX_nand_parts[2].offset = NVRAM_OFFSET;
        bcm63XX_nand_parts[2].size = NVRAM_SIZE;
        bcm63XX_nand_parts[2].ecclayout = mtd->ecclayout;
#endif

#endif
#if 0
        PRINTK("Part[0] name=%s, size=%llx, ofs=%llx\n", bcm63XX_nand_parts[0].name,
            bcm63XX_nand_parts[0].size, bcm63XX_nand_parts[0].offset);
        PRINTK("Part[1] name=%s, size=%llx, ofs=%llx\n", bcm63XX_nand_parts[1].name,
            bcm63XX_nand_parts[1].size, bcm63XX_nand_parts[1].offset);
        PRINTK("Part[2] name=%s, size=%llx, ofs=%llx\n", bcm63XX_nand_parts[2].name,
            bcm63XX_nand_parts[2].size, bcm63XX_nand_parts[2].offset);
        PRINTK("Part[3] name=%s, size=%llx, ofs=%llx\n", bcm63XX_nand_parts[3].name,
            bcm63XX_nand_parts[3].size, bcm63XX_nand_parts[3].offset);
#ifdef _SC_BUILD_
        PRINTK("Part[4] name=%s, size=%x, ofs=%x\n", bcm63XX_nand_parts[4].name,
            bcm63XX_nand_parts[4].size, bcm63XX_nand_parts[4].offset);
        PRINTK("Part[5] name=%s, size=%x, ofs=%x\n", bcm63XX_nand_parts[5].name,
            bcm63XX_nand_parts[5].size, bcm63XX_nand_parts[5].offset);
        PRINTK("Part[6] name=%s, size=%x, ofs=%x\n", bcm63XX_nand_parts[6].name,
            bcm63XX_nand_parts[6].size, bcm63XX_nand_parts[6].offset);

#endif
#endif
    }
}


static int __devinit brcmnanddrv_probe(struct platform_device *pdev)
{
    static int csi = 0; // Index into dev/nandInfo array
    int cs = 0;  // Chip Select
    int err = 0;
    struct brcmnand_info* info = NULL;
    static struct brcmnand_ctrl* ctrl = (struct brcmnand_ctrl*) 0;

    if(!gPageBuffer &&
       (gPageBuffer = kmalloc(sizeof(struct nand_buffers),GFP_KERNEL)) == NULL)
    {
        err = -ENOMEM;
    }
    else
    {
        if( (ctrl = kmalloc(sizeof(struct brcmnand_ctrl), GFP_KERNEL)) != NULL)
        {
            memset(ctrl, 0, sizeof(struct brcmnand_ctrl));
            ctrl->state = FL_READY;
            init_waitqueue_head(&ctrl->wq);
            spin_lock_init(&ctrl->chip_lock);

            if((info=kmalloc(sizeof(struct brcmnand_info),GFP_KERNEL)) != NULL)
            {
                gNandInfo[csi] = info;
                memset(info, 0, sizeof(struct brcmnand_info));
                info->brcmnand.ctrl = ctrl;
                info->brcmnand.ctrl->numchips = gNumNand = 1;
                info->brcmnand.csi = csi;

                /* For now all devices share the same buffer */
                info->brcmnand.ctrl->buffers =
                    (struct nand_buffers*) gPageBuffer;

                info->brcmnand.ctrl->numchips = gNumNand; 
                info->brcmnand.chip_shift = 0; // Only 1 chip
                info->brcmnand.priv = &info->mtd;
                info->mtd.name = dev_name(&pdev->dev);
                info->mtd.priv = &info->brcmnand;
                info->mtd.owner = THIS_MODULE;

                /* Enable the following for a flash based bad block table */
                info->brcmnand.options |= NAND_SKIP_BBTSCAN;

                /* Each chip now will have its own BBT (per mtd handle) */
                if (brcmnand_scan(&info->mtd, cs, gNumNand) == 0)
                {
                    PRINTK("Master size=%08llx\n", info->mtd.size); 
                    brcmnanddrv_setup_mtd_partitions(info);
                    mtd_device_register(&info->mtd, info->parts, info->nr_parts);
                    dev_set_drvdata(&pdev->dev, info);
                }
                else
                    err = -ENXIO;

            }
            else
                err = -ENOMEM;

        }
        else
            err = -ENOMEM;
    }

    if( err )
    {
        if( gPageBuffer )
        {
            kfree(gPageBuffer);
            gPageBuffer = NULL;
        }

        if( ctrl )
        {
            kfree(ctrl);
            ctrl = NULL;
        }

        if( info )
        {
            kfree(info);
            info = NULL;
        }
    }

    return( err );
}

static int __devexit brcmnanddrv_remove(struct platform_device *pdev)
{
    struct brcmnand_info *info = dev_get_drvdata(&pdev->dev);

    dev_set_drvdata(&pdev->dev, NULL);

    if (info)
    {
        mtd_device_unregister(&info->mtd);

        brcmnand_release(&info->mtd);
        kfree(gPageBuffer);
        kfree(info);
    }

    return 0;
}

static int __init brcmnanddrv_init(void)
{
    int ret = 0;
    int csi;
    int ncsi;
    char cmd[32] = "\0";
    struct platform_device *pdev;

    if (flash_get_flash_type() != FLASH_IFC_NAND)
        return -ENODEV;

    kerSysBlParmsGetStr(NAND_COMMAND_NAME, cmd, sizeof(cmd));
    PRINTK("%s: brcmnanddrv_init - NANDCMD='%s'\n", __FUNCTION__, cmd);

    if (cmd[0])
    {
        if (strcmp(cmd, "rescan") == 0)
            gClearBBT = 1;
        else if (strcmp(cmd, "showbbt") == 0)
            gClearBBT = 2;
        else if (strcmp(cmd, "eraseall") == 0)
            gClearBBT = 8;
        else if (strcmp(cmd, "erase") == 0)
            gClearBBT = 7;
        else if (strcmp(cmd, "clearbbt") == 0)
            gClearBBT = 9;
        else if (strcmp(cmd, "showcet") == 0)
            gClearCET = 1;
        else if (strcmp(cmd, "resetcet") == 0)
            gClearCET = 2;
        else if (strcmp(cmd, "disablecet") == 0)
            gClearCET = 3;
        else
            printk(KERN_WARNING "%s: unknown command '%s'\n",
                __FUNCTION__, cmd);
    }
    
    for (csi=0; csi<NAND_MAX_CS; csi++)
    {
        gNandTiming1[csi] = 0;
        gNandTiming2[csi] = 0;
        gAccControl[csi] = 0;
        gNandConfig[csi] = 0;
    }

    if (nacc == 1)
        PRINTK("%s: nacc=%d, gAccControl[0]=%08lx, gNandConfig[0]=%08lx\n", \
            __FUNCTION__, nacc, acc[0], nandcfg[0]);

    if (nacc>1)
        PRINTK("%s: nacc=%d, gAccControl[1]=%08lx, gNandConfig[1]=%08lx\n", \
            __FUNCTION__, nacc, acc[1], nandcfg[1]);

    for (csi=0; csi<nacc; csi++)
        gAccControl[csi] = acc[csi];

    for (csi=0; csi<ncfg; csi++)
        gNandConfig[csi] = nandcfg[csi];

    ncsi = max(nt1, nt2);
    for (csi=0; csi<ncsi; csi++)
    {
        if (nt1 && csi < nt1)
            gNandTiming1[csi] = t1[csi];

        if (nt2 && csi < nt2)
            gNandTiming2[csi] = t2[csi];
        
    }

    printk (KERN_INFO DRIVER_INFO " (BrcmNand Controller)\n");
    if( (pdev = platform_device_alloc(DRIVER_NAME, 0)) != NULL )
    {
        platform_device_add(pdev);
        platform_device_put(pdev);
        ret = platform_driver_register(&brcmnand_platform_driver);
        if (ret >= 0)
            request_resource(&iomem_resource, &brcmnand_resources[0]);
        else
            printk("brcmnanddrv_init: driver_register failed, err=%d\n", ret);
    }
    else
        ret = -ENODEV;

    return ret;
}

static void __exit brcmnanddrv_exit(void)
{
    release_resource(&brcmnand_resources[0]);
    platform_driver_unregister(&brcmnand_platform_driver);
}


module_init(brcmnanddrv_init);
module_exit(brcmnanddrv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ton Truong <ttruong@broadcom.com>");
MODULE_DESCRIPTION("Broadcom NAND flash driver");

#endif //CONFIG_BCM_KF_MTD_BCMNAND
