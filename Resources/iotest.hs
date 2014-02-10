import System.IO
import Data.Char(toUpper)

main ::IO ()
main = do
	inpStr <- readFile "dictionary.txt"
	let s = words inpStr
	--writeFile "output.txt" (map toUpper inpStr)
	writeFile "out.txt" (filterDictionary 5 s)

filterDictionary :: Int -> [String] -> String
filterDictionary len (x:xs)
	| len == (length x) = x ++ "\n" ++ filterDictionary len xs
	| otherwise = "" ++ filterDictionary len xs
filterDictionary len [x]
	| len == (length x) = x
	| otherwise = ""
filterDictionary _ [] = ""