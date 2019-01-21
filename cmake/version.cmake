FILE(STRINGS "${WORLD_BUILDER_SOURCE_DIR}/VERSION" WORLD_BUILDER_VERSION)
string(REPLACE "-" "." VERSION_LIST_TEMP ${WORLD_BUILDER_VERSION})
string(REPLACE "." ";" VERSION_LIST ${VERSION_LIST_TEMP})
list(LENGTH VERSION_LIST VERSION_LENGTH)
list(GET VERSION_LIST 0 WORLD_BUILDER_VERSION_MAJOR)
list(GET VERSION_LIST 1 WORLD_BUILDER_VERSION_MINOR)
list(GET VERSION_LIST 2 WORLD_BUILDER_VERSION_PATCH)
if (${VERSION_LENGTH} GREATER 3)
  list(GET VERSION_LIST 3 WORLD_BUILDER_VERSION_LABEL)
endif()

find_package(Git)
IF(GIT_FOUND AND EXISTS ${WORLD_BUILDER_SOURCE_DIR}/.git)
execute_process(COMMAND
  "${GIT_EXECUTABLE}" describe --match=NeVeRmAtCh --always --abbrev=40 --dirty
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_SHA1
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

execute_process(COMMAND
  "${GIT_EXECUTABLE}" rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_BRANCH
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# the date of the commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 --format=%ad --date=local
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_DATE
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

# the subject of the commit
execute_process(COMMAND
  "${GIT_EXECUTABLE}" log -1 --format=%s
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
  OUTPUT_VARIABLE GIT_COMMIT_SUBJECT
  ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)

ENDIF()