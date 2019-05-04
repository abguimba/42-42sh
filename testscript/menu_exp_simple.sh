select CHECK in ALL "*~*" "\$*" RETURN EXIT
    do
        clear
        echo "------------------------------------------"
        echo "         test expansions simple           "
        if [ "$CHECK" == 'ALL' ] ||
           [ "$CHECK" == "*~*" ]
            then
                source expansion_sim_\~.sh
        fi
        if [ "$CHECK" == 'ALL' ] ||
           [ "$CHECK" == "\$*" ]
            then
                source expansion_sim_\$.sh
        elif [ "$CHECK" == 'RETURN' ]
            then
                clear
                sh menu_tester.sh
                exit
        elif [ "$CHECK" == 'EXIT' ]
            then
                exit
        fi
                sleep 1
                echo "\n\n"
                read -p "****PRESS ANY KEY****"
                clear
                source menu_exp_simple.sh
    done
