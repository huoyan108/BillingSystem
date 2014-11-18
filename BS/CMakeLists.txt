cmake_minimum_required(VERSION 2.6)

if(WIN32)
        ADD_DEFINITIONS( -D_CRT_SECURE_NO_WARNINGS )
endif()

#project style
SET(CMAKE_BUILD_TYPE "Debug") 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

PROJECT (BS)

#build files
SET(SRC_LIST main.cpp debuginfo.cpp tools.cpp IniOper.cpp  DataTransfer.cpp DataBusiness.cpp PGDatabase.cpp PGRecordset.cpp ./proto/bcTx.pb.cc)

#zhi ding yuan wen jian mu lu 
#aux_source_directory(. SRC_LIST)

#lib include path
LINK_LIBRARIES(/usr/local/lib/)
INCLUDE_DIRECTORIES(/usr/local/include/)
LINK_DIRECTORIES(/usr/local)

#mu biao zhi xing lie biao 
ADD_EXECUTABLE(bs ${SRC_LIST})

#lian jie dong tai ku can shu 
#TARGET_LINK_LIBRARIES(hightcp lacewing)

#thread
TARGET_LINK_LIBRARIES(bs pthread)

#lua
TARGET_LINK_LIBRARIES(bs m)
TARGET_LINK_LIBRARIES(bs lua)
TARGET_LINK_LIBRARIES(bs dl)

#zmq
TARGET_LINK_LIBRARIES(bs zmq)

#protobuf
TARGET_LINK_LIBRARIES(bs protobuf)

#postgresql
TARGET_LINK_LIBRARIES(bs pq)
