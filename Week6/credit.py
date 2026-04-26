import re
from enum import Enum


class Card(Enum):
    """Enum that holds types of credit cards."""

    AMEX = 0
    MASTERCARD = 1
    VISA = 2
    INVALID = 3


AMEX_LENGTH = 15
AMEX_PATTERN = rf"^(34|37)\d{ ({AMEX_LENGTH - 2}) }$"

MC_LENGTH = 16
MC_PATTERN = rf"^(51|52|53|54|55)\d{ ({MC_LENGTH - 2}) }$"

VISA_LENGTH0 = 13
VISA_LENGTH1 = 16
VISA_PATTERN = rf"^(4\d{ ({VISA_LENGTH0 - 1}) }|4\d{ ({VISA_LENGTH1 - 1}) })$"


def match_card_type(digits: str) -> Card:
    # do something with regex to match the cards.
    # regex can match length too i think

    # if AMEX regex pattern return AMEX
    # 15 digits long, first 2 digits are 34 or 37
    if re.match(AMEX_PATTERN, digits):
        # something
        return Card.AMEX

    # if MASTERCARD pattern return MASTERCARD
    # 16 digits long, first 2 digits are 51, 52, 53, 54 or 55
    if re.match(MC_PATTERN, digits):
        return Card.MASTERCARD

    # if VISA pattern return VISA
    # 13 or 16 digits long, first digit is 4
    if re.match(VISA_PATTERN, digits):
        return Card.VISA

    # if it doesnt match return INVALID
    return Card.INVALID


def is_valid_cc(digits: str) -> bool:
    # do luhn checksum
    # if it matches return true
    checksum: int = 0
    try:
        for idx, digit in enumerate(reversed(digits), 1):
            # cast string to int so we can do maths
            # check if digit is even
            if idx % 2 == 0:
                doubled = str(int(digit) * 2)
                for digit_inner in reversed(doubled):
                    # add inner digit to checksum
                    checksum += int(digit_inner)
            else:
                checksum += int(digit)
    except ValueError:
        return False

    return checksum % 10 == 0


def main() -> None:
    user_card: str = input("Number: ").strip()

    # check if card is valid CC number
    card_type: Card = match_card_type(user_card)
    if card_type is Card.INVALID or not is_valid_cc(user_card):
        print(Card.INVALID.name)
        return

    print(card_type.name)


main()
