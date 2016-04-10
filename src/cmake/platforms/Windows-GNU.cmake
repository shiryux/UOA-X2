#[[
TARGET_COMPILE_DEFINITIONS (spheresvrNightly
# Nighly defs
        PUBLIC _NIGHTLYBUILD
        PUBLIC THREAD_TRACK_CALLSTACK
# Debug defs
        PUBLIC _DEBUG
        PUBLIC _PACKETDUMP
        PUBLIC _TESTEXCEPTION
        PUBLIC DEBUG_CRYPT_MSGS
# Extra defs
        PUBLIC _MTNETWORK
# GIT defs
        PUBLIC _GITVERSION
# Defines
        PUBLIC _WINDOWS
        PUBLIC _CRT_SECURE_NO_WARNINGS
	PUBLIC _EXCEPTIONS_DEBUG
	PUBLIC _WINSOCK_DEPRECATED_NO_WARNINGS
) ]]

SET (C_WARNING_FLAGS "-Wall -Wextra -Wno-unknown-pragmas -Wno-switch")
SET (CXX_WARNING_FLAGS "-Wall -Wextra -Wno-unknown-pragmas -Wno-invalid-offsetof -Wno-switch")
IF ( ${ARCH} STREQUAL "x86_64" )
	SET (C_ARCH_OPTS "-march=x86-64 -m64")
	SET (CXX_ARCH_OPTS "-march=x86-64 -m64")
	#SET (CMAKE_RC_FLAGS "--target=pe-x86-64")
ELSE ( ${ARCH} STREQUAL "x86_64" )
	SET (C_ARCH_OPTS "-march=i686 -m32")
	SET (CXX_ARCH_OPTS "-march=i686 -m32")
	#SET (CMAKE_RC_FLAGS "--target=pe-i386")
ENDIF ( ${ARCH} STREQUAL "x86_64" )
SET (C_OPTS "-s -fno-omit-frame-pointer -ffast-math -O3 -fno-expensive-optimizations")
SET (CXX_OPTS "-s -fno-omit-frame-pointer -ffast-math -fpermissive -O3")
SET (C_SPECIAL "-fexceptions -fnon-call-exceptions")
SET (CXX_SPECIAL "-fexceptions -fnon-call-exceptions")
SET (CMAKE_C_FLAGS "${C_WARNING_FLAGS} ${C_ARCH_OPTS} ${C_OPTS} ${C_SPECIAL} -std=c11")
SET (CMAKE_CXX_FLAGS "${CXX_WARNING_FLAGS} ${CXX_ARCH_OPTS} ${CXX_OPTS} ${CXX_SPECIAL} -std=c++11")

# Optimization flags set to max.
SET_TARGET_PROPERTIES (spheresvr		PROPERTIES	COMPILE_FLAGS -O3 )
#SET_TARGET_PROPERTIES (spheresvrNightly	 PROPERTIES	COMPILE_FLAGS -O3 )
# Force dynamic linking.
SET (CMAKE_EXE_LINKER_FLAGS "-dynamic -static-libstdc++ -static-libgcc")

# Linux libs.
TARGET_LINK_LIBRARIES ( spheresvr
        pthread
        libmysql
        ws2_32
        wsock32
)
#[[
TARGET_LINK_LIBRARIES ( spheresvrNightly
        pthread
        libmysql
        ws2_32
        wsock32
) ]]