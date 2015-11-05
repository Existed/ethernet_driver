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






MAC-OBJS += qca953x.o athrs_gmac_ctrl.o athrs_phy_ctrl.o


ifeq ($(ETH_CONFIG),_f1e)
PHY-OBJS += phys/athrf1_phy.o
override ETH_CONFIG2 := _vir
ATH_GMAC_GE1_IS_CONNECTED=1
ATH_GMAC0_RGMII=1
ATH_GMAC1_RGMII=1
endif

ifeq ($(ETH_CONFIG2),_vir)
PHY-OBJS += phys/athrs_vir_phy.o
endif

#ifeq ($(ETH_CONFIG),_s27)
PHY-OBJS += phys/athrs27_phy.o
ATH_GMAC0_RGMII=1
ATH_GMAC1_RGMII=1
#endif 








ifeq ($(ATH_GMAC_HW_QOS),1)
ifneq ($(ETH_CONFIG),_s17)
ifneq ($(ETH_CONFIG2),_s17)
ACCEL-OBJS += athrs_qos.o vlan_igmp.o
endif
endif
endif

enet_config.h:
ifeq ($(GMAC_QCA953x),1)

	@> include/config.h
	@echo "/*" > include/config.h
	@echo " * Automatically generated make config: don't edit" >> include/config.h
	@echo " */" >> include/config.h

ifeq ($(ATH_GMAC_SUPPORT_DUAL_PHY),1)
	@ echo "#define CONFIG_ATHR_SUPPORT_DUAL_PHY 1" >>include/config.h
endif # ATH_GMAC_SUPPORT_DUAL_PHY

ifeq ($(ETH_CONFIG),_vir)
	@echo "#define ATHR_GMAC0_MII_PHY ATHR_VIR_PHY" >>include/config.h
	@echo "#define CONFIG_ATHRS_VIR_PHY 1" >>include/config.h

endif
ifeq ($(ETH_CONFIG2),_vir)
	@echo "#define ATHR_GMAC1_MII_PHY ATHR_VIR_PHY" >>include/config.h
	@echo "#define CONFIG_ATHRS_VIR_PHY 1" >>include/config.h
endif

ifeq ($(ETH_CONFIG),_f1e)
	@echo "#define CONFIG_ATHRF1_PHY 1" >>include/config.h
	@echo "#define ATHR_GMAC0_MII_PHY CONFIG_ATHRF1_PHY" >>include/config.h
endif
ifeq ($(ETH_CONFIG),_f2e)
	@echo "#define CONFIG_ATHRF2_PHY 1" >>include/config.h
endif
ifeq ($(ETH_CONFIG),_vir)
	@echo "#define CONFIG_ATHRS_VIR_PHY 1" >>include/config.h
endif
ifeq ($(ETH_CONFIG),_s27)
	@echo "#define CONFIG_ATHRS27_PHY 1" >>include/config.h
	@echo "#define ATHR_GMAC0_MII_PHY ATHR_S27_PHY" >>include/config.h
	@echo "#define ATHR_GMAC1_MII_PHY ATHR_S27_PHY" >>include/config.h
endif 



ifneq ($(findstring ATHR_RGMII,$(ATH_GMAC0_MII)),)
	@echo "#define ATHR_GMAC0_MII ATHR_RGMII" >> include/config.h
endif
ifneq ($(findstring ATHR_SGMII,$(ATH_GMAC0_MII)),)
	@echo "#define ATHR_GMAC0_MII ATHR_SGMII" >> include/config.h
endif

ifneq ($(findstring ATHR_MII,$(ATH_GMAC0_MII)),)
	@echo "#define ATHR_GMAC0_MII ATHR_MII" >> include/config.h
	@echo "#define GMAC0_MII 1" >> include/config.h
endif

ifneq ($(findstring ATHR_RGMII,$(ATH_GMAC1_MII)),)
	@echo "#define ATHR_GMAC1_MII ATHR_RGMII" >> include/config.h
endif
ifneq ($(findstring ATHR_MII,$(ATH_GMAC1_MII)),)
	@echo "#define ATHR_GMAC1_MII ATHR_MII" >> include/config.h
endif

ifeq ($(ATH_GMAC_GE0_IS_CONNECTED),1)
	@echo "#define ATH_GE0_IS_CONNECTED 1" >> include/config.h
endif
ifeq ($(ATH_GMAC_GE1_IS_CONNECTED),1)
	@echo "#define ATH_GE1_IS_CONNECTED 1" >> include/config.h
endif

ifeq ($(ATH_SWITCH_ONLY_MODE),1)
	@echo "#define CONFIG_ATHR_SWITCH_ONLY_MODE 1" >> include/config.h
endif

ifeq ($(ATH_S17_PHY0_WAN),1)
	@echo "#define CONFIG_ATH_S17_WAN 1" >> include/config.h
