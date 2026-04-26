def count_string(prompt: str) -> tuple[int, int, int]:
    """Count the number of letters, words, and sentences in a given string."""
    letters = 0
    words = 0
    sentences = 0
    in_word = False
    # iterate through each character in the prompt
    for char in prompt:
        # check if the character is a letter
        if char.isalpha():
            # increment the letter count and set in_word to True
            letters += 1
            in_word = True
        # check if the character is a sentence-ending punctuation mark
        elif char in (".", "!", "?"):
            # increment the sentence count and set in_word to True
            sentences += 1
            in_word = True
        # check if the character is a whitespace character
        elif char.isspace():
            # if we are currently in a word, increment the word count and set in_word to False
            if in_word:
                in_word = False
                words += 1

    # if we ended the loop while still in a word, increment the word count
    if in_word:
        words += 1

    return letters, words, sentences


def coleman_liau(letters: int, words: int, sentences: int) -> int:
    """Calculate the Coleman-Liau index for a given number of letters, words, and sentences."""
    l_per_100 = (letters / words) * 100
    s_per_100 = (sentences / words) * 100
    return round(0.0588 * l_per_100 - 0.296 * s_per_100 - 15.8)


def main() -> None:
    prompt = input("Text: ")

    letters, words, sentences = count_string(prompt)

    cl_index: int = coleman_liau(letters, words, sentences)
    if cl_index < 1:
        print("Before Grade 1")
    elif cl_index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {cl_index}")


main()
