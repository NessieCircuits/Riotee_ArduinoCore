#!/bin/bash

# Copy all required files from git submodules into core tree. This keeps the
# core size small and prevents Arduino from trying to compile everything.

copy_paths=(
    ArduinoCore-API/api
    Riotee_Runtime/CMSIS_5/CMSIS/Core/Include
    Riotee_Runtime/nrfx/nrfx.h
    Riotee_Runtime/nrfx/hal
    Riotee_Runtime/nrfx/soc
    Riotee_Runtime/nrfx/templates
    Riotee_Runtime/nrfx/drivers/include
    Riotee_Runtime/nrfx/drivers/nrfx_common.h
    Riotee_Runtime/nrfx/drivers/nrfx_errors.h
    Riotee_Runtime/nrfx/mdk/nrf.h
    Riotee_Runtime/nrfx/mdk/nrf52833.h
    Riotee_Runtime/nrfx/mdk/system_nrf52833.h
    Riotee_Runtime/nrfx/mdk/nrf52833_bitfields.h
    Riotee_Runtime/nrfx/mdk/nrf52_to_nrf52833.h
    Riotee_Runtime/nrfx/mdk/nrf51_to_nrf52.h
    Riotee_Runtime/nrfx/mdk/nrf_peripherals.h
    Riotee_Runtime/nrfx/mdk/nrf52833_peripherals.h
    Riotee_Runtime/nrfx/mdk/compiler_abstraction.h
    Riotee_Runtime/freertos/list.c
    Riotee_Runtime/freertos/queue.c
    Riotee_Runtime/freertos/tasks.c
    Riotee_Runtime/freertos/event_groups.c
    Riotee_Runtime/freertos/portable/GCC/ARM_CM4F
    Riotee_Runtime/freertos/include
    Riotee_Runtime/src
    Riotee_Runtime/include
    Riotee_Runtime/linker.ld
)

# Cleanup
rm -rf cores/Riotee/external/*

# Copy files, creating paths as necessary
for item in "${copy_paths[@]}"
do
	src_path="external/${item}"
	dst_path="cores/Riotee/external/${item}"
    dst_dir="$(dirname -- $dst_path)"
    mkdir -p $dst_dir
    cp -r $src_path $dst_path
done