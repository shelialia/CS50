import csv
import sys


def main():

    # TODO: Check for command-line usage
    # start counting the number of words from name of program, omit python
    if len(sys.argv) != 3:
        # program should work when "python dna.py databases/small.csv sequences/1.txt" is run
        print(f"python dna.py databases/filename.csv sequences/number.txt")
        # if there is an error, we exit
        sys.exit(1)

    # TODO: Read database file into a variable
    database = []
    # using "with" function, we do not need to close files
    # remember to write storing as what
    # use the sys header to access files written in command line arguments
    with open(sys.argv[1], "r") as file:
        database_reader = csv.DictReader(file)
        # after opening the csv file, tha data is stored in the form of a sequence of dictionarites
        # database: {'name': 'Alice', 'AGATC': '2', 'AATG': '8', 'TATC': '3'}
        #           {'name': 'Bob', 'AGATC': '4', 'AATG': '1', 'TATC': '5'}
        #           {'name': 'Charlie', 'AGATC': '3', 'AATG': '2', 'TATC': '5'}
        # hence, we can access the data by going to each row. we add each row to the database dictionaries, one row at a time
        for row in database_reader:
            database.append(row)

    # TODO: Read DNA sequence file into a variable
    text = sys.argv[2]
    with open(text, "r") as text_file:
        # use the .read() function
        dna_sequence = text_file.read()

    # TODO: Find longest match of each STR in DNA sequence

    # go through database first row using [0]
    # we access the headings ie. the name of the STRs using .keys()
    # make a list using list()
    # we slice off the rest of the list using string[x:y]
    # output of this list: subsequences = ['ATTR', 'AGPT', 'AATR']
    subsequences = list(database[0].keys())[1:]

    # make a dictionary using variable = {}
    # output of this dictionary stores: result = {'AATR' = 18, 'AGPT' = 20}
    result = {}

    # for each str in the list named subsequences,
    for subsequence in subsequences:
        # we store the name of subsequence (from the list) and number of str eg 18 (that is generated using the function longest_match) in the result dictionary
        # this is accessed as a pair of key and value parts
        # result subsequence goes to the eg AATR and then gets the integer there that is stored as value part
        result[subsequence] = longest_match(dna_sequence, subsequence)

    # TODO: Check database for matching profiles
    # loop through each row
    for row in database:
        # intialise matches to 0 for each person, as we want to check person by person
        matches = 0
        # loop through every STR in the list of STRs
        for subsequence in subsequences:
            # if the integer from dna sequence matches the integer in the database, we increment matches
            # convert the string to integer. because in each row, there exists strings.
            if result[subsequence] == int(row[subsequence]):
                matches += 1
        # if every value of STR repeats matches the DNA database value, we have found a matching person. we break out of the function
        if matches == len(subsequences):
            print(f"{row['name']}")
            break
    else:
        # else there are no matches
        print(f"No match")


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
