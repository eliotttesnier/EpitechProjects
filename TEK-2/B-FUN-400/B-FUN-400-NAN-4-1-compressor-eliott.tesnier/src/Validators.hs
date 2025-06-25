{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- Validators
-}

module Validators where

import Text.Read (readMaybe)

-- ValidateNbColor (> 0)
validateNbColor :: String -> Maybe Int
validateNbColor x = do
    n <- readMaybe x
    if n > 0 then Just n else Nothing

validateConvergence :: String -> Maybe Double
validateConvergence x = do
    n <- readMaybe x
    if n > 0 then Just n else Nothing
