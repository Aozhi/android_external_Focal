# general information
SET(CPACK_PACKAGE_VENDOR "Heidelberg Collaboratory for Image Processing")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "C++ computer vision library with emphasis on customizable algorithms and data structures"
)

# package version setup
SET(CPACK_PACKAGE_VERSION_MAJOR "${VIGRA_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${VIGRA_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${VIGRA_VERSION_PATCH}")

SET(CPACK_PACKAGE_INSTALL_DIRECTORY     "${PROJECT_NAME}")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY  "${PROJECT_NAME}")
SET(CPACK_RESOURCE_FILE_LICENSE         "${PROJECT_SOURCE_DIR}/LICENSE.txt")
SET(CPACK_RESOURCE_FILE_README          "${PROJECT_SOURCE_DIR}/README.txt")
SET(CPACK_STRIP_FILES TRUE)
SET(CPACK_SOURCE_IGNORE_FILES "${PROJECT_SOURCE_DIR}/.hg" ".#" "#.*~")
SET(CPACK_PACKAGE_CONTACT "Ullrich Koethe <ullrich.koethe@iwr.uni-heidelberg.de>")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "")

INCLUDE (CPack)
