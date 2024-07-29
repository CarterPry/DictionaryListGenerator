# Dictionary Wordlist Generator
This C script generates every possible combination of words from the wordlist file you give. It's designed to help create a lengthy wordlists in case you have an idea of what might be in a password hash, but not totally sure on specifics. 

## Prerequisites
- GCC compiler for compiling the C code.
- A Linux terminal environment preferred.

## Usage

1. **Compile the Script**

   Open your Linux terminal and cd to the directory with the script. Compile the script using the GCC compiler with this command:
   `bash
   gcc -o wordlistGenerator listGenerator.c
   `

2. **Run the Script**

   Once compiled, you need to execute the script with the following command:
   `bash
   ./wordlistGenerator <wordlist.txt>
   `
   - `wordlist.txt`: The path to your input wordlist file.

3. **Choose an option**

   The script will then prompt you to choose how to handle uppercase and lowercases of the new list you're creating
   - **Option 1**: Includes only the words as they appear in the original wordlist.
   - **Option 2**: Includes the words as they are, plus variations with the first letter in both uppercase and lowercase for all words.

