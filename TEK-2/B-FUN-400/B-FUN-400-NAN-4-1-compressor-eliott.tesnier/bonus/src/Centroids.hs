{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- Centroids
-}

module Centroids where

import System.Random
import FileParsing
import qualified Data.Set as Set
import Data.List (uncons)

import Distance

generateUniqueIndices :: Int -> Int -> Int -> Set.Set Int -> [Int]
generateUniqueIndices _ 0 _ acc = Set.toList acc
generateUniqueIndices seed k maxVal acc
    | Set.size acc >= maxVal = take k $ Set.toList acc
    | otherwise =
        let generator = mkStdGen (seed + Set.size acc)
            (index, _) = randomR (0, maxVal - 1) generator
        in if Set.member index acc
            then generateUniqueIndices (seed + 1) k maxVal acc
            else generateUniqueIndices seed (k-1) maxVal (Set.insert index acc)

generateIndices :: Int -> Int -> Int -> [Int]
generateIndices seed k maxVal = generateUniqueIndices seed k maxVal Set.empty

getFirstColor :: [CustomPixel] -> Color
getFirstColor pixels = case uncons pixels of
    Just (firstPixel, _) -> _color firstPixel
    Nothing -> error "Error: Empty pixel list."

pickNext :: [CustomPixel] -> [Color] -> Color
pickNext pixels centroids =
    let distances = calculateDistances pixels centroids
        cumulative = scanl1 (+) distances
        total = last cumulative
        randomValue = generateRandomValue total
        selectedPixel = selectPixel pixels cumulative randomValue
    in _color selectedPixel

calculateDistances :: [CustomPixel] -> [Color] -> [Float]
calculateDistances pxls centroids =
    map (\p -> minimum (map (realToFrac . distance (_color p)) centroids)) pxls

generateRandomValue :: Float -> Float
generateRandomValue total =
    let randomGen = mkStdGen 42
        (randInt, _) = random randomGen :: (Int, StdGen)
        normalizedRand = fromIntegral randInt / fromIntegral (maxBound :: Int)
    in normalizedRand * total

selectPixel :: [CustomPixel] -> [Float] -> Float -> CustomPixel
selectPixel pxls cumul randValue =
    case uncons (dropWhile (\(_, c) -> c < randValue) (zip pxls cumul)) of
        Just (firstPair, _) -> fst firstPair
        Nothing -> error "Error: No pixel selected."

initializeCentroids :: Int -> [CustomPixel] -> [Color]
initializeCentroids k pxls =
    let pickFirst = getFirstColor pxls
    in take k $ foldl (\acc _ -> acc ++ [pickNext pxls acc]) [pickFirst] [2..k]
