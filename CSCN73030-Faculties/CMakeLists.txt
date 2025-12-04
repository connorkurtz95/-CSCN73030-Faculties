cmake_minimum_required(VERSION 3.16)

project(CSCN73030-Faculties LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)


add_executable(CSCN73030-Faculties
  main.cpp
  part.h part.cpp
  calendar.h
  calendar.cpp
  calendarwidget.h calendarwidget.cpp
    report.h report.cpp

    logs.h logs.cpp
    logsWindow.h logsWindow.cpp logsWindow.ui
    writeReportWindow.h writeReportWindow.cpp writeReportWindow.ui
)
target_link_libraries(CSCN73030-Faculties
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Widgets
)
include(GNUInstallDirs)
install(TARGETS CSCN73030-Faculties
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
