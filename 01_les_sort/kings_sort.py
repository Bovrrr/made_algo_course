import re

num = int(input())
names = []
for i in range(num):
    names.append(input().split())

roman_to_arab = {
    "XL": 40,
    "IX": 9,
    "IV": 4,
    "L": 50,
    "X": 10,
    "V": 5,
    "I": 1,
}


def get_number(num: str) -> str:
    cnt = 0
    for roman_number, arab_number in roman_to_arab.items():
        cnt += len(re.findall(roman_number, num)) * arab_number
        num = num.replace(roman_number, "")
    if cnt < 10:
        return "0" + str(cnt)
    else:
        return str(cnt)


for name in names:
    name.append(get_number(name[1]))

for name in sorted(names, key=lambda x: x[0] + x[2]):
    print(name[0] + " " + name[1])
