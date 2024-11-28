#!/bin/bash

SUCCESS=0
FAIL=0
TEST_NUMBER=0
DIFF_RES=""
MAIN_OPTIONS="b e E n t T s v"
RED=`tput setaf 1`
GREEN=`tput setaf 2`
BASE=`tput setaf 7`

declare -a files=(    
     "VAR tests/tests_files/char.txt"
     "VAR tests/tests_files/test_case_cat.txt"
     "VAR tests/tests_files/test_1_cat.txt"
     "VAR tests/tests_files/test_2_cat.txt"
     "VAR tests/tests_files/test_3_cat.txt"
     "VAR tests/tests_files/test_4_cat.txt"
     "VAR tests/tests_files/test_5_cat.txt"
     "VAR tests/tests_files/test_6_cat.txt"
     "VAR tests/tests_files/test_1_cat.txt tests/tests_files/test_2_cat.txt"
     "VAR tests/tests_files/test_1_cat.txt tests/tests_files/char.txt tests/tests_files/test_2_cat.txt"
     "VAR tests/tests_files/test_1_cat.txt tests/tests_files/test_case_cat.txt tests/tests_files/test_2_cat.txt"
     "VAR tests/tests/nofile.txt"
     "VAR tests/tests_files/test_1_cat.txt tests/tests_files/nofile.txt"
     "VAR tests/tests_files/test_1_cat.txt tests/tests_files/nofile.txt tests/tests_files/test_2_cat.txt"
)

testing() {
    t=$(echo $@ | sed "s/VAR/$var/")
    ./s21_cat $t > tests/tests_log/${TEST_NUMBER}_test_s21_cat.log
    cat $t > tests/tests_log/${TEST_NUMBER}_test_sys_cat.log
    SHA1=`cat tests/tests_log/${TEST_NUMBER}_test_s21_cat.log | sha256sum`
    SHA2=`cat tests/tests_log/${TEST_NUMBER}_test_sys_cat.log | sha256sum`

    if [[ $SHA1 == $SHA2 ]]
    then
      (( SUCCESS++ ))
        RESULT="SUCCESS"
        echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAIL}${BASE}] ${GREEN}${RESULT}${BASE} cat $t"

    else
      (( FAIL++ ))
        RESULT="FAIL"
        echo "[${GREEN}${SUCCESS}${BASE}/${RED}${FAIL}${BASE}] ${RED}${RESULT}${BASE} cat $t"

    fi
}

for var1 in $MAIN_OPTIONS
do
    for i in "${files[@]}"
    do
        var="-$var1"
        testing "$i"
    done
done

for var1 in $MAIN_OPTIONS
do
    for var2 in $MAIN_OPTIONS
    do
        if [ $var1 != $var2 ]
        then
            for i in "${files[@]}"
                do
                    var="-$var1 -$var2"
                    testing "$i"
                done
        fi                        
    done
done


for var1 in $MAIN_OPTIONS
do
    for var2 in $MAIN_OPTIONS
    do
        for var3 in $MAIN_OPTIONS
        do
            if [ $var1 != $var2 ] && [ $var1 != $var3 ] && [ $var2 != $var3 ]
            then
                for i in "${files[@]}"
                    do
                        var="-$var1 -$var2 -$var3"
                        testing "$i"
                    done
            fi                        
        done
    done
done

for var1 in $MAIN_OPTIONS
do
    for var2 in $MAIN_OPTIONS
    do
        for var3 in $MAIN_OPTIONS
        do
            for var4 in $MAIN_OPTIONS
            do
                if [ $var1 != $var2 ] && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                && [ $var2 != $var3 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
                then
                    for i in "${files[@]}"
                        do
                          var="-$var1 -$var2 -$var3 -$var4"
                          testing "$i"
                        done
                fi                        
            done
        done
    done
done

for var1 in $MAIN_OPTIONS
do
    for var2 in $MAIN_OPTIONS
    do
        for var3 in $MAIN_OPTIONS
        do
            for var4 in $MAIN_OPTIONS
            do
                for var5 in $MAIN_OPTIONS
                do
                    if [ $var1 != $var2 ] && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                    && [ $var1 != $var5 ] && [ $var2 != $var3 ] && [ $var2 != $var4 ] \
                    && [ $var2 != $var5 ] && [ $var3 != $var4 ] && [ $var3 != $var5 ] \
                    && [ $var4 != $var5 ] 
                    then
                        for i in "${files[@]}"
                        do
                            var="-$var1 -$var2 -$var3 -$var4 -$var5"
                            testing "$i"
                        done
                    fi                        
                done
            done
        done
    done
done

for var1 in $MAIN_OPTIONS
do
    for var2 in $MAIN_OPTIONS
    do
        for var3 in $MAIN_OPTIONS
        do
            for var4 in $MAIN_OPTIONS
            do
                for var5 in $MAIN_OPTIONS
                do
                    for var6 in $MAIN_OPTIONS
                    do
                        if [ $var1 != $var2 ] && [ $var1 != $var3 ] && [ $var1 != $var4 ] \
                        && [ $var1 != $var5 ] && [ $var1 != $var6 ] && [ $var2 != $var3 ] \
                        && [ $var2 != $var4 ] && [ $var2 != $var5 ] && [ $var2 != $var6 ] \
                        && [ $var3 != $var4 ] && [ $var3 != $var5 ] && [ $var3 != $var6 ] \
                        && [ $var4 != $var5 ] && [ $var4 != $var6 ] && [ $var5 != $var6 ]
                        then
                            for i in "${files[@]}"
                            do
                                var="-$var1 -$var2 -$var3 -$var4 -$var5 -$var6"
                                testing "$i"
                            done
                        fi                        
                    done
                done
            done
        done
    done
done

echo "${RED}FAIL: ${FAIL}${BASE}"
echo "${GREEN}SUCCESS: ${SUCCESS}${BASE}"