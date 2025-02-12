from string import ascii_lowercase, ascii_uppercase, digits

def find_kernel(p: int) -> list[str]:
    symbols = list(digits) + list(ascii_uppercase) + list(ascii_lowercase) # list of symbols
    g = lambda si: ord(si) - ord('a') + 1

    kernel = []

    for i in range(len(symbols) - 1):
        for j in range(i + 1, len(symbols)):
            if -g(symbols[i]) == g(symbols[j]) * p:
                kernel.append(symbols[i] + symbols[j])
            if -g(symbols[j]) == g(symbols[i]) * p:
                kernel.append(symbols[j] + symbols[i])

    return kernel

for p in range(-10000, 32):
    ker = find_kernel(p)
    if ker:
        print(p, ker)