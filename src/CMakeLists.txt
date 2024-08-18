add_executable(basic_model basic_model.cpp)
target_link_libraries(basic_model ${TORCH_LIBRARIES})
set_property(TARGET basic_model PROPERTY CXX_STANDARD 17)