{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-wolfram-eliott.tesnier
-- File description:
-- Config
-}

module Config where

import Validator

data Conf = Conf {
    rule :: Maybe Int,
    start :: Int,
    nbLines :: Maybe Int,
    window :: Int,
    move :: Int
} deriving (Show, Eq)

-- Default configuration --
defaultConf :: Conf
defaultConf = Conf {
    rule = Nothing,
    start = 0,
    nbLines = Nothing,
    window = 80,
    move = 0
}

-- Parse arguments --
getOpts :: Conf -> [String] -> Maybe Conf
getOpts conf [] = Just conf
getOpts conf ("--rule":x:xs) = do
    n <- validateRule x
    getOpts (conf { rule = Just n }) xs
getOpts conf ("--start":x:xs) = do
    n <- validateNonNegative x
    getOpts (conf { start = n }) xs
getOpts conf ("--lines":x:xs) = do
    n <- validateNonNegative x
    getOpts (conf { nbLines = Just n }) xs
getOpts conf ("--window":x:xs) = do
    n <- validatePositive x
    getOpts (conf { window = n }) xs
getOpts conf ("--move":x:xs) = do
    n <- validateInt x
    getOpts (conf { move = n }) xs
getOpts _ _ = Nothing
