#create executable
add_executable(TestLib "test.cpp")

set_target_properties(TestLib PROPERTIES
CXX_STANDARD 11
CXX_STANDARD_REQUIRED ON
CXX_EXTENSIONS OFF)

target_link_libraries(TestLib PRIVATE TimeCpp)