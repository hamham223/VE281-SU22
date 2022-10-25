g++ -o generate generate.cpp
g++ -o 1/main 1/main.cpp
g++ -o 2/main 2/main.cpp
echo "\033[33m Compiled successfully! Running! \033[0m"
for i in 1 2 3 4 5
do
    echo "\033[36m round ${i} \033[0m"
    ./generate
    rm -f out1
    rm -f out2
    1/main > out1
    2/main > out2
    if !(diff out1 out2 > diff); then 
        echo "\033[31m Wrong Answer! \033[0m"; exit;
    else echo "\033[32m Accepted! \033[0m";
    fi 
done
