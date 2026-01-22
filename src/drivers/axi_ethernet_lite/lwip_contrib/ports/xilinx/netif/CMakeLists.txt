# Copyright (C) 2023 - 2024 Advanced Micro Devices, Inc.  All rights reserved.
# SPDX-License-Identifier: MIT
collect (PROJECT_LIB_SOURCES xadapter.c)
collect (PROJECT_LIB_SOURCES xpqueue.c)
collect (PROJECT_LIB_HEADERS xemac_ieee_reg.h)

if (${CONFIG_EMACLITE})
    collect (PROJECT_LIB_SOURCES xemacliteif.c)
endif()
