cmake_minimum_required(VERSION 3.15)
project(SegmentTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(SegmentTree main.cpp base.h SegmentTree.h SegmentPersistenceTree.h SegmentPersistenceTree.cpp SegmentTree.cpp)