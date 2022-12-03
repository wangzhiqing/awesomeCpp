#use cppcheck
find .  -path ./build -prune -o  -name "*.cpp" -print | xargs cppcheck