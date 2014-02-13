import System.IO

main :: IO ()
main = do
	inpStr <- readFile "dictionary.txt"
	let s = words inpStr

	-- insane hangman graphics
	-- 6 files (0 - 5)
	-- hangman0 is start, hangman5 is end
	-- could add more if 5 guesses isnt enough
	inpStr <- readFile "hangman5.txt"
	let hangman = inpStr
	putStrLn hangman

	putStrLn "Enter the length of words to filter:"
	len <-getLine
	let l = read len :: Int

	putStrLn "Enter a character to filter out:"
	letter <- getChar
	
	let o = "Words of length " ++ len ++ " filtered out from dictionary.txt to out.txt"
	putStrLn o
	let o1 = "Shortest word length: " ++ show (minimum (map length s))
	putStrLn o1
	let o2 = "Longest word length: " ++ show (maximum (map length s))
	putStrLn o2
	
	let out = (filterDictionary l s)
	writeFile "out.txt" (unwords out)
	writeFile "outfiltered.txt" (unwords (filterLetter letter out))

--------------------------------------------------
----------------Filter Dictionary-----------------
--Takes in an Int and list of Strings, and returns
--only the strings of that Int's length, separated
--by new lines in a single string.
--------------------------------------------------
filterDictionary :: Int -> [String] -> [String]
filterDictionary len str = filter (checkStrLen len) str

-- checkStrLen
--   returns True if the length of the string argument is equal to the integer
--   argument, else False
checkStrLen :: Int -> String -> Bool
checkStrLen len str 
	| len == length str = True
	| otherwise         = False 

--------------------------------------------------
-------------------Filter Letter------------------
--Takes in a character and a list of strings, and
--returns a new list of strings that do not
--contain that letter.
--------------------------------------------------
filterLetter :: Char -> [String] -> [String]
filterLetter c str = filter (c `notElem`) str

--------------------------------------------------
-------------------Display Word-------------------
--Takes in two strings, the first being the word to
--be guessed and the second the list of letters that
--have been guessed by the user, and display either
--'-' for letters that have not been guessed or the
--letters of those which have been guessed.
--------------------------------------------------
displayWord :: String -> String -> String
displayWord (w:ws) guesses
	| (elem w guesses) == True = [w] ++ displayWord ws guesses
	| otherwise = "-" ++ displayWord ws guesses
displayWord [] _ = ""

-- qsort
--   quicksort in 3 lines (not in place)
qsort :: (Ord a) => [a] -> [a]
qsort []     = []
qsort (x:xs) = qsort (filter (< x) xs) ++ [x] ++ qsort (filter (>= x) xs)
