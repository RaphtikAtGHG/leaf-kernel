cmake_minimum_required(VERSION 3.15)

set(LEAF_TARGET "Leaf-${TARGET_ARCH}-raw.bin")

file(GLOB_RECURSE CC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

file(GLOB_RECURSE ASM_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.asm"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.s"
)

add_executable(${LEAF_TARGET} ${CC_FILES} ${ASM_FILES})

target_include_directories(${LEAF_TARGET} PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/arch/${TARGET_ARCH}"
)

target_compile_definitions(${LEAF_TARGET} PUBLIC
	${TARGET_DEFINITIONS}
)