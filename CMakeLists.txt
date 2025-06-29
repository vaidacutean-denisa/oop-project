cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

###############################################################################

# external dependencies with FetchContent

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

# din cauza SFML
set(WARNINGS_AS_ERRORS OFF)

# NOTE: Also update SFML_VERSION env var in .github/workflows/cmake.yml:33
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.1
    # GIT_TAG        69ea0cd863aed1d4092b970b676924a716ff718b # 2.6.1
    # GIT_TAG        origin/master
    GIT_SHALLOW    1  # works only with branches or tags, not with arbitrary commit hashes
)

FetchContent_MakeAvailable(SFML)

###############################################################################

# external dependencies with find_package

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${MAIN_EXECUTABLE_NAME}
    main.cpp
    generated/src/Helper.cpp
    src/Ammunition.cpp
    headers/Ammunition.h
    src/Weapon.cpp
    headers/Weapon.h
    src/Bullet.cpp
    headers/Bullet.h
    src/Player.cpp
    headers/Player.h
    src/Enemy.cpp
    headers/Enemy.h
    src/Perks.cpp
    headers/Perks.h
    templates/Buttons.tpp
    headers/Buttons.h
    src/Menu.cpp
    headers/Menu.h
    src/Game.cpp
    headers/Game.h
    src/WeakZombie.cpp
    headers/WeakZombie.h
    src/StrongZombie.cpp
    headers/StrongZombie.h
    src/Zombie.cpp
    headers/Zombie.h
    src/EnemySpawner.cpp
    headers/EnemySpawner.h
    src/MessageManager.cpp
    headers/MessageManager.h
    src/LevelManager.cpp
    headers/LevelManager.h
    src/CombatSystem.cpp
    headers/CombatSystem.h
    src/AssetsManager.cpp
    headers/AssetsManager.h
    src/Skeleton.cpp
    headers/Skeleton.h
    src/MessageDisplay.cpp
    headers/MessageDisplay.h
    src/InventoryMenu.cpp
    headers/InventoryMenu.h
    src/WeaponManager.cpp
    headers/WeaponManager.h
    src/GameExceptions.cpp
    headers/GameExceptions.h
    src/Death.cpp
    headers/Death.h
    src/PerkManager.cpp
    headers/PerkManager.h
    headers/BasePerk.h
    src/PerkDecorator.cpp
    headers/PerkDecorator.h
    src/ShieldDecorator.cpp
    headers/ShieldDecorator.h
    src/RegenerationDecorator.cpp
    headers/RegenerationDecorator.h
)

# NOTE: Add all defined targets (e.g. executables, libraries, etc. )
# NOTE: RUN_SANITIZERS is optional, if it's not present it will default to true
set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})
# set_compiler_flags(TARGET_NAMES ${MAIN_EXECUTABLE_NAME} ${FOO} ${BAR})
# where ${FOO} and ${BAR} represent additional executables or libraries
# you want to compile with the set compiler flags

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)
# target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ext/<SomeHppLib>/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)

target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE headers)

target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-system
        Threads::Threads
)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
endif()

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# copy dependent DLLs to build dir
# see https://en.sfml-dev.org/forums/index.php?topic=28580.0
# remove this if not using audio or if using SFML 3
if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${MAIN_EXECUTABLE_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
         ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
         $<TARGET_FILE_DIR:${MAIN_EXECUTABLE_NAME}>
    )
endif()


copy_files(FILES tastatura.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME} DIRECTORY assets)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})
# copy_files(DIRECTORY images sounds COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})


