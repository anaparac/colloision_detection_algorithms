add_executable(simple src/main.cpp include/Square.h src/Square.cpp include/Circle.h
                src/Circle.cpp include/Rectangle.h src/Rectangle.cpp include/Rhombus.h src/Rhombus.cpp 
		include/SFMLDebugDraw.h
                src/SFMLDebugDraw.cpp include/Shape.h src/Shape.cpp include/Triangle.h src/Triangle.cpp 
		include/ContactListener.h)


set_target_properties(simple
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )


target_link_libraries(simple sfml-graphics  sfml-window sfml-system ${BOX2D_LIBRARIES})


#add_custom_command(
#        TARGET main POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy
#		${CMAKE_SOURCE_DIR}
#                ${CMAKE_CURRENT_BINARY_DIR} )
