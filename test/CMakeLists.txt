message("Proccessing Test Files")
add_executable(tests ${SOURCES} ${TESTFILES} ${INCLUDE_FILES} )

target_link_libraries(tests ${LIBRARIES})
