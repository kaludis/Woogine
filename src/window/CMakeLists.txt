set(SOURCE
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/window.cc
   PARENT_SCOPE
)

set(HEADERS
  ${HEADERS}
  ${CMAKE_CURRENT_SOURCE_DIR}/abstractwindow.h
  ${CMAKE_CURRENT_SOURCE_DIR}/window.h
  ${CMAKE_CURRENT_SOURCE_DIR}/windowsize.h
  PARENT_SCOPE
  )
