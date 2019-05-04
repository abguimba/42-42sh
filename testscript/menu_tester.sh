#!/bin/bash
cp ../42sh .
clear
select CHECK in "COMPIL 42sh" "REMOVE 42sh" "NORM EXPANSIONS" ALL SIMPLE ADVANCED EXIT
    do
        clear
        if [ "$CHECK" == "COMPIL 42sh" ]
            then
                cd ..
                make
                cd testscript
                cp ../42sh .
        fi
        if [ "$CHECK" == "REMOVE 42sh" ]
            then
                cd ..
                make fclean
                rm -r 42sh.dSYM
                cd testscript
                rm 42sh
                rm -r 42sh.dSYM
        fi
        if [ "$CHECK" == "NORM EXPANSIONS" ]
            then
                norminette ../srcs/expansions
        fi
        if  [ "$CHECK" == 'SIMPLE' ]
            then
                source menu_exp_simple.sh
        fi
        if [ "$CHECK" == 'ALL' ]
            then
                echo "------------------------------------------"
                echo "         test expansions simple         "
                source expansion_sim_~.sh
                source expansion_sim_\$.sh
                echo "------------------------------------------"
                echo "         test expansions advanced         "
                source expansion_adv_%.sh
                source expansion_adv_%\%.sh
                source expansion_adv_#.sh
                source expansion_adv_#\#.sh
                source expansion_adv_start#.sh
                source expansion_adv_+.sh
                source expansion_adv_\?.sh
                source expansion_adv_\=.sh
                source expansion_adv_\-.sh
        elif [ "$CHECK" == 'ADVANCED' ]
            then
                clear
                source menu_exp_advanced.sh
        elif [ "$CHECK" == 'EXIT' ]
            then
                exit
        fi
            sleep 1
            echo "\n\n"
            read -p "****PRESS RETURN KEY****"
            clear
            sh menu_tester.sh
            exit
    done