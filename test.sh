#!/bin/bash


echo "\033[0;34m------------------------Importing map directory ...------------------------"
git clone https://github.com/42sommecaise/map.git mapstt && echo "\n"

echo "\033[0;32m------------------------Compiling ...------------------------"
#clang -Wall -Wextra -Werror map.c parcing.c libft/libft.a -o $1 && echo "\n"
make re
./$1 mapstt/map1.cub > txt1.txt
./$1 mapstt/map2.cub > txt2.txt
./$1 mapstt/map3.cub > txt3.txt
./$1 mapstt/map4.cub > txt4.txt
./$1 mapstt/map5.cub > txt5.txt
./$1 mapstt/map6.cub > txt6.txt
./$1 mapstt/map7.cub > txt7.txt
./$1 mapstt/map8.cub > txt8.txt
./$1 mapstt/map9.cub > txt9.txt
./$1 mapstt/map10.cub > txt10.txt
./$1 mapstt/map11.cub > txt11.txt
./$1 mapstt/map12.cub > txt12.txt
./$1 mapstt/map13.cub > txt13.txt
./$1 mapstt/map14.cub > txt14.txt
./$1 mapstt/map15.cub > txt15.txt
./$1 mapstt/map16cub > txt16.txt

echo "\033[0;36m------------------------Result------------------------"
echo "\033[0;35mcase 1 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt1.txt && echo "\n"
echo "\033[0;35mcase 2 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt2.txt && echo "\n"
echo "\033[0;35mcase 3 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt3.txt && echo "\n"
echo "\033[0;35mcase 4 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt4.txt && echo "\n"
echo "\033[0;35mcase 5 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt5.txt && echo "\n"
echo "\033[0;35mcase 6 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt6.txt && echo "\n"
echo "\033[0;35mcase 7 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt7.txt && echo "\n"
echo "\033[0;35mcase 8 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt8.txt && echo "\n"
echo "\033[0;35mcase 9 \033[0;36m>>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt9.txt && echo "\n"
echo "\033[0;35mcase 10 \033[0;36m>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt10.txt && echo "\n"
echo "\033[0;35mcase 11 \033[0;36m>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt11.txt && echo "\n"
echo "\033[0;35mcase 12 \033[0;36m>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt12.txt && echo "\n"
echo "\033[0;35mcase 13 \033[0;36m>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt13.txt && echo "\n"
echo "\033[0;35mcase 14 \033[0;36m>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt14.txt && echo "\n"
echo "\033[0;35mcase 15 \033[0;36m>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt15.txt && echo "\n"
echo "\033[0;35mcase 16 \033[0;36m>>>>>>>>>>>>>>>>>>\033[0;32m\n"
cat txt16.txt && echo "\n"

rm -rf mapstt
rm txt*.txt
