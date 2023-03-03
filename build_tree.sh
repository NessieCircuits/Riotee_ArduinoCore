#!/bin/bash

# Clean directory
rm -rf cores/Riotee/external

# Copy external code into core directory
cp -r external/ cores/Riotee/external/

# We want to keep these files
keepers=( \
cores/Riotee/external/Riotee_Runtime/freertos/list.c \
cores/Riotee/external/Riotee_Runtime/freertos/queue.c \
cores/Riotee/external/Riotee_Runtime/freertos/tasks.c \
cores/Riotee/external/Riotee_Runtime/freertos/timers.c \
cores/Riotee/external/Riotee_Runtime/freertos/portable/GCC/ARM_CM4F/port.c \
)

# We want to delete these files
targets=( \
cores/Riotee/external/Riotee_Runtime/src/main.c \
)

# Find all 'external' C source files in the runtime lib
readarray -d '' candidates < <(find cores/Riotee/external/Riotee_Runtime/freertos cores/Riotee/external/Riotee_Runtime/nrfx cores/Riotee/external/Riotee_Runtime/CMSIS_5 cores/Riotee/external/ArduinoCore-API/test -type f \( -name "*.c" -o -name "*.cpp" -o -name "*.S" -o -name "*.asm" \) -print0)


# Build difference between candidates and keepers
declare -A temp
for element in "${candidates[@]}" "${keepers[@]}"
do
    ((temp[$element]++))
done
for element in "${!temp[@]}"
do
    if (( ${temp[$element]} > 1 ))
    then
        unset "temp[$element]"
    fi
done

# These are the files that we want to delete
targets+=(${!temp[@]})

echo "found ${#candidates[@]}"
echo "excluding ${#keepers[@]} files"
echo "deleting ${#targets[@]} files"

for item in "${targets[@]}"
do
	rm -f "$item"
done