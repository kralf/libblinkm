remake_find_file("linux/i2c-dev.h" PACKAGE i2c-dev)
remake_include(${I2C_DEV_PATH})

remake_add_library(i2c LINK base)
remake_add_headers(INSTALL i2c)
