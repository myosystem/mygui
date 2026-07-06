file(GLOB SRCS *.cpp)

add_executable(mygui ${SRCS})

target_link_libraries(mygui PRIVATE mylibc)

target_link_options(mygui PRIVATE
    -nostdlib
    -T ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
)

set_target_properties(mygui PROPERTIES
    LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld
)

add_custom_command(TARGET mygui POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${BOOT_OUT_DIR}
    COMMAND objcopy -O binary
        --only-section=.text --only-section=.rodata --only-section=.data
        $<TARGET_FILE:mygui>
        ${BOOT_OUT_DIR}/mygui.o
    VERBATIM
)
