set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/fsresolver.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/meshdatareader.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/programdatareader.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/spritedatareader.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/imageloader.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/objloader.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.cc
   ${CMAKE_CURRENT_SOURCE_DIR}/texturedatareader.cc
   PARENT_SCOPE
)

set(HEADERS
  ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/fsresolver.h
   ${CMAKE_CURRENT_SOURCE_DIR}/meshdatareader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/programdatareader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/spritedatareader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/imageloader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/objloader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/resourcemanager.h
   ${CMAKE_CURRENT_SOURCE_DIR}/texturedatareader.h
   ${CMAKE_CURRENT_SOURCE_DIR}/meshrawdata.h
   ${CMAKE_CURRENT_SOURCE_DIR}/texturerawdata.h
   ${CMAKE_CURRENT_SOURCE_DIR}/objdata.h
   ${CMAKE_CURRENT_SOURCE_DIR}/programrawdata.h
   ${CMAKE_CURRENT_SOURCE_DIR}/spriterawdata.h
  PARENT_SCOPE
  )
