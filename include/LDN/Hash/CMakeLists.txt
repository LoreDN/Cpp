# ======================== Hash/CMakeLists.txt =======================
cmake_minimum_required(VERSION 3.15)
project(LDN_Hash VERSION 1.0.1 LANGUAGES CXX)

set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../src")
set(LIB_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../build")


# ======================== Library Definition ========================
add_library(LDN_Hash INTERFACE)
target_include_directories(LDN_Hash INTERFACE "${LIB_INCLUDE_DIR}")
target_compile_features(LDN_Hash INTERFACE cxx_std_20)

add_library(LDN_Hash_ETI SHARED "${SRC_DIR}/HashSet_inst.cpp")
target_link_libraries(LDN_Hash_ETI PUBLIC LDN_Hash)
target_compile_features(LDN_Hash_ETI PUBLIC cxx_std_20)
set_target_properties(
    LDN_Hash_ETI PROPERTIES
    OUTPUT_NAME "LDN_Hash"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../../../lib"
)

# ======================= Library Installation =======================
install(
    DIRECTORY "${LIB_INCLUDE_DIR}/"
    DESTINATION include/LDN
    PATTERN "CHANGELOG.md" EXCLUDE
    PATTERN "CMakeLists.txt" EXCLUDE
)
    
install(
    TARGETS LDN_Hash_ETI
    LIBRARY DESTINATION lib/LDN
)

install(
    FILES ${LIB_INCLUDE_DIR}/CHANGELOG.md
    DESTINATION share/doc/LDN/Hash
)


# ========================= PACKAGING (CPack) ========================
set(CPACK_PACKAGE_NAME "ldn-hash")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "lorenzo_dinapoli@icloud.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "LDN --- Hash-Structure library")
set(CPACK_PACKAGE_DESCRIPTION "Hash-Structure library, implements different types of Hash-Structures")
set(CPACK_PACKAGE_VENDOR "Lorenzo Di Napoli")
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_FILE_NAME "ldn-hash-v${PROJECT_VERSION}")

include(CPack)


# ========================== Generate .deb  ==========================
add_custom_target(package_hash
    COMMAND ${CMAKE_COMMAND} -S ${CMAKE_CURRENT_SOURCE_DIR} -B ${LIB_BUILD_DIR} -DCMAKE_INSTALL_PREFIX=/usr
    COMMAND ${CMAKE_COMMAND} --build ${LIB_BUILD_DIR} --target package
    COMMAND /bin/sh -c "cp ${LIB_BUILD_DIR}/*.deb ${LIB_BUILD_DIR}/../deb/Hash || true"
)