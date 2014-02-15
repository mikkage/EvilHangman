-- qsort
--   quicksort in 3 lines (not in place)
qsort :: (Ord a) => [a] -> [a]
qsort []     = []
qsort (x:xs) = qsort (filter (< x) xs) ++ [x] ++ qsort (filter (>= x) xs)

