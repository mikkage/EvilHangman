import System.IO
import Data.Char(toUpper)

main ::IO ()
main = do
	inpStr <- readFile "dictionary.txt"
	let s = words inpStr
	putStrLn "Enter the length of words to filter:"
	len <-getLine
	let l = read len :: Int
	let o = "Words of length " ++ len ++ " filtered out from dictionary.txt to out.txt"
	putStrLn o
	let o1 = "Shortest word length: " ++ show (minimum (map length s))
	putStrLn o1
	let o2 = "Longest word length: " ++ show (maximum (map length s))
	putStrLn o2
	writeFile "out.txt" (filterDictionary l s)

filterDictionary :: Int -> [String] -> String
filterDictionary len (x:xs)
	| len == (length x) = x ++ "\n" ++ filterDictionary len xs
	| otherwise = "" ++ filterDictionary len xs
filterDictionary len [x]
	| len == (length x) = x
	| otherwise = ""
filterDictionary _ [] = ""