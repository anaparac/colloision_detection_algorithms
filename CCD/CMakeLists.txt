add_executable(ccd src/main.cpp include/Bullet.h
                src/Bullet.cpp include/Wall.h src/Wall.cpp  include/SFMLDebugDraw.h
                src/SFMLDebugDraw.cpp include/Shape.h src/Shape.cpp  
                include/Character.h src/Character.cpp include/Target.h src/Target.cpp )


set_target_properties(ccd
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENSIONS OFF
    CXX_STANDARD_REQUIRED ON
  )


target_link_libraries(ccd sfml-graphics  sfml-window sfml-system ${BOX2D_LIBRARIES})


add_custom_command(
        TARGET ccd POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
	${CMAKE_SOURCE_DIR}/CCD/data/*.png
                ${CMAKE_CURRENT_BINARY_DIR} )
