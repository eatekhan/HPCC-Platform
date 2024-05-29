project(hpcccmd)

include_directories (
    ${CMAKE_BINARY_DIR}
    ${HPCC_SOURCE_DIR}/esp/esdllib
    ${HPCC_SOURCE_DIR}/system/jlib
    ${HPCC_SOURCE_DIR}/esp/platform
    ${HPCC_SOURCE_DIR}/system/xmllib
    ${HPCC_SOURCE_DIR}/esp/bindings
    ${HPCC_SOURCE_DIR}/esp/bindings/http/client
    ${HPCC_SOURCE_DIR}/esp/bindings/SOAP/xpp
    ${HPCC_SOURCE_DIR}/esp/clients/wsecl
    ${HPCC_SOURCE_DIR}/system/include
    ${HPCC_SOURCE_DIR}/esp/services/common
    ${HPCC_SOURCE_DIR}/esp/esdlscriptlib
    ${HPCC_SOURCE_DIR}/system/security/shared
    ${HPCC_SOURCE_DIR}/tools/esdlcomp
    ${HPCC_SOURCE_DIR}/tools/esdlcmd-xml
)
set (  SRCS
       hpcccmd.cpp
       hpcccmd.hpp
       hpccshell.cpp
    )

ADD_DEFINITIONS(-D_CONSOLE)

HPCC_ADD_EXECUTABLE ( hpcc ${SRCS} )



install ( TARGETS hpcc RUNTIME DESTINATION ${EXEC_DIR} )


add_dependencies ( hpcc esdllib jlib espscm)

target_link_libraries( hpcc
    esdllib
    jlib
    xmllib
    dllserver)
