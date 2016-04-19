delay=1

clear && \
   g++ *.cpp -lwiringPi -std=c++11 && \
   echo "Staring in ${delay}" && \
   sleep ${delay} && \
   time sudo ./a.out
