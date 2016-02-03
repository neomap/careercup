# !/usr/bin/python
# Filename while.py

number = 23
running = True
while running:
    guess = int(input("Enter an integer:"))

    if guess == number:
    	print("Congratulation, you guessed it!")
    	running = False
    elif guess < number:
        print("No, it's a little higher")
    else:
    	print("No, it's a little lower")
else:
	print(" the while loop is over.")

print("done")
