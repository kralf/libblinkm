remake_project_header(config.h.remake)

remake_find_file("linux/i2c-dev.h" PACKAGE i2c-dev)
remake_include(. blinkm ${I2C_DEV_PATH})

remake_add_directories()
remake_pkg_config_generate()