endif

ifeq ($(ATH_GMAC_DESC_SRAM),1)
	@echo "#define CONFIG_ATHR_DESC_SRAM 1" >> include/config.h
endif

	@echo "#define CONFIG_ATH_LEN_PER_TX_DS $(ATH_GMAC_LEN_PER_TX_DS)" >> include/config.h
	@echo "#define CONFIG_ATH_NUMBER_TX_PKTS  $(ATH_GMAC0_TX_CNT)" >>include/config.h
	@echo "#define CONFIG_ATH_NUMBER_RX_PKTS   $(ATH_GMAC0_RX_CNT)" >>include/config.h
	@echo "#define CONFIG_ATH_NUMBER_TX_PKTS_1 $(ATH_GMAC1_TX_CNT)" >>include/config.h
	@echo "#define CONFIG_ATH_NUMBER_RX_PKTS_1 $(ATH_GMAC1_RX_CNT)" >>include/config.h
	@echo "#define CONFIG_ATH_MAC_LOCATION $(ATH_GMAC_LOCATION)" >>include/config.h
ifdef ATH_GMAC_TXQUEUELEN
	@echo "#define ATH_GMAC_TXQUEUELEN $$ATH_GMAC_TXQUEUELEN" >> include/config.h
else
	# refer to ether_setup
	@echo "#define ATH_GMAC_TXQUEUELEN 1000" >> include/config.h
endif

ifeq ($(ATH_GMAC0_RXFCTL),1)
	@echo "#define CONFIG_GMAC0_RXFCTL 1" >>include/config.h
endif

ifeq ($(ATH_GMAC0_TXFCTL),1)
	@echo "#define CONFIG_GMAC0_TXFCTL 1" >>include/config.h
endif

ifeq ($(ATH_GMAC1_RXFCTL),1)
	@echo "#define CONFIG_GMAC1_RXFCTL 1" >>include/config.h
endif

ifeq ($(ATH_GMAC1_TXFCTL),1)
	@echo "#define CONFIG_GMAC1_TXFCTL 1" >>include/config.h
endif
ifeq ($(ATH_LINK_INTR),1)
	@echo "#define CONFIG_ATH_LINK_INTR 1" >> include/config.h
endif

ifeq ($(ATH_PHY_SWAP),1)
	@echo "#define CONFIG_ATHR_PHY_SWAP 1" >> include/config.h
endif

ifeq ($(ATH_SWITCH_ONLY_MODE),1)
	@echo "#define CONFIG_ATHR_SWITCH_ONLY_MODE 1" >> include/config.h
endif

ifeq ($(ATH_GPIO_LED),1)
	@echo "#define CONFIG_ATH_GPIO_LED 1" >> include/config.h
endif

ifeq ($(ATH_DMA_CHECK),1)
	@echo "#define CONFIG_ATH_DMA_CHECK 1" >> include/config.h
endif
endif #END QCA953x




ifeq ($(ATH_GMAC_HW_QOS),1)
	@echo "#define CONFIG_ATHRS_QOS 1" >>include/config.h
endif

ifeq ($(ATH_GMAC_RX_TASKLET),1)
	@echo "#define CONFIG_ATHR_RX_TASK 1" >>include/config.h
	@echo "#define CONFIG_ATHR_RX_PKTS_CNT $(ATH_GMAC_RX_PKT_CNT)" >>include/config.h
endif

ifdef ATH_GMAC_TXQUEUELEN
	@echo "#define ATH_GMAC_TXQUEUELEN $$ATH_GMAC_TXQUEUELEN" >> include/config.h
else
	# refer to ether_setup
	@echo "#define ATH_GMAC_TXQUEUELEN 1000" >> include/config.h
endif

ifeq ($(strip ${ATH_CAL_NAND_FLASH}), 1)
	echo "#define ATH_CAL_NAND_FLASH 1"	    >>include/config.h
	echo "#define ATH_CAL_NAND_PARTITION "\"$(strip ${ATH_CAL_NAND_PARTITION})\"	    >>include/config.h
endif

ifeq ($(strip ${ATH_GMAC_RXTIMER}), 1)
	echo "#define CONFIG_GMAC_RXTIMER 1"	    >>include/config.h
	echo "#define CONFIG_GMAC_RXTIMER_FREQ $(ATH_GMAC_RXTIMER_FREQ)"	    >>include/config.h
else
	echo "#define CONFIG_GMAC_RXTIMER 0"	    >>include/config.h
endif

ifeq ($(ETHDEBUG),1)
	@echo "#define ETHDEBUG_ENABLED $(ETHDEBUG)" >>include/config.h
else
	@echo "#define ETHDEBUG_ENABLED 0" >>include/config.h
endif


