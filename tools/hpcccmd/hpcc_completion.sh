#!/bin/bash

function _hpcc {
    local AVAILABLE_SERVICES=$(/home/khan/HPCC-Platform/build/Debug/bin/hpcc --printServices)

    
    


    COMPREPLY=()
    local CURRENT_WORD=${COMP_WORDS[COMP_CWORD]}
    local SERVICE_NAME=${COMP_WORDS[1]}

    

    if [ "${COMP_CWORD}"  -eq 1 ]
    then
        COMPREPLY=($( compgen -W "$AVAILABLE_SERVICES" -- $CURRENT_WORD ))
    elif [[ "${COMP_CWORD}" -eq 2 ]]
    then
        local METHODS=$(/home/khan/HPCC-Platform/build/Debug/bin/hpcc $SERVICE_NAME --printMethods)
        if [ -n "$METHODS" ]; then
            COMPREPLY=($(compgen -W "$METHODS" -- $CURRENT_WORD))
        fi
    fi

}



complete -F _hpcc ./hpcc