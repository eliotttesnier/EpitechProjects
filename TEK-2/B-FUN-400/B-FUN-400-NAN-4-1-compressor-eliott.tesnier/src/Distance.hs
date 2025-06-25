{-
-- EPITECH PROJECT, 2025
-- B-FUN-400-NAN-4-1-compressor-eliott.tesnier
-- File description:
-- Distance
-}

module Distance where

import FileParsing
import Control.Parallel
import Control.Parallel.Strategies

distance :: Color -> Color -> Double
distance color1 color2 =
    let (r1, g1, b1) = color1
        (r2, g2, b2) = color2
        square x = (fromIntegral x :: Double) ** 2
        rDist' = square (r2-r1)
        gDist' = square (g2-g1)
        bDist' = square (b2-b1)
        total = rDist' + gDist' + bDist'
    in rDist' `par` gDist' `par` bDist' `pseq` sqrt total

-- Batch calculate distances between a color and multiple colors
distanceBatch :: Color -> [Color] -> [Double]
distanceBatch color colors =
    let computeDistances = map (distance color) colors
    in withStrategy (parList rseq) computeDistances
