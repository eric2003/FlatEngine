cmake_minimum_required(VERSION 3.29)

project(testprj LANGUAGES CXX)

set ( PRJ_COMPILE_FEATURES )
set ( PRJ_COMPILE_DEFINITIONS )
set ( PRJ_LIBRARIES )
set ( PRJ_INCLUDE_DIRS )

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

list ( APPEND PRJ_LIBRARIES Qt6::Widgets )
list ( APPEND PRJ_COMPILE_FEATURES cxx_std_23 )

if ( MSVC )
    set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )
endif()


add_executable( ${PROJECT_NAME}
)

target_sources( ${PROJECT_NAME}
  PRIVATE
    main.cpp
    Collisions.h Collisions.cpp
    FlatBody.h FlatBody.cpp
	FlatTransform.h FlatTransform.cpp
    FlatUtil.h FlatUtil.cpp
	FlatVector.h FlatVector.cpp
    GraphicsView.h GraphicsView.cpp
    Game.h Game.cpp
    RandomHelper.h RandomHelper.cpp
)

target_include_directories ( ${PROJECT_NAME}
  PRIVATE
    ${PRJ_INCLUDE_DIRS}
)

target_link_libraries( ${PROJECT_NAME} 
  PRIVATE 
    ${PRJ_LIBRARIES}
)

target_compile_features ( ${PROJECT_NAME} 
  PRIVATE 
    ${PRJ_COMPILE_FEATURES}
)

target_compile_definitions ( ${PROJECT_NAME}
  PRIVATE
    ${PRJ_COMPILE_DEFINITIONS} 
)
