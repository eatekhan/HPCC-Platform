#!/bin/bash

function _hpcc {
    local AVAILABLE_SERVICES="WsTopology WsExample"

    declare -A METHOD_MAPPING=(
        ["WsTopology"]="TpMachineQuery Ping"
    )


    COMPREPLY=()
    local SERVICE_NAME=${COMP_WORDS[COMP_CWORD]}
    local METHOD_NAME=${COMP_WORDS[1]}

    if [ "${COMP_CWORD}"  -eq 1 ]
    then
        COMPREPLY=($( compgen -W "$AVAILABLE_SERVICES" -- $SERVICE_NAME ))
    elif [[ -n "${METHOD_MAPPING[$METHOD_NAME]}" ]]
    then
        COMPREPLY=($( compgen -W "${METHOD_MAPPING[$METHOD_NAME]}" -- $SERVICE_NAME ))
    fi

}


complete -F _hpcc hpcc