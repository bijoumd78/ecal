# =====n=================== eCAL LICENSE =================================
#
# Copyright (C) 2016 - 2019 Continental Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# ========================= eCAL LICENSE =================================

project(person_rec_events)

find_package(eCAL REQUIRED)
find_package(Protobuf REQUIRED)

set(person_rec_events_src
    person_rec_events.cpp
)

set(person_rec_events_proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/animal.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/house.proto
  ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/person.proto    
)
ecal_add_sample(${PROJECT_NAME} ${person_rec_events_src})
PROTOBUF_TARGET_CPP(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/protobuf ${person_rec_events_proto})
target_include_directories(${PROJECT_NAME} PRIVATE .)

target_link_libraries(${PROJECT_NAME}
  eCAL::core
  protobuf::libprotobuf)

ecal_install_sample(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER samples/cpp/person)
