cmake_minimum_required(VERSION 3.1.0)

project(babelclient)

SET(SRCS    main.cpp
	    img.qrc
	    Gui.cpp
	    BabelClient.cpp
	    MainWindow.cpp
	    ConnectionWindow.cpp
	    PaSound.cpp
	    Opus.cpp
	    Udp.cpp
	    ContactLabel.cpp
	    CallWindow.cpp)

INCLUDE_DIRECTORIES(lib/include)
LINK_DIRECTORIES(lib)

set (UIS
 ConnectionWindow.ui
 ContactLabel.ui
 MainWindow.ui
)

set (RESOURCES
 img.qrc
)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

# Tell CMake to create the helloworld executable
add_executable(babelclient WIN32 ${SRCS})

target_compile_features(babelclient PRIVATE cxx_range_for)

# Use the Widgets module from Qt 5.
qt5_use_modules(babelclient Widgets Network)

target_link_libraries(babelclient portaudio)
target_link_libraries(babelclient asound)
target_link_libraries(babelclient pthread)
target_link_libraries(babelclient opus)
