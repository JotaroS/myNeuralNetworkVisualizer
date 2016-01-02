g++ main.cpp -o main -std=c++11
rm ./outimage/*
./main
python csvtopng.py
