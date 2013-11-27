set(ZQUERY_LIBS "")
set(INS_TARGETS "")

set(INCLUDE_DIRECTORIES
  ${ZMQ_INCLUDE_DIR}
  ${CZMQ_INCLUDE_DIR}
  ${CMAKE_SOURCE_DIR}/src
)
include_directories( ${INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
  ${ZMQ_LIBRARIES}
  ${CZMQ_LIBRARIES}
)
link_directories( ${LINK_DIRECTORIES})

add_executable(zs_worker zs_worker.c)
target_link_libraries(zs_worker ${ZQUERY_LIBS} ${ZMQ_LIBRARIES} ${CZMQ_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
list(APPEND INS_TARGETS zs_worker)

add_executable(zs_broker zs_broker.c)
target_link_libraries(zs_broker ${ZQUERY_LIBS} ${ZMQ_LIBRARIES} ${CZMQ_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
list(APPEND INS_TARGETS zs_broker)

add_executable(zs_client zs_client.c)
target_link_libraries(zs_client ${ZQUERY_LIBS} ${ZMQ_LIBRARIES} ${CZMQ_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
list(APPEND INS_TARGETS zs_client)

install(TARGETS ${INS_TARGETS}
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION lib COMPONENT RUNTIME
ARCHIVE DESTINATION lib COMPONENT DEVELOPMENT)
