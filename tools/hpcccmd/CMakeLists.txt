project(hpcccmd)

include_directories (
    ${HPCC_SOURCE_DIR}/esp/esdllib
)
set (  SRCS
       hpcccmd.cpp
    )

ADD_DEFINITIONS(-D_CONSOLE)

HPCC_ADD_EXECUTABLE ( hpcc ${SRCS} )



install ( TARGETS hpcc RUNTIME DESTINATION ${EXEC_DIR} )


add_dependencies ( hpcc esdllib)

target_link_libraries( hpcc
    esdllib)