{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- Error
-}

module Error where

import System.Exit
import System.IO

-- handleError --
handleError :: String -> IO ()
handleError msg = hPutStrLn stderr msg >> exitWith (ExitFailure 84)
