import math

TARGET = 10551264

total = 0;
for i in range(1, int(math.sqrt(TARGET))):
    if TARGET % i == 0:
        total += i + (TARGET / i)

print(total)
