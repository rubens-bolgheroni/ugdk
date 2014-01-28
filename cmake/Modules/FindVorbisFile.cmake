# Locate VorbisFile
#
# This module defines the standard variables
# - VORBISFILE_LIBRARIES
# - VORBISFILE_FOUND
# - VORBISFILE_INCLUDE_DIRS
#

SET(VORBISFILE_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # Fink
    /opt/local # DarwinPorts
    /opt/csw # Blastwave
    /opt
)

FIND_PATH(VORBISFILE_INCLUDE_DIR
    NAMES vorbis/vorbisfile.h
    HINTS
    $ENV{VORBISFILEDIR}
    $ENV{VORBISFILE_PATH}
    $ENV{VORBISDIR}
    $ENV{VORBIS_PATH}
    PATH_SUFFIXES include
    PATHS ${VORBISFILE_SEARCH_PATHS}
)

FIND_LIBRARY(VORBISFILE_LIBRARY
    NAMES vorbisfile libvorbisfile
    HINTS
    $ENV{VORBISFILEDIR}
    $ENV{VORBISFILE_PATH}
    PATH_SUFFIXES lib
    PATHS ${VORBISFILE_SEARCH_PATHS}
)


INCLUDE(FindPackageHandleStandardArgs)

set(VORBISFILE_LIBRARIES    ${VORBISFILE_LIBRARY})
set(VORBISFILE_INCLUDE_DIRS ${VORBISFILE_INCLUDE_DIR})

FIND_PACKAGE_HANDLE_STANDARD_ARGS(VORBISFILE
    REQUIRED_VARS VORBISFILE_LIBRARIES VORBISFILE_INCLUDE_DIRS)

mark_as_advanced(VORBISFILE_LIBRARY VORBISFILE_INCLUDE_DIR)