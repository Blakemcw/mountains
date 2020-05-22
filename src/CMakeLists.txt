message("Proccessing Source Files")
add_executable( mountains ${SOURCES} ${MAIN} ${INCLUDE_FILES})

target_link_libraries(mountains ${LIBRARIES})
