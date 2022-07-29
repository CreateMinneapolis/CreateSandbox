project (WebService)

include(${CMAKE_FRAMEWORK_DIR}/project/project.cmake)

# --------------------- Source -----------------------

set (SOURCEFILES
  web_app.cc
)

set (HEADERFILES
)

# --------------------- Dependencies -----------------------

add_external(CppWebServerLib
	GIT_REPOSITORY https://github.com/dtorban/CppWebServer.git
	LIB_NAME CppWebServer
)
set(DEP_INCLUDES ${DEP_INCLUDES} ${external_dir}/CppWebServerLib/src/src)
set(DEP_INCLUDES ${DEP_INCLUDES} 
  ${external_dir}/CppWebServerLib/src/cmake/framework/external/WebSockets/build/install/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/physics_system/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/entity_system/include

)

set(DEP_LINK_DIRS ${DEP_LINK_DIRS} 
  ${external_dir}/CppWebServerLib/src/cmake/framework/external/WebSockets/build/install/lib
)


set(ALL_LIBS ${ALL_LIBS} websockets crypto ssl z)

include(${external_dir}/CPP11/CPP11.cmake)
useCPP11()

set(DEP_INCLUDES ${DEP_INCLUDES} PhysicsSystem)
set(DEP_LIBS ${DEP_LIBS} PhysicsSystem)

set(DEP_INCLUDES ${DEP_INCLUDES} EntitySystem)
set(DEP_LIBS ${DEP_LIBS} EntitySystem)



# --------------------- Executable -----------------------

addStandardExecutable()

