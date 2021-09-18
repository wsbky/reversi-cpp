import pyperclip

f = open("./input.txt", "r")
input = f.read()
f.close()

black = 0
white = 0

input = "".join(input.splitlines())[::-1]

for i in range(64):
    if input[i] == "o":
        black |= (1 << i)
    elif input[i] == "x":
        white |= (1 << i)

output = "0x" + str(hex(black)).replace("0x", "").zfill(16) + ", 0x" + str(hex(white)).replace("0x", "").zfill(16)

pyperclip.copy(output)

print(output)
