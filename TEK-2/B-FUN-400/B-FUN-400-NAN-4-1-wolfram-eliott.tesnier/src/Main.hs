{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-wolfram-eliott.tesnier
-- File description:
-- Main
-}

import System.Environment
import Config
import Error
import Rules
import Wolfram

-- Process rule --
processRule :: Conf -> IO ()
processRule Conf {rule = Nothing} = handleError "Error: -rule is mandatory."
processRule Conf
    {rule = Just r, start = s, window = w, move = m, nbLines = l} =
    case selectRule r of
        Nothing ->
            handleError $ "Error: Rule " ++ show r ++ " not implemented."
        Just ruleFunc ->
            runWolfram ruleFunc w s m l

-- Main function --
main :: IO ()
main = do
    args <- getArgs
    if null args
        then handleError "Error: No arguments provided."
        else case getOpts defaultConf args of
            Nothing -> handleError "Error: Invalid arguments."
            Just conf -> processRule conf
