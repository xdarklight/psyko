project( KOPETE_PSYKO )

find_package( KDE4 REQUIRED ) 
find_package( Automoc4 REQUIRED )
find_package( Qt4 REQUIRED )

add_definitions( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS} )

include_directories( ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )
link_directories( ${KDE4_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

# libkopete_psyko
set( KOPETEPSYKO_SRCS psykoplugin.cpp )

# FIXME
# kde4_add_kcfg_files( KOPETEPSYKO_SRCS psykoconfig.kcfgc )

kde4_add_plugin( kopete_psyko ${KOPETEPSYKO_SRCS} )
target_link_libraries( kopete_psyko kopete kdecore kdeui ${QT_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} )

# installation
#install( FILES kopetepsykoconfig.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
install( FILES kopete_psyko.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( TARGETS kopete_psyko DESTINATION ${PLUGIN_INSTALL_DIR} )