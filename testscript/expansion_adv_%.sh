SUCCESS="\033[1;32m\t\tSUCCESS\033[1;37m"
ERROR="\033[1;31m\t\t****ERROR****\033[1;37m"
echo "                    *%*                   "
echo "echo \${HOME%se}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${HOME%se}" | ./42sh)
CMD_BASH=$(echo "echo \${HOME%se}" | /bin/bash)
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
echo "echo \${HOME%*se}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${HOME%*se}" | ./42sh)
CMD_BASH=$(echo "echo \${HOME%*se}" | /bin/bash)
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
echo "echo \${HOME%se*}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${HOME%se*}" | ./42sh)
CMD_BASH=$(echo "echo \${HOME%se*}" | /bin/bash)
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
echo "echo \${HOME%/}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${HOME%/}" | ./42sh)
CMD_BASH=$(echo "echo \${HOME%/}" | /bin/bash)
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
echo "echo \${HOME%*/}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${HOME%*/}" | ./42sh)
CMD_BASH=$(echo "echo \${HOME%*/}" | /bin/bash)
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
echo "echo \${HOME%/*}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${HOME%/*}" | ./42sh)
CMD_BASH=$(echo "echo \${HOME%/*}" | /bin/bash)
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
echo "echo \${HOME%lo}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${HOME%lo}" | ./42sh)
CMD_BASH=$(echo "echo \${HOME%lo}" | /bin/bash)
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
echo "echo \${PEPE%lo}"
echo "------------------------------------------"
CMD_42sh=$(echo "echo \${PEPE%lo}" | ./42sh)
CMD_BASH=$(echo "echo \${PEPE%lo}" | /bin/bash)
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