set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)
set(CMAKE_ASM_COMPILER_WORKS TRUE)
set(CMAKE_C_COMPILER   x86_64-elf-gcc)
set(CMAKE_CXX_COMPILER x86_64-elf-g++)
set(CMAKE_LINKER  x86_64-elf-ld)
set(CMAKE_ASM_NASM_COMPILER nasm)

if(CMAKE_ASM_NASM_COMPILER)
    set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf64")
else()
    message(FATAL_ERROR "NASM not found!") 
endif()

message(">>> Setting flags")
set(COMMON_FLAGS "-g -ffreestanding -Wno-packed-bitfield-compat -fno-stack-protector -fno-stack-check -fno-omit-frame-pointer -fno-lto -fPIE -m64 -march=x86-64 -mabi=sysv -mno-80387 -mno-mmx -msse -msse2 -mno-red-zone -MP")

set(CMAKE_C_FLAGS "${COMMON_FLAGS} -std=gnu11")
set(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=gnu++11")

set(CMAKE_EXE_LINKER_FLAGS "-nostdlib -static -z max-page-size=0x1000 -T ${CMAKE_SOURCE_DIR}/arch/${TARGET_ARCH}/linker.ld")

message(">>> Setting target definitions")
set(TARGET_DEFINITIONS
    LEAF_LIMINE
    LEAF_X64
)
