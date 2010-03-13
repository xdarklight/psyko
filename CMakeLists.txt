project( KOPETE_PSYKO )

find_package( KDE4 REQUIRED ) 
find_package( Automoc4 REQUIRED )
find_package( Qt4 REQUIRED )

add_definitions( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS} )

include_directories( ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/src )
link_directories( ${KDE4_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/src )

add_subdirectory(src)