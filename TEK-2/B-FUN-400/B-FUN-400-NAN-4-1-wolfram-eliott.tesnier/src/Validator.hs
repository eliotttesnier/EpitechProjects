{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-wolfram-eliott.tesnier
-- File description:
-- Validator
-}

module Validator where

import Text.Read (readMaybe)

-- Validate rule (0-255) --
validateRule :: String -> Maybe Int
validateRule x = do
    n <- readMaybe x
    if n >= 0 && n <= 255 then Just n else Nothing

-- Validate non-negative integer --
validateNonNegative :: String -> Maybe Int
validateNonNegative x = do
    n <- readMaybe x
    if n >= 0 then Just n else Nothing

-- Validate positive integer --
validatePositive :: String -> Maybe Int
validatePositive x = do
    n <- readMaybe x
    if n > 0 then Just n else Nothing

-- Validate integer --
validateInt :: String -> Maybe Int
validateInt x = readMaybe x