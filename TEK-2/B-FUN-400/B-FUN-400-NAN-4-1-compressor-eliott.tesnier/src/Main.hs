{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- Main
-}

module Main (main) where

import System.Environment ( getArgs )
import Control.Monad ( when )
import Control.Parallel.Strategies ( parList, rseq, withStrategy )

import Error
import Config
import FileParsing
import Centroids
import Clustering
import qualified Data.Set as Set

handlePixels :: Config -> [Pixel] -> IO ()
handlePixels conf@(Config {_nb_colors = nbColors}) pixels
    | length pixels < nbColors = handleError "Error: Invalid -n."
    | otherwise =
        let centroids = initializeCentroids nbColors pixels
            initialClusters = withStrategy (parList rseq) $
                map (\x -> Cluster x (0, 0, 0) Set.empty) centroids
            clusters = calculateClusters conf pixels initialClusters
        in mapM_ (putStr . show) clusters

processCompressor :: Config -> IO ()
processCompressor config@(Config {_filename=filename}) = do
    fileContent <- readFile filename
    case parseFile fileContent of
        Nothing -> handleError "Error: Invalid file content."
        Just pixels -> handlePixels config pixels

main :: IO ()
main = do
    args <- getArgs
    when (null args) $ handleError "Error: No arguments provided."
    case getOpts args of
        Nothing -> handleError "Error: Invalid arguments."
        Just config -> processCompressor config
