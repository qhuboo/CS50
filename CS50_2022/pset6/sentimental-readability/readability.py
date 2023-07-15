from cs50 import get_string

# Prompts the user fot a text input
text = get_string("Text: ")

# Calculates the number of words in the text
words = len(text.split())

# Calculates the number of letters in the text
letters = 0
for char in text:
    if char.isalpha():
        letters += 1

# Calcualates the number of sentences in the text
sentences = text.count('.') + text.count('?') + text.count('!')

# Calculates the Coleman-Liau Index
L = letters * (100 / words)
S = sentences * (100 / words)
cl_index = int(round((0.0588 * L) - (0.296 * S) - 15.8, 0))

# Prints out the grade level
if cl_index > 15:
    print("Grade 16+")
elif cl_index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {cl_index}") 
