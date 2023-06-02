import math

a, b = input().split(" ")
a = int(a)
b = int(b)

p = int(input())
m = int(input())

l = math.ceil(math.log((b - a) * pow(10, p), 2))
d = (b - a) / pow(2, l)

for i in range(m):
    command = input()
    number = input()

    match command:
        case "TO":
            number = float(number)
            bin_str = ("0" * l)
            replace_str = bin(int((number-a)/d)).split('0b')[1]
            display_str = bin_str[:-len(replace_str)] + replace_str
            print(display_str)
        case "FROM":
            print(int(number.replace("0b", ""), 2)*d+a)
