SUCCESS="\033[1;32m\t\tSUCCESS\033[1;37m"
ERROR="\033[1;31m\t\t****ERROR****\033[1;37m"
echo "                    #*                     "
echo "echo \${#HOME}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#HOME}" | ./42sh)
CMD_BASH=$(echo "echo \${#HOME}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "echo \${#*HOME}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#*HOME}" | ./42sh)
CMD_BASH=$(echo "echo \${#*HOME}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "echo \${#HOME*}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#HOME*}" | ./42sh)
CMD_BASH=$(echo "echo \${#HOME*}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${#lolo}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#lolo}" | ./42sh)
CMD_BASH=$(echo "echo \${#lolo}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${#*lolo}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#*lolo}" | ./42sh)
CMD_BASH=$(echo "echo \${#*lolo}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${#lolo*}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#lolo*}" | ./42sh)
CMD_BASH=$(echo "echo \${#lolo*}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${#}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#}" | ./42sh)
CMD_BASH=$(echo "echo \${#}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
        echo "$CMD_42sh"
        echo "$CMD_BASH"
fi
sleep 0.5
echo "------------------------------------------"
echo "echo \${#*}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${#*}" | ./42sh)
CMD_BASH=$(echo "echo \${#*}" | /bin/bash)
if [ $CMD_42sh == $CMD_BASH ]
    then
        echo $SUCCESS
else
        echo $ERROR
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