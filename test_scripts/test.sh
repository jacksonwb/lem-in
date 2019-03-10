./generator $1 > input.txt
time ./lem-in < input.txt | grep "L" | wc -l
cat input.txt | grep ":"