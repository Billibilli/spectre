# Distributed under the MIT License.
# See LICENSE.txt for details.

set(EXECUTABLE HelloWorldNoCharm)

add_executable(
  ${EXECUTABLE}
  EXCLUDE_FROM_ALL
  HelloWorld.cpp
  )

target_link_libraries(
  ${EXECUTABLE}
  DataStructures
  )

set_target_properties(
  ${EXECUTABLE}
  PROPERTIES LINK_FLAGS "-nomain-module -nomain"
  )
