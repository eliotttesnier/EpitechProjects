{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-wolfram-eliott.tesnier
-- File description:
-- Rules
-}

module Rules where

import Data.Bits

type Rule = (Char, Char, Char) -> Char

-- Convert pattern to index (0-7)
patternToIndex :: (Char, Char, Char) -> Int
patternToIndex (a, b, c) = 4 * charToInt a + 2 * charToInt b + charToInt c
  where
    charToInt '*' = 1
    charToInt _ = 0

-- Create rule function from rule number
makeRule :: Int -> Rule
makeRule n pattern = if testBit n (patternToIndex pattern) then '*' else ' '

-- Select implemented rule
selectRule :: Int -> Maybe Rule
selectRule n | n >= 0 && n <= 255 = Just (makeRule n)
            | otherwise = Nothing
