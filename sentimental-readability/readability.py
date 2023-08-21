# TODO

from cs50 import get_string

letters = 0
words = 1
sentences = 0

text = get_string("Text: ")

# use the python function len(), isalpha() and isspace()
for i in range(len(text)):
    if text[i].isalpha():
        letters += 1
    elif text[i].isspace():
        words += 1
    elif text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# use the python function float()
l = letters / words * 100
L = float(l)
s = sentences / words * 100
S = float(s)

# use the python function round()
index = round(0.0588 * L - 0.296 * S - 15.8)

if index > 15:
    print(f"Grade 16+")
elif index < 1:
    print(f"Before Grade 1")
else:
    print(f"Grade {index}")
