# first prompt the user for the half-pyramid's height, a positive integer. 1 >= 8
# If the user fails to provide a positive integer no greater than 8, you should re-prompt
# Then, generate (with the help of print and one or more loops) the desired half-pyramids.
# align the bottom-left corner of your pyramid with the left-hand edge of your terminal window,
# ensure that there are two spaces between the two pyramids,
# and no additional spaces after the last set of hashes on each row.

MAX_HEIGHT: int = 8
MIN_HEIGHT: int = 1


user_height = 0
while user_height < MIN_HEIGHT or user_height > MAX_HEIGHT:
    try:
        user_height = int(input("Height: "))
    except ValueError:
        continue
# loop as many times as the height the user entered
for idx in range(1, user_height + 1):
    # use an f string and string formatting to align and basically one liner this
    print(f"{('#' * idx):>{user_height}}  {('#' * idx)}")
