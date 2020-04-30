module HW2 (
    ClassRecord,
    StudentRecord,
    computeGpas,
    splitLines,
    parseRecord,
    sortAndGroupRecords,
    calcGpa,
    formatRecord
    ) where

import Data.List
import Numeric
import Text.Printf

-- Starter code for CS 352 HW 2 (see accompanying PDF for behaviour)
-- Author: Aaron Moss (based on design by Steve Vegdahl)

-- Single line record of input
type ClassRecord = (String,Int,String,Int,String,Double)

-- Final record for a student
type StudentRecord = (String,Double,Int)

-- Record for associated gpa to credits
type AssocGPA = (Double, Int)

-- Implements top-level conversion from input to output file
computeGpas :: String -> String
computeGpas input = do
    let outputStr = map formatRecord (map calcGpa (sortAndGroupRecords (map parseRecord (splitLines input))))
    (printf "%32s  %-s  %-s" ("NAME") ("GPA") (" #")) ++ "\n" ++ (unlines outputStr)

-- Splits input into a list of lines
splitLines :: String -> [String]
splitLines s = lines s

-- Parses input line into record
parseRecord :: String -> ClassRecord
parseRecord line = do
    let list = words line
    let name = list!!5 ++ ", " ++ list!!4
    (list!!0, readAsInt (list!!1), list!!2, readAsInt (list!!3), name, gradeToNum (list!!6))

-- Reads a string as an integer
readAsInt :: String -> Int
readAsInt str = read str :: Int

-- Converts a String grade to the numeric representation
gradeToNum :: String -> Double
gradeToNum str =
    case str of
        "A+" -> 4.3
        "A"  -> 4.0
        "A-" -> 3.7
        "B+" -> 3.3
        "B" -> 3.0
        "B-" -> 2.7
        "C+" -> 2.3
        "C" -> 2.0
        "C-" -> 1.7
        "D+" -> 1.3
        "D" -> 1.0
        "D-" -> 0.7
        _ -> 0.0

-- Sorts & Groups list of records by name
sortAndGroupRecords :: [ClassRecord] -> [[ClassRecord]]
sortAndGroupRecords records = do
    let sorted = sortRecords records
    groupBy (equalName) sorted

-- Sorts ClassRecords by their fifth element(name)
sortRecords :: [ClassRecord] -> [ClassRecord]
sortRecords recd = sortOn fth recd

-- Calculates the GPA for a single student given their course list
calcGpa :: [ClassRecord] -> StudentRecord
calcGpa classes = do
    let list = flip map classes tupleClasses
    let tup = tupleToGPA list
    (fth (head classes), fst tup, snd tup)

-- Takes a ClassRecord and converts it to an associated GPA
tupleClasses :: ClassRecord -> AssocGPA
tupleClasses cl = (sixh cl, frth cl)

-- Takes a list of associated GPAs and gets the final weighted gpa+credits
tupleToGPA :: [AssocGPA] -> AssocGPA
tupleToGPA list = do
    let sumCredits = fromIntegral (sum [c | (_,c) <- list])
    (sum [((x*(fromIntegral g))/sumCredits) | (x,g) <- list], sum [g | (_,g) <- list])

-- Formats a student record in the proper output format
formatRecord :: StudentRecord -> String
formatRecord student = printf "%32s  %-s  %-s" (fst3 student) (showFFloat (Just 2) (snd3 student) "") (show (last3 student))

-- Gets first, second, and last for triples
fst3 :: StudentRecord -> String
fst3 (a,_,_) = a
snd3 :: StudentRecord -> Double
snd3 (_,a,_) = a
last3 :: StudentRecord -> Int
last3 (_,_,a) = a

-- Gets fourth element of a 6-tuple
frth :: ClassRecord -> Int
frth (_,_,_,a,_,_) = a

-- Gets fifth element of a 6-tuple
fth :: ClassRecord -> String
fth (_,_,_,_,a,_) = a

-- Gets sixth element of a 6-tuple
sixh :: ClassRecord -> Double
sixh (_,_,_,_,_,a) = a

-- Tests the 5th (name) element of a ClassRecord to be equals
equalName :: ClassRecord -> ClassRecord -> Bool
equalName x y = (fth x) == (fth y)
