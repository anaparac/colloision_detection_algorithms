add_executable(nonconvex src/main.cpp include/Wall.h src/Wall.cpp  include/SFMLDebugDraw.h
                src/SFMLDebugDraw.cpp include/Player.h src/Player.cpp include/Character1.h src/Character1.cpp
                include/Character2.h src/Character2.cpp include/Character3.h 
		src/Character3.cpp include/ContactListener.h)


set_target_properties(nonconvex
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )


target_link_libraries(nonconvex sfml-graphics  sfml-window sfml-system ${BOX2D_LIBRARIES})


add_custom_command(
        TARGET nonconvex POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
		${CMAKE_SOURCE_DIR}/nonconvex_shape/data/*.png
                ${CMAKE_CURRENT_BINARY_DIR} )
