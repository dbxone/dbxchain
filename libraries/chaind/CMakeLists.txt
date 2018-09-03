
file(GLOB headers "*.h")

set(sources net.cpp chaind.cpp
            ${headers})

add_library( chaind
             ${sources}
             ${HEADERS} )
target_link_libraries( chaind PRIVATE jsoncpp ${CMAKE_DL_LIBS} ${PLATFORM_SPECIFIC_LIBS} )
target_include_directories( chaind
                            PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}"
                          )

install( TARGETS
   chaind

   RUNTIME DESTINATION bin
   LIBRARY DESTINATION lib
   ARCHIVE DESTINATION lib
)
install( FILES ${headers} DESTINATION "." )
