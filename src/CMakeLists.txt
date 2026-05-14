add_executable(lcd-tools lcd-tools.cpp catfish-tools.cpp rubyfish-tools.cpp koi-tools.cpp medaka-tools.cpp)
target_link_libraries(lcd-tools PUBLIC CLI11::CLI11 ${mlite6_LIBRARIES} Qt::Core ${LIBHYBRIS_LIBRARIES})
target_include_directories(lcd-tools PRIVATE ${mlite6_INCLUDE_DIRS})
