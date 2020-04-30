
module Lib
        ( someFunc
        ) where

import Data.List
import Text.ParserCombinators.ReadPrec

someFunc :: IO ()
someFunc = putStrLn "Hello, world!"


fib x
    | x < 2 = 1
    | otherwise = fib (x - 1) + fib (x - 2)


type IntFn = Int -> Int
fact :: IntFn
fact 0 = 1
fact 1 = 1
fact n = n * fact (n-1)

data CourseGrade = Credit Bool | Grade Double

passed :: CourseGrade -> Bool
passed (Credit x)= x
passed (Grade x) =
    if x > 1.7
        then True
    else
        False


data List t = Nil | Cons t (List t)

width ::List t -> Int
width Nil = 0
width (Cons x xs) = (width xs)+1

-- >>> width (Cons 1 (Cons 2 (Cons 3 Nil)))
-- 3
--
