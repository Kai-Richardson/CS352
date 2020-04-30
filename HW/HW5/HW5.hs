module HW5(parseRecord) where

import Text.Read
import Data.Maybe

-- PL 352 HW5 by Kai Richardson
-- Question 2:
--     New error: NegativeCourseNum
--         Requires each course number to be a positive integer


-- A record representing a student's course performance
-- Contains Subject, CourseNum, Section, NumCredits, "LastName, FirstName", Grade
type ClassRecord = (String,Int,String,Int,String,Double)

-- Parse error
data ParseError =
    WrongFieldCount Int         -- wrong count of fields, count provided
    | InvalidCourseNum String   -- invalid course number, string provided
    | InvalidNumCredits String  -- invalid number of credits, string provided
    | InvalidGrade String       -- invalid grade, string provided
    | NegativeCourseNum Int     -- invalid course number, negative int provided
    deriving Show

-- Convert an input string in the following format to a ClassRecord tuple:
--   Subject CourseNum Section NumCredits FirstName LastName GradeLetter
--
-- The fields are subject to the following constraints:
--   * CourseNum and NumCredits are integer values
--   * GradeLetter is a valid grade according to the following grammar:
--       [A-D]('+'|'-')? | 'F'
--   * There are exactly seven whitespace-separated fields
--
-- Returns the ClassRecord wrapped in Right on successful match,
-- an appropriate ParseError wrapped in Left otherwise.
parseRecord :: String -> Either ParseError ClassRecord
parseRecord line = do
    let list = words line
    if (length list /= 7) -- 7 elements required
        then Left (WrongFieldCount (length list))
        else
            if (isNothing (readMaybeFromString (list!!1))) -- Must be a integer
                then Left (InvalidCourseNum (list!!1))
                else
                    if ((fromMaybe 0 (readMaybeFromString (list!!1))) < 0) -- Must be a positive integer
                        then Left (NegativeCourseNum (fromMaybe 0 (readMaybeFromString (list!!1))))
                        else
                            if (isNothing (readMaybeFromString (list!!3))) -- Must be an integer
                                then Left (InvalidNumCredits (list!!3))
                                else
                                    if (isNothing (letterToGpa (list!!6))) -- Must match a defined grade
                                        then Left (InvalidGrade (list!!6))
                                        else
                                            Right (list!!0, (fromMaybe 0 (readMaybeFromString (list!!1))), list!!2, (fromMaybe 0 (readMaybeFromString (list!!3))), (list!!5 ++ ", " ++ list!!4), (fromMaybe 0 (letterToGpa (list!!6))))

-- Reads a string as an integer
readMaybeFromString :: String -> Maybe Int
readMaybeFromString str = readMaybe str :: Maybe Int

-- Converts a String grade to the numeric representation
letterToGpa :: String -> Maybe Double
letterToGpa str =
    case str of
        "A+" -> Just 4.3
        "A"  -> Just 4.0
        "A-" -> Just 3.7
        "B+" -> Just 3.3
        "B" -> Just 3.0
        "B-" -> Just 2.7
        "C+" -> Just 2.3
        "C" -> Just 2.0
        "C-" -> Just 1.7
        "D+" -> Just 1.3
        "D" -> Just 1.0
        "D-" -> Just 0.7
        "F" -> Just 0.0
        _ -> Nothing