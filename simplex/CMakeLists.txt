CMAKE_MINIMUM_REQUIRED(VERSION 3.10.2 )
project(<PROJECT-NAME>_SOURCE_DIR)
add_subdirectory(gsl)
add_executable( app main.c prepare_data.c)
target_link_libraries(app gsl)
file(GLOB data_files "data/*.txt")
message(${data_files})

configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/data/matrix.txt ${CMAKE_CURRENT_BINARY_DIR}/matrix.txt COPYONLY)
configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/data/vectorB.txt ${CMAKE_CURRENT_BINARY_DIR}/vectorB.txt COPYONLY)

