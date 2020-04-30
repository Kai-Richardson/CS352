module Sized where

import TwoFour

-- Define Sized typeclass
class Sized t where
    size :: t -> Int

-- Define Sized for arb. lists
instance Sized [a] where
    size [] = 0
    size (_:xs) = 1 + size xs

-- Define Sized for TwoFourTree
instance (Show a) => Sized (TwoFourTree a) where
    size Nil = 0
    size (Branch2 a b c) = 1 + size b + size c
    size (Branch3 a b c d e) = 2 + size c + size d + size e
    size (Branch4 a b c d e f g) = 3 + size d + size e + size f + size g
