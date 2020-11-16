

set(SOURCE_TEST_DATA_DIR "${PROJECT_SOURCE_DIR}/tests/data")
set(BINARY_TEST_DATA_DIR "${PROJECT_BINARY_DIR}/tests/data")

# Add test data files here to use in test
# (gets added to 'playground::TEST_DATA' array in 'test_config.h' in next few steps)
set(TEST_DATA_FILE_LIST
	"test_data.txt"
)


foreach(data_file ${TEST_DATA_FILE_LIST})
	
	set (data_file_path "${BINARY_TEST_DATA_DIR}/${data_file}")

	# Setting data file path string list
	if(NOT TEST_DATA_FILES)
		set(TEST_DATA_FILES "\"${data_file_path}\"")
	else()
		set(TEST_DATA_FILES "${TEST_DATA_FILES},\n\t\"${data_file_path}\"")
	endif()
	
	# Modify file names to valid C++ file names (and avoid most probable resulting name clashes)
	string(REGEX REPLACE "[^0-9A-Za-z\/_]" "____" data_file_id "${data_file}")
	string(REGEX REPLACE "\/" "__DIR__" data_file_id "${data_file_id}")

	# Checking that data file id is not taken, if yes, abort
	if("${data_file_id}" IN_LIST TEST_DATA_FILE_ID_LIST)
		message(FATAL_ERROR "CMake data file id generation failed: '${data_file_id}' already exists.")
	endif()
	list(APPEND TEST_DATA_FILE_ID_LIST "${data_file_id}")

	# Setting data file name string list
	if(NOT TEST_DATA_FILE_IDS)
		set(TEST_DATA_FILE_IDS "${data_file_id}")
	else()
		set(TEST_DATA_FILE_IDS "${TEST_DATA_FILE_IDS},\n\t${data_file_id}")
	endif()

endforeach()



# Copy data folder from source to binary folder
add_custom_target(copy-files ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	"${SOURCE_TEST_DATA_DIR}"
	"${BINARY_TEST_DATA_DIR}"
)

# configuring test_config header with needed file paths
configure_file(test_config.h.in test_config.h @ONLY)

set(TEST_SOURCE_LIST
	"playground_seesaw_tests.cpp"
)

# Add test executable
set(TEST_APP_NAME "PlaygroundTests")
add_executable("${TEST_APP_NAME}" ${TEST_SOURCE_LIST} "${CMAKE_CURRENT_BINARY_DIR}/test_config.h")

# We need this directory
target_include_directories("${TEST_APP_NAME}" PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

# The target itself requires at least C++11
target_compile_features("${TEST_APP_NAME}" PRIVATE cxx_std_11)

# Link test executable with library and gtest
target_link_libraries("${TEST_APP_NAME}"
	gtest_main
	"${LIBRARY_NAME}"
)

add_test(
	NAME "${TEST_APP_NAME}"
	COMMAND "${TEST_APP_NAME}"
	# works for ctest, but not for test executable, thus not used
	#WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/tests/data"
)

