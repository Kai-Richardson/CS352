import HW5

import System.Environment

-- runs parseRecord on each line of the file and concatenates the results
parseAllRecords :: String -> String
parseAllRecords inp = unlines (map (show . parseRecord) (lines inp))

-- entry point for the program
main :: IO ()
main = do
    args <- getArgs
    case args of
        [] -> do
            input <- getContents
            putStr (parseAllRecords input)
        [infile] -> do
            input <- readFile infile
            putStr (parseAllRecords input)
        [infile,outfile] -> do
            input <- readFile infile
            writeFile outfile (parseAllRecords input)
        _ -> putStrLn "usage: ./hw5 [infile [outfile]]"