import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")

    # Read database file into a variable
    # The list strs will contain all the Short Tandem Repeats contained
    # in the database file
    database = []
    strs = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for person in reader:
            database.append(person)
    # Populates the strs list
    for key in database[0].keys():
        strs.append(key)
    strs.remove('name')
 
    # Read DNA sequence file into a variable
    txt_file = open(sys.argv[2], "r")
    sequence = txt_file.read()
    txt_file. close()

    # Find longest match of each STR in DNA sequence
    # Createa dictionary where the keys are the STR
    # and the values are the repeat number of times
    # the STRs are found in the sequence
    str_count = {}
    for i in range(len(strs)):
        number = longest_match(sequence, strs[i])
        str_count[strs[i]] = number

    # Check database for matching profiles
    matches = 0
    for i in range(len(database)):
        count = 0
        for j in range(len(strs)):
            if int(database[i][strs[j]]) == (str_count[strs[j]]):
                count += 1
        if count == len(strs):
            matches += 1
            print(database[i]['name'])
            break
    if matches == 0:
        print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

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

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
