#!/bin/bash

TEST_FILES=3.txt

grep 'FAIL' $TEST_FILES | sed 's/.*cat //' | sed '/FAIL/d' > temp.txt && mv temp.txt $TEST_FILES
cat $TEST_FILES | wc -l > temp.txt
COUNT_FILES=$(sed -n '1p' temp.txt)
rm temp.txt analysis/*

for ((i=1; i<=COUNT_FILES; i++))
do
    ./s21_cat $(sed -n "${i}p" $TEST_FILES) > analysis/s21_$i.txt
    cat $(sed -n "${i}p" $TEST_FILES) > analysis/default_$i.txt
    diff -a -y analysis/default_$i.txt analysis/s21_$i.txt > analysis/analys_fails_$i.txt
    rm analysis/default_$i.txt analysis/s21_$i.txt
done

for ((i=1; i<=COUNT_FILES; i++))
do
    echo "TEST: $i" >> analysis/all_analys.txt
    echo "options and files: $(sed -n "${i}p" $TEST_FILES)" >> analysis/all_analys.txt
    cat analysis/analys_fails_$i.txt >> analysis/all_analys.txt
    echo $'\n' >> analysis/all_analys.txt
done

rm 3.txt
cat analysis/all_analys.txt