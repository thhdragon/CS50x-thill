import csv
import sys
from collections.abc import Sequence
from pathlib import Path

VALID_ARG_COUNT = 3


def match_individual(database: list, counts: dict) -> str | None:
    # iterate through the list of dictionaries
    for data in database:
        if counts.items() <= data.items():
            return data["name"]

    return None


def calculate_longest_matches(sequence: str, labels: Sequence[str]) -> dict:
    counts = {}
    for label in labels:
        result = longest_match(sequence, label)
        # so we dont compare ints and str
        counts[label] = str(result)

    return counts


def main() -> None:
    sys.argv.append("databases/large.csv")
    sys.argv.append("sequences/5.txt")

    # Check for command-line usage
    # print an error if program started with incorrect number of cli args
    # get amount of arguments passed in
    arg_count: int = len(sys.argv)
    if arg_count != VALID_ARG_COUNT:
        print(
            f"This program takes {VALID_ARG_COUNT} arguments: the python file, csv file, and txt.\n"
            f"User input of {arg_count} argument(s) is incorrect",
        )
        return
    # sys.argv[1] = name of a CSV file containing the STR counts for a list of individuals
    databases_path: Path = Path(sys.argv[1])
    # sys.argv[2] = name of a txt file containing the DNA sequence to identify.
    sequences_path: Path = Path(sys.argv[2])

    # Read database file into a variable
    # open the CSV file and read its contents into memory.
    with databases_path.open(mode="r") as dbp:
        # use the csv module to read the CSV file and store its contents in a variable
        reader: csv.DictReader[str] = csv.DictReader(dbp)
        if reader.fieldnames is None:
            return
        # the first row of the CSV file contains the column labels
        # read it into a variable using the fieldnames attribute of the csv.DictReader object
        # slice off the first element (the name column)
        labels: Sequence[str] = reader.fieldnames[1:]
        # the rest of the CSV file contains the STR counts for each individual
        database: list = list(reader)

    # Read DNA sequence file into a variable
    sequence: str = sequences_path.read_text()

    # Find longest match of each STR in DNA sequence

    counts = calculate_longest_matches(sequence, labels)

    # # Check database for matching profiles
    # # If the STR counts match any of the individuals in the CSV file,
    result: str | None = match_individual(database, counts)
    if result is None:
        # print No match
        print("No match")
    else:
        # print out the name of the matching individual.
        print(result)
    return


def longest_match(sequence: str, subsequence: Sequence[str]) -> int:
    """Return length of longest run of subsequence in sequence."""
    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
