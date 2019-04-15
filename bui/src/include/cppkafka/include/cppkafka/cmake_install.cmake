# Install script for directory: /data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka

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
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppkafka" TYPE FILE FILES
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/buffer.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/clonable_ptr.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/configuration.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/configuration_base.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/configuration_option.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/consumer.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/cppkafka.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/error.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/event.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/exceptions.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/group_information.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/header.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/header_list.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/header_list_iterator.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/kafka_handle_base.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/logging.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/macros.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/message.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/message_builder.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/message_internal.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/message_timestamp.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/metadata.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/producer.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/queue.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/topic.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/topic_configuration.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/topic_partition.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/topic_partition_list.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppkafka/utils" TYPE FILE FILES
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/backoff_committer.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/backoff_performer.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/buffered_producer.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/compacted_topic_processor.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/consumer_dispatcher.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/poll_interface.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/poll_strategy_base.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/utils/roundrobin_poll_strategy.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xHeadersx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cppkafka/detail" TYPE FILE FILES
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/detail/callback_invoker.h"
    "/data/sydeng/repositary/hnsw-repo/Distributed-HNSW/src/include/cppkafka/include/cppkafka/detail/endianness.h"
    )
endif()

