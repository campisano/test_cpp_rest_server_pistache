cmake_minimum_required(VERSION 3.2.3)

INCLUDE(ExternalProject)

set(VAR_NAME pistache)
set(VAR_CMAKE_BASE_ARGS -DCMAKE_RULE_MESSAGES=OFF -DCMAKE_INSTALL_MESSAGE=NEVER -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_STANDARD=11)
set(VAR_CMAKE_BASE_ARGS ${VAR_CMAKE_BASE_ARGS} -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install ${CMAKE_CURRENT_BINARY_DIR}/${VAR_NAME}_ext-prefix/src/${VAR_NAME}_ext)

ExternalProject_Add(
    ${VAR_NAME}_ext
    DOWNLOAD_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/download
    DOWNLOAD_NAME           ${VAR_NAME}.zip
    URL                     https://codeload.github.com/oktal/pistache/zip/d6a2ff625d9d488d6d3d8cf0423f8fa21a7eb68d
    URL_HASH                MD5=b90a25a3efae9eba8bfdc156fccd4ac6
    CONFIGURE_COMMAND       ${CMAKE_COMMAND} ${VAR_CMAKE_BASE_ARGS} -DPISTACHE_BUILD_EXAMPLES=false -DPISTACHE_BUILD_TESTS=false -DPISTACHE_BUILD_DOCS=false -DPISTACHE_USE_SSL=true -DPISTACHE_INSTALL=ON
    BUILD_COMMAND           ${CMAKE_COMMAND} --build .
    INSTALL_COMMAND         ${CMAKE_COMMAND} --build . --target install
    )

add_library(${VAR_NAME} STATIC IMPORTED)
set_target_properties(${VAR_NAME} PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/install/lib/libpistache.a)
