{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- Reconstruction
-}

module Reconstruction where

import Codec.Picture
import Data.List (foldl')
import Data.Char (toLower)
import Clustering
import FileParsing
import Control.Parallel.Strategies
import Control.DeepSeq
import qualified Data.Set as Set
import qualified Data.Map.Strict as Map

createPixelMap :: [Cluster] -> Map.Map (Int, Int) (Int, Int, Int)
createPixelMap clusters =
    let entries = [(pos, _meanCentroid cluster) |
                   cluster <- clusters,
                   CustomPixel pos _ <- Set.toList (_pixels cluster)]
    in force $ Map.fromList entries

createImage :: Int -> Int -> [Cluster] -> Image PixelRGB8
createImage width height clusters =
    let pixelMapping = createPixelMap clusters `using` rdeepseq
    in generateImage (pixelRenderer pixelMapping) width height
    where
        pixelRenderer pixelMapping x y =
            case Map.lookup (x, y) pixelMapping of
                Just (r, g, b) -> PixelRGB8 (fromIntegral r) (fromIntegral g) (fromIntegral b)
                Nothing -> PixelRGB8 0 0 0

getOutputPath :: String -> String
getOutputPath filename =
    let ext = reverse . takeWhile (/= '.') . reverse $ filename
    in case map toLower ext of
        "jpg" -> replaceExtension filename "_compressed.jpg"
        "jpeg" -> replaceExtension filename "_compressed.jpg"
        _ -> replaceExtension filename "_compressed.png"

replaceExtension :: String -> String -> String
replaceExtension filename newExt =
    (reverse . dropWhile (/= '.') . reverse $ filename) ++ newExt

saveImage :: String -> Image PixelRGB8 -> IO ()
saveImage outputPath img =
    let imgValue = force img
    in case map toLower . reverse . takeWhile (/= '.') . reverse $ outputPath of
        "jpg" -> saveJpgImage 100 outputPath (ImageRGB8 imgValue)
        "jpeg" -> saveJpgImage 100 outputPath (ImageRGB8 imgValue)
        "png" -> savePngImage outputPath (ImageRGB8 imgValue)
        _ -> savePngImage outputPath (ImageRGB8 imgValue)

printClusterColors :: [Cluster] -> IO ()
printClusterColors clusters = do
    putStrLn "Cluster colors:"
    mapM_ (\cluster -> let (r,g,b) = _meanCentroid cluster
                       in putStrLn $ "RGB: (" ++ show r ++ "," ++ show g ++ "," ++ show b ++ ")") clusters

findImageDimensions :: [CustomPixel] -> (Int, Int)
findImageDimensions pixels = force $ runEval $ do
    positions <- rseq $ map (\(CustomPixel (x, y) _) -> (x, y)) pixels
    maxX <- rpar $ foldl' (\acc (x, _) -> max acc x) 0 positions
    maxY <- rpar $ foldl' (\acc (_, y) -> max acc y) 0 positions
    return (maxX + 1, maxY + 1)
