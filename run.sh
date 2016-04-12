delay=1

clear && \
   g++ *.cpp *.h -lwiringPi -std=c++11 && \
   echo "Staring in ${delay}" && \
   sleep ${delay} && \
   time sudo ./a.out
