add_executable(main main.cpp Wall.h Wall.cpp  SFMLDebugDraw.h
                SFMLDebugDraw.cpp Player.h Player.cpp Character1.h Character1.cpp
                Character2.h Character2.cpp Character3.h Character3.cpp ContactListener.h)


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
