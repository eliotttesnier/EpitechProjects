{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-wolfram-eliott.tesnier
-- File description:
-- Error
-}

module Error where

import System.Exit

-- Handle error --
handleError :: String -> IO a
handleError msg = putStrLn msg >> exitWith (ExitFailure 84)
