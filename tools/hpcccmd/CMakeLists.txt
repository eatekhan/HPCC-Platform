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
    ${HPCC_SOURCE_DIR}/common/dllserver
    ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}/oss
    ${HPCC_SOURCE_DIR}/fs/dafsclient
    ${HPCC_SOURCE_DIR}/system/mp 
    ${HPCC_SOURCE_DIR}/rtl/eclrtl 
    ${HPCC_SOURCE_DIR}/dali/base 
    ${HPCC_SOURCE_DIR}/esp/esdlscriptlib
    ${HPCC_SOURCE_DIR}/rtl/include #IXMLWriter
    ${HPCC_SOURCE_DIR}/common/thorhelper #JSONWRITER
    # ${HPCC_SOURCE_DIR}/common/dllserver #loading plugins
    ${HPCC_SOURCE_DIR}/tools/hidl #TAccessMapGenerator
    ${HPCC_SOURCE_DIR}/system/masking/include

    
)
set (  SRCS
       hpcccmd.cpp
       hpcccmd.hpp
       hpccshell.cpp
       hpccshell.hpp
       hpccservice.hpp
       hpccservice.cpp
    )

ADD_DEFINITIONS(-D_CONSOLE)

HPCC_ADD_EXECUTABLE ( hpcc ${SRCS} )



install ( TARGETS hpcc RUNTIME DESTINATION ${EXEC_DIR} )


add_dependencies ( hpcc esdllib jlib espscm)

target_link_libraries( hpcc
    esdllib
    jlib
    xmllib
    dllserver
    esphttp)
