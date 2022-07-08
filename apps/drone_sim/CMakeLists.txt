project (DroneSim)

include(${CMAKE_FRAMEWORK_DIR}/project/project.cmake)

# --------------------- Source -----------------------

file(GLOB src
     "src/*.cc"
)

file(GLOB inc
     "include/*.h"
)

set (SOURCEFILES
	${src}
)

set (HEADERFILES
	${inc}
)

# --------------------- Dependencies -----------------------

add_external(picojson
	GIT_REPOSITORY https://github.com/kazuho/picojson.git
	HEADER_ONLY
)
add_external(CppWebServerLib
	GIT_REPOSITORY https://github.com/dtorban/CppWebServer.git
	LIB_NAME CppWebServer
)
set(DEP_INCLUDES ${DEP_INCLUDES} ${external_dir}/CppWebServerLib/src/src)
set(DEP_INCLUDES ${DEP_INCLUDES} ${external_dir}/CppWebServerLib/src/cmake/framework/external/WebSockets/build/install/include)
set(DEP_LINK_DIRS ${DEP_LINK_DIRS} 
  ${external_dir}/CppWebServerLib/src/cmake/framework/external/WebSockets/build/install/lib
)
set(DEP_INCLUDES ${DEP_INCLUDES} 
	${external_dir}/picojson/src
)
set(ALL_LIBS ${ALL_LIBS} websockets crypto ssl z)

include(${external_dir}/CPP11/CPP11.cmake)
useCPP11()

# --------------------- Executable -----------------------

addStandardExecutable()

