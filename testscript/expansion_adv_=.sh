SUCCESS="\033[1;32m\t\tSUCCESS\033[1;37m"
ERROR="\033[1;31m\t\t****ERROR****\033[1;37m"
TEST="HOME:="
echo "                   *:=*                    "
echo "echo \${$TEST}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${$TEST}" | ./42sh)
CMD_BASH=$(echo "echo \${$TEST}" | /bin/bash)
echo "TEST1:"
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
echo "TEST2:"
TEST2="HOME="
CMD_42sh=$(echo "\${$TEST} ; set | grep $TEST2" | ./42sh)
CMD_BASH=$(echo "\${$TEST} ; set | grep $TEST2" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo "$SUCCESS" 
        echo "ENVAR OR SETVAR IS SETED CORRECTLY"
else
        echo "$ERROR"
        echo "ENVAR OR SETVAR IS NOT SETED CORRECTLY"
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="HOME:=test"
echo "------------------------------------------"
echo "echo \${$TEST}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${$TEST}" | ./42sh)
CMD_BASH=$(echo "echo \${$TEST}" | /bin/bash)
echo "TEST1:"
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
echo "TEST2:"
TEST2="HOME="
CMD_42sh=$(echo "\${$TEST} ; set | grep $TEST2" | ./42sh)
CMD_BASH=$(echo "\${$TEST} ; set | grep $TEST2" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo "$SUCCESS" 
        echo "ENVAR OR SETVAR IS SETED CORRECTLY"
else
        echo "$ERROR"
        echo "ENVAR OR SETVAR IS NOT SETED CORRECTLY"
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="KK:=test"
echo "------------------------------------------"
echo "echo \${$TEST}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${$TEST}" | ./42sh)
CMD_BASH=$(echo "echo \${$TEST}" | /bin/bash)
echo "TEST1:"
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
echo "TEST2:"
TEST2="KK="
CMD_42sh=$(echo "\${$TEST} ; set | grep $TEST2" | ./42sh)
CMD_BASH=$(echo "\${$TEST} ; set | grep $TEST2" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo "$SUCCESS" 
        echo "ENVAR OR SETVAR IS SETED CORRECTLY"
else
        echo "$ERROR"
        echo "ENVAR OR SETVAR IS NOT SETED CORRECTLY"
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST=":=test"
echo "------------------------------------------"
echo "echo \${$TEST}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${$TEST}" | ./42sh)
CMD_BASH=$(echo "echo \${$TEST}" | /bin/bash)
echo "TEST1:"
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
echo "TEST2:"
TEST2="=test"
CMD_42sh=$(echo "\${$TEST} ; set | grep $TEST2" | ./42sh)
CMD_BASH=$(echo "\${$TEST} ; set | grep $TEST2" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo "$SUCCESS" 
        echo "ENVAR OR SETVAR IS SETED CORRECTLY"
else
        echo "$ERROR"
        echo "ENVAR OR SETVAR IS NOT SETED CORRECTLY"
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST=":=HOME"
echo "------------------------------------------"
echo "echo \${$TEST}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${$TEST}" | ./42sh)
CMD_BASH=$(echo "echo \${$TEST}" | /bin/bash)
echo "TEST1:"
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
TEST2="=HOME"
CMD_42sh=$(echo "\${$TEST} ; set | grep $TEST2" | ./42sh)
CMD_BASH=$(echo "\${$TEST} ; set | grep $TEST2" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo "$SUCCESS" 
        echo "ENVAR OR SETVAR IS SETED CORRECTLY"
else
        echo "$ERROR"
        echo "ENVAR OR SETVAR IS NOT SETED CORRECTLY"
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
TEST="HOME:=\$PWD"
echo "------------------------------------------"
echo "echo \${$TEST}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${$TEST}" | ./42sh)
CMD_BASH=$(echo "echo \${$TEST}" | /bin/bash)
echo "TEST1:"
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
TEST2="HOME="
CMD_42sh=$(echo "\${$TEST} ; set | grep $TEST2" | ./42sh)
CMD_BASH=$(echo "\${$TEST} ; set | grep $TEST2" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo "$SUCCESS" 
        echo "ENVAR OR SETVAR IS SETED CORRECTLY"
else
        echo "$ERROR"
        echo "ENVAR OR SETVAR IS NOT SETED CORRECTLY"
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
#echo "-----------------------------------------"
#echo "test autre"
#echo "-----------------------------------------"
#echo "echo '$HOME'" | ./42sh
#echo "echo '$HOME'" | /bin/bash
#echo "-----------------------------------------"