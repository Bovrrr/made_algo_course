from sympy import nextprime


primeNumbers = []

prev = 97 + 26 + 1

# while prev < 1e6:
#     primeNumbers.append(nextprime(2 * prev))
#     prev = primeNumbers[-1]

# print(f"длина массива = {len(primeNumbers)}")

print(nextprime(prev))

# print("{" + ", ".join(list(map(str, primeNumbers))) + "}")
