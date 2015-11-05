#
# Copyright (c) 2013 Qualcomm Atheros, Inc.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
# 
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#

# Makefile for Ar7240 gigabit MAC and Phys
#

export KERNELPATH=/home/leon/devel/qsdk/build_dir/linux-ar71xx_generic/linux-3.3.8
#export ENETDIR=$(KERNELPATH)/drivers/net/ethernet/qca-ethernet
export ENETDIR=$(KERNELPATH)/drivers/net/ethernet/atheros/ag71xx
export GMAC_QCA953x=1

include ${ENETDIR}/Makefile.inc 

#
# Makefile for the Atheros AR71xx built-in ethernet macs
#

#ag71xx-y       += ag71xx_main.o
#ag71xx-y       += ag71xx_ethtool.o
#ag71xx-y       += ag71xx_phy.o
#ag71xx-y       += ag71xx_mdio.o
#ag71xx-y       += ag71xx_ar7240.o

#ag71xx-$(CONFIG_AG71XX_DEBUG_FS)       += ag71xx_debugfs.o
#ag71xx-$(CONFIG_AG71XX_AR8216_SUPPORT) += ag71xx_ar8216.o

#obj-$(CONFIG_AG71XX)   += ag71xx.o


#ifeq ($(GMAC_QCA953x),1)
#obj-m						:= athrs_gmac.o 
obj-$(CONFIG_AG71XX)	+= athrs_gmac.o 
ifeq ($(HYBRID_VLAN_IGMP), 1)
PHY-OBJS	+= athrs_qos.o
PHY-OBJS	+= vlan_igmp.o
endif

athrs_gmac-objs					:= qca_soc_mac.o $(ACCEL-OBJS) $(PHY-OBJS) $(MAC-OBJS) athrs_mac_timer.o athrs_flowmac.o


#else

#endif
#endif 


EXTRA_CFLAGS += -I$(ENETDIR)/include -I$(ENETDIR)/include/phys -I$(KERNELPATH)/arch/mips/include

ifdef FLOWMACDIR
EXTRA_CFLAGS+= -I ${FLOWMACDIR}
endif

ifndef NO_PUSH_BUTTON
export NO_PUSH_BUTTON=1
endif

ifeq ($(strip ${NO_PUSH_BUTTON}), 1)
EXTRA_CFLAGS+= -DNO_PUSH_BUTTON=1
else
EXTRA_CFLAGS+= -DNO_PUSH_BUTTON=0
endif


ifeq ($(strip ${AP136_BOOTROM_TGT}), 1)
EXTRA_CFLAGS+= -DAP136_BOOTROM_TGT
else
EXTRA_CFLAGS+= -UAP136_BOOTROM_TGT
endif

ifeq ($(strip ${AP136_BOOTROM_HOST}), 1)
EXTRA_CFLAGS+= -DAP136_BOOTROM_HOST
else
EXTRA_CFLAGS+= -UAP136_BOOTROM_HOST
endif

ifeq ($(strip ${HYBRID_VLAN_COMMUNICATE}), 1)
EXTRA_CFLAGS+= -DHYBRID_VLAN_COMMUNICATE=1
else
EXTRA_CFLAGS+= -DHYBRID_VLAN_COMMUNICATE=0
endif

ifeq ($(strip ${HYBRID_PATH_SWITCH}), 1)
EXTRA_CFLAGS+= -DATH_HY_PATH_SWITCH
endif

ifeq ($(strip ${HYBRID_PLC_FILTER}), 1)
EXTRA_CFLAGS+= -DHYBRID_PLC_FILTER
endif

ifeq ($(strip ${HYBRID_LINK_CHANGE_EVENT}), 1)
EXTRA_CFLAGS+= -DHYBRID_LINK_CHANGE_EVENT=1
else
EXTRA_CFLAGS+= -DHYBRID_LINK_CHANGE_EVENT=0
endif

ifeq ($(strip ${HYBRID_SWITCH_PORT6_USED}), 1)
EXTRA_CFLAGS+= -DHYBRID_SWITCH_PORT6_USED=1
else
EXTRA_CFLAGS+= -DHYBRID_SWITCH_PORT6_USED=0
endif

ifeq ($(strip ${HYBRID_APH126_128_S17_WAR}), 1)
EXTRA_CFLAGS+= -DHYBRID_APH126_128_S17_WAR=1
else
EXTRA_CFLAGS+= -DHYBRID_APH126_128_S17_WAR=0
endif

ifneq ($(strip ${ATHR_PORT1_LED_GPIO}), )
EXTRA_CFLAGS+= -DATHR_PORT1_LED_GPIO=${ATHR_PORT1_LED_GPIO}
endif

ifdef STAGING_DIR
ifneq ($(strip $(ATH_HEADER)),)
EXTRA_CFLAGS+= -DCONFIG_ATHEROS_HEADER_EN=1
endif
ifneq ($(strip $(CONFIG_AR7240_S26_VLAN_IGMP)),)
EXTRA_CFLAGS+= -DCONFIG_AR7240_S26_VLAN_IGMP=1
ifneq ($(strip $(CONFIG_QCAGMAC_ATH_SNOOPING_V6)),)
EXTRA_CFLAGS+= -DCONFIG_IPV6=1
endif
endif
ifneq ($(strip $(CONFIG_AR7240_S27_VLAN_IGMP)),)
EXTRA_CFLAGS+= -DCONFIG_AR7240_S27_VLAN_IGMP=1
ifneq ($(strip $(CONFIG_QCAGMAC_ATH_SNOOPING_V6)),)
EXTRA_CFLAGS+= -DCONFIG_IPV6=1
endif
endif
ifneq ($(strip $(CONFIG_AR7240_S17_VLAN_IGMP)),)
EXTRA_CFLAGS+= -DCONFIG_AR7240_S17_VLAN_IGMP=1
ifneq ($(strip $(CONFIG_QCAGMAC_ATH_SNOOPING_V6)),)
EXTRA_CFLAGS+= -DCONFIG_IPV6=1
endif
endif
endif

clean:
	rm -f *.o *.ko 
	rm -f phys/*.o *.ko
ifneq ($(ACCEL-OBJS),)
	rm -f hwaccels/*.o
endif


