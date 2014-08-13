# Michael Parker
# 8/13/2014
# 
# Evil Hangman is a twist on the classic game of Hangman in which the computer will cheat in attempt
# to make sure it's very difficult to win, without you ever knowing. This is done by loading the entire
# dictionary, and changing the word based on the user's guesses. 


#### BEGIN HELPER FUNCTIONS ####

#### filter_by_length ####
# Creates a new dictionary with only words of the correct length
#
# dict - The current dictionary
# len - The length of the words to be contained in the new dictionary
#
# Returns a new dictionary with only words of a certain length
def filter_by_length(dict, len)
	filtered_dict = []
	dict.each {
		|x|
		if x.length == len
			filtered_dict += [x]
		end
	}
	return filtered_dict
end

#### filter_by_letter ####
# Creates a new dictionary that only contains words that do not contain the given letter
#
# dict - The current dictionary
# letter - The letter that cannot be in any of the words in the new dictionary
#
# Returns a new dictionary containing only words that do not have the letter
def filter_by_letter(dict, letter)
	filtered_dict = []
	dict.each {
		|x|
		if !x.include? letter
			filtered_dict += [x]
		end
	}
	return filtered_dict
end

#### filter_by_position ####
# Filters out words that do not fit the revealed word pattern
# Ex: If the word is -oo-, all words that do not have two 'o's in the same positions
# will be removed from the dictionary
#
# guesses - The list of all characters guessed so far
# word - The current word, covered
# dict - The current dictionary
#
# Returns a new dictionary containing words that match the pattern of the covered up word
def filter_by_position(guesses, word, dict)
	temp_dict = []
	dict.each {
		|x|
		if string_compare(x, word, guesses)
			temp_dict += [x]
		end
	}
	return temp_dict
end

#### string_compare ####
# Used by filter_by_position to determine whether a word will fit the pattern of the current word
#
# word - The current word, uncovered
# word_covered - The current word, covered
# guesses - The list of all characters guessed so far
# 
# Returns a new dictionary of words that fit the pattern
def string_compare(word, word_covered, guesses)
	for i in 0..word.split("").length
		# If at any point the covered word has a '-' and the uncovered word has a letter that
		# has already been guessed, it cannot be used, so return false
		if (word_covered[i] == "-") && (guesses.include? word[i])
			return false
		end

		# If at any point the covered word and uncovered word do not have the same character at the same index,
		# and the current letter in the covered word is '-', then the positions do not match, so return false
		if (word[i] != word_covered[i]) && (word_covered[i] != "-")
			return false
		end
	end
	# If the for loop has ended without returning false, then all of the letters that can be seen by the player
	# match the word, so it can be used in the new dictionary
	return true
end

#### get_covered_word ####
# Creates a new string that is used to show the user the current word, with unguessed characters covered
# Ex: If the word is 'foobar' and the letters 'o' and 'a' have been guessed, it will return the string "-oo-a-"
#
# word - The current word
# guesses - The list of all characters guessed so far
#
# Returns a string with the covered up word
def get_covered_word (word, guesses)
	word_covered = []
	word.split("").each {
		|x|
		if guesses.include? x
			word_covered += [x]
		else word_covered += ['-']
		end
	}
	return word_covered.join("")
end

#### make_guess ####
# Takes user input for guessing a letter
#
# guesses - The list of all characters guessed so far
#
# Returns the character guessed, once valid input has been entered
def make_guess(guesses)
	puts "Enter your guess"
	guess = gets.chomp
	guess = guess.downcase

	# Make sure the guess is a single letter
	if !guess =~ /[a-z]/ || guess.length > 1
		puts "Not a letter. Guess again.\n"
		make_guess(guesses)
	else
		# If the guess is a single letter, then we just need to be sure it has not been guessed already
		if !guesses.include? guess
			# If the letter has not been guessed, we have reached a valid input and can return the letter
			return guess
		else
			# If the letter has already been guessed, print the list of guesses so far and try again
			puts "Letter alread guessed. Guess again.\n"
			puts "Currently guessed: " + guesses.join("")
			return make_guess(guesses)
		end
	end
end

#### END HELPER FUNCTIONS ####

# Number of attempts player gets to guess the word
NUMBER_OF_GUESSES = 10

# Original, unchanged dictionary
dict_original = File.read("hangmandata.txt").split("\n")

continue = 'y'
while continue == 'y'
	# Word length input
	begin
		puts "Enter the length of the word you want to guess"
		word_length = gets.chomp.to_i
		if word_length <2 || word_length > 30
			puts "Invalid input. Make sure the number is actually a number, and is >1 and <30"
			redo
		end
	end

	# Set up guesses list and number of guesses before entering the main game loop
	guesses = []
	guesses_remaining = NUMBER_OF_GUESSES

	# Remove all words of the wrong length from the dictionary, and set the word to the first word in
	# the dictionary
	dict = filter_by_length(dict_original, word_length)
	puts get_covered_word(dict.first, guesses)

	# Main game loop - runs until the player has 0 or fewer guesses remaining, or the player gets the word right.
	until guesses_remaining < 1 do
		puts "\n"
		puts "You have " + guesses_remaining.to_s + " guesses remaining"
		puts "Currently guessed: " + guesses.join("")
		# Get guess from player, then add it to the list of guessed letters
		guessed_char = make_guess(guesses)
		guesses += [guessed_char]

		word_hidden = get_covered_word(dict.first, guesses)

		# Temporary dictionary, used to make sure that the filtered dictionary is not empty
		temp_dict = []

		# Filter out all words containing the letter that the player guessed.
		temp_dict = filter_by_letter(dict, guessed_char) 
		if temp_dict != []
			# As long as the resulting dictionary is not empty, we can use any of the words in the dictionary without
			# the player knowing we're cheating
			dict = temp_dict
		end

		# Update current word after previous filter
		word = dict.first

		# Do the same process as filtering by letter as above, but this time filter by position of exposed letters
		temp_dict = filter_by_position(guesses, word_hidden, dict)
		if temp_dict != []
			dict = temp_dict
		end

		# Update word and show results to user
		word = dict.first
		word_hidden = get_covered_word(word, guesses)
		puts word_hidden

		# If the guessed character is shown to the user, then they guessed a letter correctly and don't lose a turn
		if word_hidden.include? guessed_char
			guesses_remaining += 1
		end

		# Check to see if there are any '-' in the word shown to the user. If there are none, then the player has won
		if !word_hidden.include? '-'
			puts "You win... this time."
			break
		end

		# If the player has not won, take away a guess and start the loop again
		guesses_remaining -= 1
	end

	# If the loop has ended and the player has 0 or fewer guesses, they have lost.
	if guesses_remaining < 1
		puts "You lose - The word was: " + word
	end

	puts "Play again? (y/n)"
	continue = gets.chomp.downcase
end
