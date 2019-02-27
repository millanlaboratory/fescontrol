# Install script for directory: /home/cnbi/dev/fesapps/fesjson

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/fescontrol/libfescontrol.a")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/lib/fescontrol" TYPE STATIC_LIBRARY FILES "/home/cnbi/dev/fesapps/fesjson/libfescontrol.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/bin/fesControl" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/bin/fesControl")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/bin/fesControl"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/bin/fesControl")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/bin" TYPE EXECUTABLE FILES "/home/cnbi/dev/fesapps/fesjson/build/fesControl")
  if(EXISTS "$ENV{DESTDIR}/usr/bin/fesControl" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/bin/fesControl")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/usr/bin/fesControl"
         OLD_RPATH "/usr/include/jsoncpp:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/bin/fesControl")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/fescontrol/Application.h;/usr/include/fescontrol/Channel.h;/usr/include/fescontrol/ConnectedApplication.h;/usr/include/fescontrol/FESJsonReader.h;/usr/include/fescontrol/FESStimulator.h;/usr/include/fescontrol/Incrementer.h;/usr/include/fescontrol/IncrementerFactory.h;/usr/include/fescontrol/LinearIncrementer.h;/usr/include/fescontrol/MovementAuthorizer.h;/usr/include/fescontrol/SetterAction.h;/usr/include/fescontrol/StimulationAction.h;/usr/include/fescontrol/StimulationActionFactory.h;/usr/include/fescontrol/TimeLimitedAction.h;/usr/include/fescontrol/matplotlibcpp.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include/fescontrol" TYPE FILE FILES
    "/home/cnbi/dev/fesapps/fesjson/src/Application.h"
    "/home/cnbi/dev/fesapps/fesjson/src/Channel.h"
    "/home/cnbi/dev/fesapps/fesjson/src/ConnectedApplication.h"
    "/home/cnbi/dev/fesapps/fesjson/src/FESJsonReader.h"
    "/home/cnbi/dev/fesapps/fesjson/src/FESStimulator.h"
    "/home/cnbi/dev/fesapps/fesjson/src/Incrementer.h"
    "/home/cnbi/dev/fesapps/fesjson/src/IncrementerFactory.h"
    "/home/cnbi/dev/fesapps/fesjson/src/LinearIncrementer.h"
    "/home/cnbi/dev/fesapps/fesjson/src/MovementAuthorizer.h"
    "/home/cnbi/dev/fesapps/fesjson/src/SetterAction.h"
    "/home/cnbi/dev/fesapps/fesjson/src/StimulationAction.h"
    "/home/cnbi/dev/fesapps/fesjson/src/StimulationActionFactory.h"
    "/home/cnbi/dev/fesapps/fesjson/src/TimeLimitedAction.h"
    "/home/cnbi/dev/fesapps/fesjson/src/matplotlibcpp.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/fescontrol/interfaces/CcCoreInstance.h;/usr/include/fescontrol/interfaces/ClLoopInstance.h;/usr/include/fescontrol/interfaces/ClTobiIdInstance.h;/usr/include/fescontrol/interfaces/SerialPort.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include/fescontrol/interfaces" TYPE FILE FILES
    "/home/cnbi/dev/fesapps/fesjson/src/interfaces/CcCoreInstance.h"
    "/home/cnbi/dev/fesapps/fesjson/src/interfaces/ClLoopInstance.h"
    "/home/cnbi/dev/fesapps/fesjson/src/interfaces/ClTobiIdInstance.h"
    "/home/cnbi/dev/fesapps/fesjson/src/interfaces/SerialPort.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/fescontrol/errors/AuthorizerException.h;/usr/include/fescontrol/errors/ChannelException.h;/usr/include/fescontrol/errors/JsonException.h;/usr/include/fescontrol/errors/LoopException.h;/usr/include/fescontrol/errors/StimulationException.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include/fescontrol/errors" TYPE FILE FILES
    "/home/cnbi/dev/fesapps/fesjson/src/errors/AuthorizerException.h"
    "/home/cnbi/dev/fesapps/fesjson/src/errors/ChannelException.h"
    "/home/cnbi/dev/fesapps/fesjson/src/errors/JsonException.h"
    "/home/cnbi/dev/fesapps/fesjson/src/errors/LoopException.h"
    "/home/cnbi/dev/fesapps/fesjson/src/errors/StimulationException.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/include/fescontrol/fesdecode.h;/usr/include/fescontrol/fesencode.h;/usr/include/fescontrol/feslanguage.h;/usr/include/fescontrol/serialport.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/include/fescontrol" TYPE FILE FILES
    "/usr/include/feslanguage/fesdecode.h"
    "/usr/include/feslanguage/fesencode.h"
    "/usr/include/feslanguage/feslanguage.h"
    "/usr/include/feslanguage/serialport.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/cnbi/dev/fesapps/fesjson/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
