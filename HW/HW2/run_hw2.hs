import HW2

import System.Environment

-- entry point for the program
main :: IO ()
main = do
    args <- getArgs
    case args of
        [] -> do
            input <- getContents
            putStr (computeGpas input)
        [infile] -> do
            input <- readFile infile
            putStr (computeGpas input)
        [infile,outfile] -> do
            input <- readFile infile
            writeFile outfile (computeGpas input)
        _ -> putStrLn "usage: ./hw2 [infile [outfile]]"