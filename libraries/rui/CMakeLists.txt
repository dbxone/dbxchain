
file(GLOB headers "*.h")

set(sources rnet.cpp
            ${headers})

add_library( rui
             ${sources}
             ${HEADERS} )
target_link_libraries( rui PRIVATE jsoncpp ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} )
target_include_directories( rui
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
                          )

install( TARGETS
   rui

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${headers} DESTINATION "." )
