import random
with open('text', 'w', encoding='utf-8') as file:
    N = 500000
    file.write(str(N))
    file.write('\n')
    l1, l2, r1 = -1000000000, 1, 0
    r2 = random.randint(max(1, r1 * l2 // l1), 10**9)
    file.write(f"{l1} {l2} {r1} {r2}\n")
    s = set()
    for i in range(N):
        x, y = random.randint(-10**9, 10**9), 0
        while (x, y) in s:
            x, y = random.randint(-10**9, 10**9), 0
        s.add((x, y))
        file.write(f"{x} {y}\n")