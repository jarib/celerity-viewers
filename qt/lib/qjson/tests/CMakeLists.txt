##### Probably don't want to edit below this line ##### 

SET( QT_USE_QTTEST TRUE )

# Use it
INCLUDE( ${QT_USE_FILE} )

INCLUDE(AddFileDependencies)

# Include the library include directories, and the current build directory (moc)
INCLUDE_DIRECTORIES(
	../src
	${CMAKE_CURRENT_BINARY_DIR}
)

QT4_WRAP_CPP(MOC_SOURCE cmdline_tester.cpp)
ADD_EXECUTABLE(
	cmdline_tester
	cmdline_tester.cpp
)

ADD_FILE_DEPENDENCIES(cmdline_tester.cpp ${MOC_SOURCE})
TARGET_LINK_LIBRARIES(
	cmdline_tester
	${QT_LIBRARIES}
	qjson
)

SET( UNIT_TESTS
	testjsondriver
)

# Build the tests
FOREACH(test ${UNIT_TESTS})
	MESSAGE(STATUS "Building ${test}")
	QT4_WRAP_CPP(MOC_SOURCE ${test}.cpp)
	ADD_EXECUTABLE(
		${test}
		${test}.cpp

	)
	ADD_FILE_DEPENDENCIES(${test}.cpp ${MOC_SOURCE})
	TARGET_LINK_LIBRARIES(
		${test}
		${QT_LIBRARIES}
		qjson
	)
	if (QJSON_TEST_OUTPUT STREQUAL "xml")
		# produce XML output
                add_test( ${test} ${test} -xml -o ${test}.tml )
	else (QJSON_TEST_OUTPUT STREQUAL "xml")
		add_test( ${test} ${test} )
	endif (QJSON_TEST_OUTPUT STREQUAL "xml")
ENDFOREACH()
