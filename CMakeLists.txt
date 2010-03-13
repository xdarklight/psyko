project( KOPETE_PSYKO )

find_package( KDE4 REQUIRED ) 
find_package( Automoc4 REQUIRED )
find_package( Qt4 REQUIRED )

add_definitions( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS} )

include_directories( ${KDE4_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} )
link_directories( ${KDE4_LIB_DIR} ${CMAKE_CURRENT_BINARY_DIR} )

# libkopete_psyko
set( KOPETEPSYKO_SRCS psykoplugin.cpp )

kde4_add_kcfg_files( KOPETEPSYKO_SRCS psykoconfiguration.kcfgc )
kde4_add_plugin( kopete_psyko ${KOPETEPSYKO_SRCS} )

target_link_libraries( kopete_psyko kopete kdecore kdeui ${QT_LIBRARIES} ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} )

# libkcm_kopete_psyko
set( KCMKOPETEPSYKO_SRCS psykopreferences.cpp )

kde4_add_ui_files( KCMKOPETEPSYKO_SRCS psykopreferences.ui )
kde4_add_kcfg_files( KCMKOPETEPSYKO_SRCS psykoconfiguration.kcfgc )
kde4_add_plugin( kcm_kopete_psyko ${KCMKOPETEPSYKO_SRCS} )

target_link_libraries( kcm_kopete_psyko kopete kdecore kdeui ${KDE4_KDEUI_LIBS} )

# installation
install( FILES psykoconfiguration.kcfg DESTINATION ${KCFG_INSTALL_DIR} )
install( FILES kopete_psyko.desktop DESTINATION ${SERVICES_INSTALL_DIR} )
install( FILES kopete_psyko_configuration.desktop DESTINATION ${SERVICES_INSTALL_DIR}/kconfiguredialog )
install( TARGETS kopete_psyko DESTINATION ${PLUGIN_INSTALL_DIR} )
install( TARGETS kcm_kopete_psyko DESTINATION ${PLUGIN_INSTALL_DIR} )