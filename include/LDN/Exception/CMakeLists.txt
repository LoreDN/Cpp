# ===================== Exception/CMakeLists.txt =====================
cmake_minimum_required(VERSION 3.15)
project(LDN_Exception VERSION 1.0.1 LANGUAGES CXX)

set(LIB_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(LIB_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../build")


# ======================== Library Definition ========================
add_library(LDN_Exception INTERFACE)
target_include_directories(LDN_Exception INTERFACE "${LIB_INCLUDE_DIR}")
target_compile_features(LDN_Exception INTERFACE cxx_std_20)


# ======================= Library Installation =======================
install(
    DIRECTORY "${LIB_INCLUDE_DIR}/"
    DESTINATION include/LDN
    PATTERN "CHANGELOG.md" EXCLUDE
    PATTERN "CMakeLists.txt" EXCLUDE
)

install(
    FILES ${LIB_INCLUDE_DIR}/CHANGELOG.md
    DESTINATION share/doc/LDN/Exception
)


# ========================= PACKAGING (CPack) ========================
set(CPACK_PACKAGE_NAME "ldn-exception")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_CONTACT "lorenzo_dinapoli@icloud.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "LDN --- Exception handling library")
set(CPACK_PACKAGE_DESCRIPTION "Exception handling library, used especially with other LDN libraries")
set(CPACK_PACKAGE_VENDOR "Lorenzo Di Napoli")
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_FILE_NAME "ldn-exception-v${PROJECT_VERSION}")

include(CPack)


# ========================== Generate .deb  ==========================
add_custom_target(package_exception
    COMMAND ${CMAKE_COMMAND} -S ${CMAKE_CURRENT_SOURCE_DIR} -B ${LIB_BUILD_DIR} -DCMAKE_INSTALL_PREFIX=/usr
    COMMAND ${CMAKE_COMMAND} --build ${LIB_BUILD_DIR} --target package
    COMMAND /bin/sh -c "cp ${LIB_BUILD_DIR}/*.deb ${LIB_BUILD_DIR}/../deb/Exception || true"
)