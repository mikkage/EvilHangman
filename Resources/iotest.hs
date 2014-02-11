import System.IO

main ::IO ()
main = do
	inpStr <- readFile "dictionary.txt"
	let s = words inpStr

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
	
	let out = filterDictionary l s
	writeFile "out.txt" out
	writeFile "outfiltered.txt" (filterLetter letter (lines out))

--------------------------------------------------
----------------Filter Dictionary-----------------
--Takes in an Int and list of Strings, and returns
--only the strings of that Int's length, separated
--by new lines in a single string.
--------------------------------------------------
filterDictionary :: Int -> [String] -> String
filterDictionary len (x:xs)
	| len == (length x) = x ++ "\n" ++ filterDictionary len xs
	| otherwise = "" ++ filterDictionary len xs
filterDictionary len [x]
	| len == (length x) = x
	| otherwise = ""
filterDictionary _ [] = ""


--------------------------------------------------
-------------------Filter Letter------------------
--Takes in a character and a list of strings, and
--returns a new string with words that do not
--contain that character in a new string, separated
--by new lines.
--------------------------------------------------
filterLetter :: Char -> [String] -> String
filterLetter letter (x:xs)
	| (elem letter x) == False = x ++ "\n" ++ filterLetter letter xs
	| otherwise = "" ++ filterLetter letter xs
filterLetter letter [x]
	| (elem letter x) == False = x
	| otherwise = ""
filterLetter _ [] = ""