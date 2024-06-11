include_directories (../)
include_directories (./)

add_library(
        EyerCore
        # SHARED

        EyerCore.hpp

        EyerString.hpp
        EyerString.cpp

        EyerLog.hpp
        EyerLog.cpp

        EyerLogStatus.cpp

        EyerRand.cpp
        EyerTime.cpp

        EyerLRUMap.hpp
        EyerLockQueue.hpp

        EyerTime.hpp

        EyerBuffer.cpp
        EyerBuffer.hpp

        string_ext.cpp
        string_ext.h

        EyerURLUtil.cpp
        EyerURLUtil.hpp

        EyerUtil.cpp
        EyerUtil.hpp

        EyerBufferMut.cpp
        EyerBufferMut.hpp

        EyerMD5.cpp
        EyerMD5.hpp

        EyerSockaddr.cpp
        EyerSockaddr.hpp

        BLOCK_TIME.cpp
        BLOCK_TIME.hpp

        EyerTable.cpp
        EyerTable.hpp

        EyerRand.hpp
        EyerObserverQueue.hpp

        EyerObserver.cpp
        EyerObserver.hpp

        EyerSubject.cpp
        EyerSubject.hpp

        EyerObserverQueue.h
        EyerObserverQueue_C.cpp

        EyerBuffer.h
        EyerBuffer_C.cpp

        EyerBufferPlus.cpp
        EyerBufferPlus.hpp

        EyerBufferPlusCallback.hpp
        EyerBufferPlusCallback.cpp

        EyerBitStream.hpp
        EyerBitStream.cpp

        EyerSmartPtr.cpp
        EyerSmartPtr.hpp

        EyerSharedCount.cpp
        EyerSharedCount.hpp

        EyerFileReader.hpp
        EyerFileReader.cpp

        EyerObserverList.cpp
        EyerObserverList.hpp

        EyerVersion.cpp

        EyerLRUCache.hpp
        EyerLRUCache.cpp
)

set(head_files 
        EyerString.hpp
        EyerCore.hpp
        EyerLog.hpp
        EyerTime.hpp
        EyerLinkedList.hpp
        EyerLinkedEle.hpp
        EyerQueue.hpp
        EyerMap.hpp
        EyerMapEle.hpp
        EyerLockQueue.hpp
        EyerLRUMap.hpp
        EyerBuffer.hpp
        EyerBufferMut.hpp
        EyerURLUtil.hpp
        EyerUtil.hpp
        EyerMD5.hpp
        EyerSockaddr.hpp
        BLOCK_TIME.hpp
        EyerTable.hpp
        EyerRand.hpp
        EyerObserverQueue.h
        EyerObserverQueue.hpp
        EyerBuffer.h
        EyerSubject.hpp
        EyerObserver.hpp
        EyerBufferPlus.hpp
        EyerBufferPlusCallback.hpp
        EyerBitStream.hpp
        EyerSmartPtr.hpp
        EyerSharedCount.hpp
        EyerFileReader.hpp
        EyerObserverList.hpp
        EyerLRUCache.hpp
)

INSTALL(FILES ${head_files} DESTINATION include/EyerCore)
INSTALL(
        TARGETS EyerCore
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
