# !/bin/bash

to_build_file=$1

echo "building: "$to_build_file
g++ $to_build_file
#gcc hello_world.cpp -lstdc++ -o a.out