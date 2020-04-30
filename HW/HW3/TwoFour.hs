module TwoFour (
    TwoFourTree(..),
    sampleTree
) where

-- Our TwoFour Tree Datatype
data TwoFourTree a = Nil
    | Branch2 a (TwoFourTree a) (TwoFourTree a)
    | Branch3 a a (TwoFourTree a) (TwoFourTree a) (TwoFourTree a)
    | Branch4  a a a (TwoFourTree a) (TwoFourTree a) (TwoFourTree a) (TwoFourTree a)
    deriving (Show)

-- Our sampleTree
sampleTree :: TwoFourTree Int
sampleTree = Branch4 2 3 4 Nil Nil (Branch2 5 Nil Nil) (Branch2 6 Nil (Branch2 7 Nil Nil))
