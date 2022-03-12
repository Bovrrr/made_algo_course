from sympy import nextprime


primeNumbers = []

prev = 2

# while prev < 1e6:
#     primeNumbers.append(nextprime(2 * prev))
#     prev = primeNumbers[-1]

# print(f"длина массива = {len(primeNumbers)}")

print(nextprime(150 * 1000))

# print("{" + ", ".join(list(map(str, primeNumbers))) + "}")
