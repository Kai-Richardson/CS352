import TwoFour
import Sized

main :: IO ()
main = do
    putStrLn (show sampleTree)
    putStrLn (show (size ["hello", "goodbye"]) ++ " " ++ show (size sampleTree))