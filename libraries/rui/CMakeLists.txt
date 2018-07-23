
file(GLOB headers "*.h")

set(sources rnet.cpp
            ${headers})

add_library( rui
             ${sources}
             ${HEADERS} )
target_link_libraries( rui )
target_include_directories( rui
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
                          )

install( TARGETS
   rui

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${headers} DESTINATION "rui" )
