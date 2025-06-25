{-
-- EPITECH PROJECT, 2025
-- imageCompressor
-- File description:
-- FileParsing
-}

module FileParsing where

import Text.Read
import Data.Maybe ( catMaybes )
import Control.Parallel.Strategies ( parMap, rseq )

type Position = (Int, Int)
type Color = (Int, Int, Int)

data Pixel = Pixel {
    _position :: Position,
    _color :: Color
} deriving (Eq, Ord)

instance Show Pixel where
    show (Pixel pos col) = show pos ++ " " ++ show col

parseLine :: [String] -> Maybe Pixel
parseLine [word1, word2] = liftA2 Pixel (readMaybe word1) (readMaybe word2)
parseLine _ = Nothing

parseLines :: [String] -> Maybe [Pixel]
parseLines linesList =
    let parsed = parMap rseq (parseLine . words) linesList
    in if Nothing `elem` parsed then Nothing else Just (catMaybes parsed)

parseFile :: String -> Maybe [Pixel]
parseFile = parseLines . lines
