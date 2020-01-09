add_executable(main main.cpp  Circle.h
                Circle.cpp Rectangle.h Rectangle.cpp  SFMLDebugDraw.h
                SFMLDebugDraw.cpp Shape.h Shape.cpp Character1.h Character1.cpp
	        Character2.h Character2.cpp ContactListener.h)


set_target_properties(main
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )


target_link_libraries(main sfml-graphics  sfml-window sfml-system ${BOX2D_LIBRARIES})


add_custom_command(
        TARGET main POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/data/*.png
                ${CMAKE_CURRENT_BINARY_DIR} )
