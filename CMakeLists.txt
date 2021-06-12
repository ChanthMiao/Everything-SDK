cmake_minimum_required(VERSION 3.13.0)

if(not ${MSVC})
    message(FATAL_ERROR "This project is windows(MSVC) only. CMake will exit.")
endif()

project(Everything-SDK LANGUAGES C)
# target
add_library(Everything-SDK SHARED "")
set_target_properties(Everything-SDK PROPERTIES OUTPUT_NAME "Everything")

target_include_directories(Everything-SDK PUBLIC
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
$<INSTALL_INTERFACE:include>
)
target_compile_options(Everything-SDK PRIVATE
    "/Wall"
    "/wd4668"
    "/wd5045"
    "/sdl"
    "/GS"
    "/D_CRT_SECURE_NO_WARNINGS"
    "/DUNICODE"
    "/utf-8"
    "/EHsc"
    "$<$<CONFIG:Relase>:/MD>"
    "$<$<CONFIG:Debug>:/MDd>"
    "$<$<CONFIG:RelWithDebInfo>:/MDd>"
    "$<$<CONFIG:MinSizeRel>:/Md>"
)

target_link_options(Everything-SDK PRIVATE
    /DEF:${CMAKE_SOURCE_DIR}/src/Everything.def
)
target_sources(Everything-SDK PRIVATE
    src/Everything.c
)

# target
add_executable(test "")
set_target_properties(test PROPERTIES OUTPUT_NAME "test")
add_dependencies(test Everything-SDK)

target_compile_options(test PRIVATE
    "/Wall"
    "/wd4668"
    "/wd5045"
    "/sdl"
    "/GS"
    "/D_CRT_SECURE_NO_WARNINGS"
    "/DUNICODE"
    "/utf-8"
    "/EHsc"
    "$<$<CONFIG:Relase>:/MD>"
    "$<$<CONFIG:Debug>:/MDd>"
    "$<$<CONFIG:RelWithDebInfo>:/MDd>"
    "$<$<CONFIG:MinSizeRel>:/Md>"
)
target_link_libraries(test PRIVATE
    Everything-SDK
)

target_sources(test PRIVATE
    test/main.c
)

install(TARGETS Everything-SDK
    EXPORT everything
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
install(FILES include/Everything.h DESTINATION include)
install(FILES LICENSE DESTINATION share/everything)
install(EXPORT everything DESTINATION share/everything)