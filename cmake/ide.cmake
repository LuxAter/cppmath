#---------------------------------------------------------------------------------------
# IDE support for headers
#---------------------------------------------------------------------------------------
set(CPPMATH_HEADERS_DIR "${CMAKE_CURRENT_LIST_DIR}/../include")

file(GLOB CPPMATH_TOP_HEADERS "${CPPMATH_HEADERS_DIR}/cppmath/*.h")
file(GLOB CPPMATH_DETAILS_HEADERS "${CPPMATH_HEADERS_DIR}/cppmath/details/*.h")
file(GLOB CPPMATH_SINKS_HEADERS "${CPPMATH_HEADERS_DIR}/cppmath/sinks/*.h")
file(GLOB CPPMATH_FMT_HEADERS "${CPPMATH_HEADERS_DIR}/cppmath/fmt/*.h")
file(GLOB CPPMATH_FMT_BUNDELED_HEADERS "${CPPMATH_HEADERS_DIR}/cppmath/fmt/bundled/*.h")
set(CPPMATH_ALL_HEADERS ${CPPMATH_TOP_HEADERS} ${CPPMATH_DETAILS_HEADERS} ${CPPMATH_SINKS_HEADERS} ${CPPMATH_FMT_HEADERS} ${CPPMATH_FMT_BUNDELED_HEADERS})

source_group("Header Files\\cppmath" FILES ${CPPMATH_TOP_HEADERS})
source_group("Header Files\\cppmath\\details" FILES ${CPPMATH_DETAILS_HEADERS})
source_group("Header Files\\cppmath\\sinks" FILES ${CPPMATH_SINKS_HEADERS})
source_group("Header Files\\cppmath\\fmt" FILES ${CPPMATH_FMT_HEADERS})
source_group("Header Files\\cppmath\\fmt\\bundled\\" FILES ${CPPMATH_FMT_BUNDELED_HEADERS})

