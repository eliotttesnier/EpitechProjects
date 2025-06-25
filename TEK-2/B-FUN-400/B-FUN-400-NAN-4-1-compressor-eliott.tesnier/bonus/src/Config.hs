{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- Config
-}

module Config where

import Validators

-- ParseConfig (for parsing) --
data ParseConfig = ParseConfig {
    _p_nb_colors :: Maybe Int,
    _p_convergence :: Maybe Double,
    _p_filename :: Maybe String
} deriving (Show, Eq)

-- Config (for storing) --
data Config = Config {
    _nb_colors :: Int,
    _convergence :: Double,
    _filename :: String
} deriving (Show, Eq)

-- Empty ParseConfig --
emptyConfig :: ParseConfig
emptyConfig = ParseConfig Nothing Nothing Nothing

-- isComplete --
isComplete :: ParseConfig -> Bool
isComplete (ParseConfig (Just _) (Just _) (Just _)) = True
isComplete _ = False

-- parseArgs --
parseArgs :: ParseConfig -> [String] -> Maybe ParseConfig
parseArgs conf [] = Just conf
parseArgs conf ("-n":x:xs) = do
    n <- validateNbColor x
    parseArgs (conf { _p_nb_colors = Just n }) xs
parseArgs conf ("-l":x:xs) = do
    l <- validateConvergence x
    parseArgs (conf { _p_convergence = Just l }) xs
parseArgs conf ("-f":x:xs) = parseArgs (conf { _p_filename = Just x }) xs
parseArgs _ _ = Nothing

-- getOpts --
getOpts :: [String] -> Maybe Config
getOpts args = do
    ParseConfig (Just n) (Just l) (Just f) <- parseArgs emptyConfig args
    Just $ Config {
        _nb_colors = n,
        _convergence = l,
        _filename = f
    }
