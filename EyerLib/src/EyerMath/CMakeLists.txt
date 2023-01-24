INCLUDE_DIRECTORIES (../)
INCLUDE_DIRECTORIES (./)

ADD_LIBRARY(
        EyerMath
        EyerMath.hpp
        Eatrix.hpp
        Eatrix.cpp
        Eatrix4x4.hpp
        Eath.cpp
        Eath.hpp
        Eatrix3x1.hpp
        Eatrix3x3.hpp
        EnterPolation.cpp
        EnterPolation.hpp
        Eatrix4x1.hpp
        Eatrix2x1.hpp
        Eyer2DCrop.hpp
        Eyer2DCrop.cpp
        Eatrix2x1.hpp

        RectUtil.hpp
        RectUtil.cpp

        Eect.cpp
        Eect.hpp

        EyerColor.hpp
        EyerColor.cpp

        Vec2I.hpp
        Vec2I.cpp

        EyerRectI.hpp
        EyerRectI.cpp
)

SET(head_files
        EyerMath.hpp
        Eath.hpp
        Eatrix.hpp
        Eatrix3x1.hpp
        Eatrix3x3.hpp
        Eatrix4x1.hpp
        Eatrix4x4.hpp
        Eatrix2x1.hpp
        EnterPolation.hpp
        Eyer2DCrop.hpp
        RectUtil.hpp
        Eect.hpp
        EyerColor.hpp
        Vec2I.hpp
        EyerRectI.hpp
        )

INSTALL(FILES ${head_files} DESTINATION include/EyerMath)
INSTALL(
        TARGETS EyerMath
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
