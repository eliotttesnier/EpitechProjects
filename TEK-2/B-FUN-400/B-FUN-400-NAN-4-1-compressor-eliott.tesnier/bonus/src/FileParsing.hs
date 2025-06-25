{-
-- EPITECH PROJECT, 2025
-- imageCompressor
-- File description:
-- FileParsing
-}

module FileParsing where

import Codec.Picture

type Position = (Int, Int)
type Color = (Int, Int, Int)

data CustomPixel = CustomPixel {
    _position :: Position,
    _color :: Color
} deriving (Eq, Ord)

instance Show CustomPixel where
    show (CustomPixel pos col) = show pos ++ " " ++ show col

convertPixelRGB8ToTuple :: PixelRGB8 -> (Int, Int, Int)
convertPixelRGB8ToTuple (PixelRGB8 r g b) = (fromIntegral r, fromIntegral g, fromIntegral b)

imageToPixels :: Image PixelRGB8 -> [CustomPixel]
imageToPixels img = [CustomPixel (x, y) (convertPixelRGB8ToTuple (pixelAt img x y))
                    | y <- [0..imageHeight img - 1],
                      x <- [0..imageWidth img - 1]]

parseFile :: FilePath -> IO (Maybe [CustomPixel])
parseFile filepath = do
    imageResult <- readImage filepath
    case imageResult of
        Left _ -> return Nothing
        Right image -> case convertRGB8 image of
            img -> return $ Just $ imageToPixels img
